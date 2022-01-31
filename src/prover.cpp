#include <fstream>
#include <iomanip>
#include "prover.hpp"
#include "utils.hpp"
#include "mem.hpp"
#include "batchmachine_executor.hpp"
#include "proof2zkin.hpp"
#include "verifier_cpp/main.hpp"
#include "binfile_utils.hpp"
#include "zkey_utils.hpp"
#include "wtns_utils.hpp"
#include "groth16.hpp"
#include "prove_context.hpp"

using namespace std;

Prover::Prover( RawFr &fr,
            const Rom &romData,
            const Script &script,
            const Pil &pil,
            const Pols &constPols,
            const Config &config ) :
        fr(fr),
        romData(romData),
        executor(fr, romData, config),
        script(script),
        pil(pil),
        constPols(constPols),
        config(config)
{
    mpz_init(altBbn128r);
    mpz_set_str(altBbn128r, "21888242871839275222246405745257275088548364400416034343698204186575808495617", 10);
    
    try {
        zkey = BinFileUtils::openExisting(config.starkVerifierFile, "zkey", 1); // TODO: Should we delete this?
        zkeyHeader = ZKeyUtils::loadHeader(zkey.get()); // TODO: Should we delete this?

        //std::string proofStr;
        if (mpz_cmp(zkeyHeader->rPrime, altBbn128r) != 0) {
            throw std::invalid_argument( "zkey curve not supported" );
        }

        groth16Prover = Groth16::makeProver<AltBn128::Engine>(
            zkeyHeader->nVars,
            zkeyHeader->nPublic,
            zkeyHeader->domainSize,
            zkeyHeader->nCoefs,
            zkeyHeader->vk_alpha1,
            zkeyHeader->vk_beta1,
            zkeyHeader->vk_beta2,
            zkeyHeader->vk_delta1,
            zkeyHeader->vk_delta2,
            zkey->getSectionData(4),    // Coefs
            zkey->getSectionData(5),    // pointsA
            zkey->getSectionData(6),    // pointsB1
            zkey->getSectionData(7),    // pointsB2
            zkey->getSectionData(8),    // pointsC
            zkey->getSectionData(9)     // pointsH1
        );

    } catch (std::exception& e) {
        cerr << "Error: Prover::Prover() got an exception: " << e.what() << '\n';
        exit(-1);
    }

    Pols2Refs(fr, constPols, constRefs);
}

Prover::~Prover ()
{
    mpz_clear(altBbn128r);
}

void Prover::prove (ProveContext &proveCtx)
{
    TimerStart(PROVER_PROVE);

    // Init the context for this prove
    if (proveCtx.uuid.size()==0)
    {
        proveCtx.uuid = getUUID();
    }
    proveCtx.timestamp = getTimestamp();
    cout << "Prover::prove() timestamp: " << proveCtx.timestamp << endl;
    cout << "Prover::prove() UUID: " << proveCtx.uuid << endl;

    proveCtx.init(config);
    cout << "Prover::prove() input file: " << proveCtx.inputFile << endl;
    cout << "Prover::prove() public file: " << proveCtx.publicFile << endl;
    cout << "Prover::prove() proof file: " << proveCtx.proofFile << endl;

    // Save input to <timestamp>.input.json, as provided by client
    json inputJson;
    proveCtx.input.save(inputJson);
    json2file(inputJson, proveCtx.inputFile);

    /************/
    /* Executor */
    /************/
    
    // Load committed polynomials into memory, mapped to a newly created output file, filled by executor
    Pols cmPols;
    cmPols.load(pil.cmPols);
    cmPols.mapToOutputFile(config.cmPolsFile);

    // Execute the program
    TimerStart(EXECUTOR_EXECUTE);
    executor.execute(proveCtx.input, cmPols, proveCtx.db, proveCtx.counters);
    TimerStopAndLog(EXECUTOR_EXECUTE);

    // Save input to <timestamp>.input.json, after execution
    json inputJsonEx;
    proveCtx.input.save(inputJsonEx, proveCtx.db);
    json2file(inputJsonEx, proveCtx.inputFileEx);

    // Save public.json file
    TimerStart(SAVE_PUBLIC_JSON);
    json publicJson;
    publicJson[0] = fr.toString(cmPols.FREE0.pData[0]);
    json2file(publicJson, proveCtx.publicFile);
    TimerStopAndLog(SAVE_PUBLIC_JSON);

    /***********************/
    /* STARK Batch Machine */
    /***********************/

    TimerStart(MEM_ALLOC);
    Mem mem;
    MemAlloc(mem, fr, script, cmPols, constRefs, config.constantsTreeFile);
    TimerStopAndLog(MEM_ALLOC);

    TimerStart(BATCH_MACHINE_EXECUTOR);
    json starkProof;
    BatchMachineExecutor bme(fr, script);
    bme.execute(mem, starkProof);
    json stark;
    stark["proof"] = starkProof;
    json globalHash;
    globalHash["globalHash"] = fr.toString(cmPols.FREE0.pData[0]);
    stark["publics"] = globalHash;

    TimerStopAndLog(BATCH_MACHINE_EXECUTOR);

    // If stark file present (i.e. enabled) save stark.json file to disk
    if (config.starkFile.size()>0)
    {
        TimerStart(SAVE_STARK_PROOF);
        json2file(stark, config.starkFile);
        TimerStopAndLog(SAVE_STARK_PROOF);
    }

    /****************/
    /* Proof 2 zkIn */
    /****************/

    TimerStart(PROOF2ZKIN);
    json zkin;
    proof2zkin(stark, zkin);
    zkin["globalHash"] = fr.toString(cmPols.FREE0.pData[0]);
    TimerStopAndLog(PROOF2ZKIN);

    // If stark file present (i.e. enabled) save stark.zkin.json file to disk
    if (config.starkFile.size()>0)
    {
        TimerStart(SAVE_ZKIN_PROOF);
        string zkinFile = config.starkFile;
        zkinFile.erase(zkinFile.find_last_not_of(".json")+1);
        zkinFile += ".zkin.json";
        json2file(zkin, zkinFile);
        TimerStopAndLog(SAVE_ZKIN_PROOF);
    }

#ifdef PROVER_INJECT_ZKIN_JSON
    TimerStart(PROVER_INJECT_ZKIN_JSON);
    zkin.clear();
    std::ifstream zkinStream("/home/fractasy/git/zkproverc/testvectors/zkin.json");
    if (!zkinStream.good())
    {
        cerr << "Error: failed loading zkin.json file " << endl;
        exit(-1);
    }
    zkinStream >> zkin;
    zkinStream.close();
    TimerStopAndLog(PROVER_INJECT_ZKIN_JSON);
#endif

    /************/
    /* Verifier */
    /************/
    TimerStart(CIRCOM_LOAD_CIRCUIT);    
    Circom_Circuit *circuit = loadCircuit(config.verifierFile);
    TimerStopAndLog(CIRCOM_LOAD_CIRCUIT);
 
    TimerStart(CIRCOM_LOAD_JSON);
    Circom_CalcWit *ctx = new Circom_CalcWit(circuit);
    loadJsonImpl(ctx, zkin);
    if (ctx->getRemaingInputsToBeSet()!=0)
    {
        cerr << "Error: Not all inputs have been set. Only " << get_main_input_signal_no()-ctx->getRemaingInputsToBeSet() << " out of " << get_main_input_signal_no() << endl;
        exit(-1);
    }
    TimerStopAndLog(CIRCOM_LOAD_JSON);

    // If present, save witness file
    if (config.witnessFile.size()>0)
    {
        TimerStart(CIRCOM_WRITE_BIN_WITNESS);
        writeBinWitness(ctx, config.witnessFile); // No need to write the file to disk, 12-13M fe, in binary, in wtns format
        TimerStopAndLog(CIRCOM_WRITE_BIN_WITNESS);
    }

    TimerStart(CIRCOM_GET_BIN_WITNESS);
    AltBn128::FrElement * pWitness = NULL;
    uint64_t witnessSize = 0;
    getBinWitness(ctx, pWitness, witnessSize);
    TimerStopAndLog(CIRCOM_GET_BIN_WITNESS);

#ifdef PROVER_USE_PROOF_GOOD_JSON
    // Load and parse a good proof JSON file, just for development and testing purposes
    string goodProofFile = "../testvectors/proof.good.json";
    std::ifstream goodProofStream(goodProofFile);
    if (!goodProofStream.good())
    {
        cerr << "Error: failed loading a good proof JSON file " << goodProofFile << endl;
        exit(-1);
    }
    json jsonProof;
    goodProofStream >> jsonProof;
    goodProofStream.close();
#else
    // Generate Groth16 via rapid SNARK
    TimerStart(RAPID_SNARK);
    json jsonProof;
    try
    {
        auto proof = groth16Prover->prove(pWitness); // TODO: Don't compile rapid snark files
        jsonProof = proof->toJson();
    }
    catch (std::exception& e)
    {
        cerr << "Error: Prover::Prove() got exception in rapid SNARK:" << e.what() << '\n';
        exit(-1);
    }
    TimerStopAndLog(RAPID_SNARK);
#endif

    // Save proof.json to disk
    json2file(jsonProof, proveCtx.proofFile);

    // Populate Proof with the correct data
    PublicInputsExtended publicInputsExtended;
    publicInputsExtended.publicInputs = proveCtx.input.publicInputs;
    publicInputsExtended.inputHash = NormalizeTo0xNFormat(fr.toString(cmPols.FREE0.pData[0], 16), 64);
    proveCtx.proof.load(jsonProof, publicInputsExtended);

    /***********/
    /* Cleanup */
    /***********/

    TimerStart(MEM_FREE);
    MemFree(mem);
    TimerStopAndLog(MEM_FREE);

    free(pWitness);
    cmPols.unmap();

    //cout << "Prover::prove() done" << endl;

    TimerStopAndLog(PROVER_PROVE);
}
