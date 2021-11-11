
#include <iostream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "ffiasm/fr.hpp"
#include "executor.hpp"

using namespace std;
using json = nlohmann::json;

#define NEVALUATIONS 1000 //1<<23 // 8M
#define NPOLS 100 //512
// TODO: Segmentation fault: out of memory -> memmory allocated in file

typedef RawFr::Element tPolynomial[NEVALUATIONS]; // This one could be dynamic, based on PIL JSON file contents, or static
typedef tPolynomial tExecutorOutput[NPOLS]; // This one could be static
// TODO: Allocate dynamically?

#define INVALID_ID 0xFFFFFFFFFFFFFFFF
uint64_t A0 = INVALID_ID;
uint64_t A1 = INVALID_ID;
uint64_t A2 = INVALID_ID;
uint64_t A3 = INVALID_ID;
uint64_t B0 = INVALID_ID;
uint64_t B1 = INVALID_ID;
uint64_t B2 = INVALID_ID;
uint64_t B3 = INVALID_ID;
uint64_t C0 = INVALID_ID;
uint64_t C1 = INVALID_ID;
uint64_t C2 = INVALID_ID;
uint64_t C3 = INVALID_ID;
uint64_t D0 = INVALID_ID;
uint64_t D1 = INVALID_ID;
uint64_t D2 = INVALID_ID;
uint64_t D3 = INVALID_ID;
uint64_t E0 = INVALID_ID;
uint64_t E1 = INVALID_ID;
uint64_t E2 = INVALID_ID;
uint64_t E3 = INVALID_ID;
uint64_t FREE0 = INVALID_ID;
uint64_t FREE1 = INVALID_ID;
uint64_t FREE2 = INVALID_ID;
uint64_t FREE3 = INVALID_ID;
uint64_t CONST = INVALID_ID;
uint64_t CTX = INVALID_ID;
uint64_t GAS = INVALID_ID;
uint64_t JMP = INVALID_ID;
uint64_t JMPC = INVALID_ID;
uint64_t MAXMEM = INVALID_ID;
uint64_t PC = INVALID_ID;
uint64_t SP = INVALID_ID;
uint64_t SR = INVALID_ID;
uint64_t arith = INVALID_ID;
uint64_t assert = INVALID_ID;
uint64_t bin = INVALID_ID;
uint64_t comparator = INVALID_ID;
uint64_t ecRecover = INVALID_ID;
uint64_t hashE = INVALID_ID;
uint64_t hashRD = INVALID_ID;
uint64_t hashWR = INVALID_ID;
uint64_t inA = INVALID_ID;
uint64_t inB = INVALID_ID;
uint64_t inC = INVALID_ID;
uint64_t inD = INVALID_ID;
uint64_t inE = INVALID_ID;
uint64_t inCTX = INVALID_ID;
uint64_t inFREE = INVALID_ID;
uint64_t inGAS = INVALID_ID;
uint64_t inMAXMEM = INVALID_ID;
uint64_t inPC = INVALID_ID;
uint64_t inSP = INVALID_ID;
uint64_t inSR = INVALID_ID;
uint64_t inSTEP = INVALID_ID;
uint64_t inc = INVALID_ID;
uint64_t ind = INVALID_ID;
uint64_t isCode = INVALID_ID;
uint64_t isMaxMem = INVALID_ID;
uint64_t isMem = INVALID_ID;
uint64_t isNeg = INVALID_ID;
uint64_t isStack = INVALID_ID;
uint64_t mRD = INVALID_ID;
uint64_t mWR = INVALID_ID;
uint64_t neg = INVALID_ID;
uint64_t offset = INVALID_ID;
uint64_t opcodeRomMap = INVALID_ID;
uint64_t sRD = INVALID_ID;
uint64_t sWR = INVALID_ID;
uint64_t setA = INVALID_ID;
uint64_t setB = INVALID_ID;
uint64_t setC = INVALID_ID;
uint64_t setD = INVALID_ID;
uint64_t setE = INVALID_ID;
uint64_t setCTX = INVALID_ID;
uint64_t setGAS = INVALID_ID;
uint64_t setMAXMEM = INVALID_ID;
uint64_t setPC = INVALID_ID;
uint64_t setSP = INVALID_ID;
uint64_t setSR = INVALID_ID;
uint64_t shl = INVALID_ID;
uint64_t shr = INVALID_ID;
uint64_t useCTX = INVALID_ID;
uint64_t zkPC = INVALID_ID;
uint64_t byte4_freeIN = INVALID_ID;
uint64_t byte4_out = INVALID_ID;

// TODO: check if map performance is better
void addPol(string &name, uint64_t id)
{
         if (name=="main.A0") A0 = id;
    else if (name=="main.A1") A1 = id;
    else if (name=="main.A2") A2 = id;
    else if (name=="main.A3") A3 = id;
    else if (name=="main.B0") B0 = id;
    else if (name=="main.B1") B1 = id;
    else if (name=="main.B2") B2 = id;
    else if (name=="main.B3") B3 = id;
    else if (name=="main.C0") C0 = id;
    else if (name=="main.C1") C1 = id;
    else if (name=="main.C2") C2 = id;
    else if (name=="main.C3") C3 = id;
    else if (name=="main.D0") D0 = id;
    else if (name=="main.D1") D1 = id;
    else if (name=="main.D2") D2 = id;
    else if (name=="main.D3") D3 = id;
    else if (name=="main.E0") E0 = id;
    else if (name=="main.E1") E1 = id;
    else if (name=="main.E2") E2 = id;
    else if (name=="main.E3") E3 = id;
    else if (name=="main.FREE0") FREE0 = id;
    else if (name=="main.FREE1") FREE1 = id;
    else if (name=="main.FREE2") FREE2 = id;
    else if (name=="main.FREE3") FREE3 = id;
    else if (name=="main.CONST") CONST = id;
    else if (name=="main.CTX") CTX = id;
    else if (name=="main.GAS") GAS = id;
    else if (name=="main.JMP") JMP = id;
    else if (name=="main.JMPC") JMPC = id;
    else if (name=="main.MAXMEM") MAXMEM = id;
    else if (name=="main.PC") PC = id;
    else if (name=="main.SP") SP = id;
    else if (name=="main.SR") SR = id;
    else if (name=="main.arith") arith = id;
    else if (name=="main.assert") assert = id;
    else if (name=="main.bin") bin = id;
    else if (name=="main.comparator") comparator = id;
    else if (name=="main.ecRecover") ecRecover = id;
    else if (name=="main.hashE") hashE = id;
    else if (name=="main.hashRD") hashRD = id;
    else if (name=="main.hashWR") hashWR = id;
    else if (name=="main.inA") inA = id;
    else if (name=="main.inB") inB = id;
    else if (name=="main.inC") inC = id;
    else if (name=="main.inD") inD = id;
    else if (name=="main.inE") inE = id;
    else if (name=="main.inCTX") inCTX = id;
    else if (name=="main.inFREE") inFREE = id;
    else if (name=="main.inGAS") inGAS = id;
    else if (name=="main.inMAXMEM") inMAXMEM = id;
    else if (name=="main.inPC") inPC = id;
    else if (name=="main.inSP") inSP = id;
    else if (name=="main.inSR") inSR = id;
    else if (name=="main.inSTEP") inSTEP = id;
    else if (name=="main.inc") inc = id;
    else if (name=="main.ind") ind = id;
    else if (name=="main.isCode") isCode = id;
    else if (name=="main.isMaxMem") isMaxMem = id;
    else if (name=="main.isMem") isMem = id;
    else if (name=="main.isNeg") isNeg = id;
    else if (name=="main.isStack") isStack = id;
    else if (name=="main.mRD") mRD = id;
    else if (name=="main.mWR") mWR = id;
    else if (name=="main.neg") neg = id;
    else if (name=="main.offset") offset = id;
    else if (name=="main.opcodeRomMap") opcodeRomMap = id;
    else if (name=="main.sRD") sRD = id;
    else if (name=="main.sWR") sWR = id;
    else if (name=="main.setA") setA = id;
    else if (name=="main.setB") setB = id;
    else if (name=="main.setC") setC = id;
    else if (name=="main.setD") setD = id;
    else if (name=="main.setE") setE = id;
    else if (name=="main.setCTX") setCTX = id;
    else if (name=="main.setGAS") setGAS = id;
    else if (name=="main.setMAXMEM") setMAXMEM = id;
    else if (name=="main.setPC") setPC = id;
    else if (name=="main.setSP") setSP = id;
    else if (name=="main.setSR") setSR = id;
    else if (name=="main.shl") shl = id;
    else if (name=="main.shr") shr = id;
    else if (name=="main.useCTX") useCTX = id;
    else if (name=="main.zkPC") zkPC = id;
    else if (name=="byte4.freeIN") byte4_freeIN = id;
    else if (name=="byte4.out") byte4_out = id;
    else
    {
        cerr << "Error: pol() could not find a polynomial for name: " << name << ", id: " << id << endl;
        exit(-1); // TODO: Should we kill the process?
    }
}

typedef struct {
    uint64_t ln; // Program Counter (PC)
    uint64_t step; // Interation, instruction execution loop counter
    string fileName; // From ROM JSON file instruction
    uint64_t line; // From ROM JSON file instruction
    map<string,RawFr::Element> vars; 
    RawFr *pFr;
    tExecutorOutput * pPols;
} tContext;

void createPols(tExecutorOutput &pols, json &pil);
void initState(RawFr &fr, tExecutorOutput &pols);
void preprocessTxs(tContext &ctx, json &input);
RawFr::Element evalCommand(tContext &ctx, json tag);
int64_t fe2n(RawFr &fr, RawFr::Element &fe);

void execute(RawFr &fr, json &input, json &rom, json &pil)
{
    cout << "execute()" << endl;

    tExecutorOutput pols;
    tContext ctx;
    ctx.pFr = &fr;
    ctx.pPols = &pols;
    RawFr::Element op3, op2, op1, op0;

    createPols(pols, pil); // TODO: rename to addPols()

    initState(fr, pols);

    preprocessTxs(ctx, input);

    assert(rom.is_array());

    for (uint64_t i=0; i<NEVALUATIONS; i++)
    {
        //ctx.ln = Fr_toInt(pols[zkPC][i].v); // TODO: ctx.ln = Fr.toObject(pols.main.zkPC[i]);
        ctx.ln = i;
        ctx.step = i; // To be used inside evaluateCommand() to find the current value of the registers
        //ctx.A = [pols.main.A0[i], pols.main.A1[i], pols.main.A2[i], pols.main.A3[i]];
        //ctx.B = [pols.main.B0[i], pols.main.B1[i], pols.main.B2[i], pols.main.B3[i]];
        //ctx.C = [pols.main.C0[i], pols.main.C1[i], pols.main.C2[i], pols.main.C3[i]];
        //ctx.D = [pols.main.D0[i], pols.main.D1[i], pols.main.D2[i], pols.main.D3[i]];
        //ctx.E = [pols.main.E0[i], pols.main.E1[i], pols.main.E2[i], pols.main.E3[i]];
        //ctx.SR = pols.main.SR[i];
        //ctx.CTX = pols.main.CTX[i];
        //ctx.SP = pols.main.SP[i];
        //ctx.PC = pols.main.PC[i];
        //ctx.MAXMEM = pols.main.MAXMEM[i];
        //ctx.GAS = pols.main.GAS[i];
        //ctx.zkPC = pols.main.zkPC[i];
    
        // Get the line ctx.ln from the ROM JSON file
        //const l = rom[ fe2n(Fr, ctx.zkPC) ];
        json l = rom[ctx.ln];

        // In case we reached the end of the ROM JSON file, break the for() loop
        if (!l.is_object())
        {
            break;
        }

        ctx.fileName = l["fileName"]; // TODO: check presence and type
        ctx.line = l["line"]; // TODO: check presence and type

        //printRegs(Fr, ctx);

        //if (i==104) {
        //    console.log("pause");
        //}

        if (l["cmdBefore"].is_array()) {
            for (json::iterator it = l["cmdBefore"].begin(); it != l["cmdBefore"].end(); ++it) {
                std::cout << "cmdBefore: " << *it << '\n';
                evalCommand(ctx,*it);
            }
        }
        /*if (l.cmdBefore) {
            for (let j=0; j< l.cmdBefore.length; j++) {
                evalCommand(ctx, l.cmdBefore[j]);
            }
        }*/

        op0 = op1 = op2 = op3 = fr.zero(); //[op0, op1, op2, op3] = [Fr.zero, Fr.zero, Fr.zero, Fr.zero];

        if (l["inA"]==1)
        {
            fr.copy(op0,pols[A0][i]); // TODO: Confirm with Jordi that this can be a fr.copy() instead of a fr.add(op0,op0,pols[A0][i])
            fr.copy(op1,pols[A1][i]);
            fr.copy(op2,pols[A2][i]);
            fr.copy(op3,pols[A3][i]);
            pols[inA][i] = fr.one();
        }
        else {
            pols[inA][i] = fr.zero();
        }
        /*if (l.inA == 1) {
            [op0, op1, op2, op3] = [Fr.add(op0, ctx.A[0]), Fr.add(op1, ctx.A[1]), Fr.add(op2, ctx.A[2]), Fr.add(op3, ctx.A[3])];
            pols.main.inA[i] = Fr.one;
        } else {
            pols.main.inA[i] = Fr.zero;
        }*/

        // TODO: If inA==1, it should exclude inB==1.  Can we skip this if?  Or fail if both are 1?
        if (l["inB"]==1) {
            fr.copy(op0,pols[B0][i]);
            fr.copy(op1,pols[B1][i]);
            fr.copy(op2,pols[B2][i]);
            fr.copy(op3,pols[B3][i]);
            pols[inB][i] = fr.one();
        } else {
            pols[inB][i] = fr.zero();
        }

        if (l["inC"]==1) {
            fr.copy(op0,pols[C0][i]);
            fr.copy(op1,pols[C1][i]);
            fr.copy(op2,pols[C2][i]);
            fr.copy(op3,pols[C3][i]);
            pols[inC][i] = fr.one();
        } else {
            pols[inC][i] = fr.zero();
        }

        if (l["inD"]==1) {
            fr.copy(op0,pols[D0][i]);
            fr.copy(op1,pols[D1][i]);
            fr.copy(op2,pols[D2][i]);
            fr.copy(op3,pols[D3][i]);
            pols[inD][i] = fr.one();
        } else {
            pols[inD][i] = fr.zero();
        }

        if (l["inE"]==1) {
            fr.copy(op0,pols[E0][i]);
            fr.copy(op1,pols[E1][i]);
            fr.copy(op2,pols[E2][i]);
            fr.copy(op3,pols[E3][i]);
            pols[inE][i] = fr.one();
        } else {
            pols[inE][i] = fr.zero();
        }

        if (l["inSR"]==1) {
            fr.copy(op0,pols[SR][i]);
            pols[inSR][i] = fr.one();
        } else {
            pols[inSR][i] = fr.zero();
        }
        /*if (l.inSR == 1) {
            op0 = Fr.add(op0, ctx.SR);
            pols.main.inSR[i] = Fr.one;
        } else {
            pols.main.inSR[i] = Fr.zero;
        }*/

        if (l["inCTX"]==1) {
            fr.copy(op0,pols[CTX][i]);
            pols[inCTX][i] = fr.one();
        } else {
            pols[inCTX][i] = fr.zero();
        }

        if (l["inSP"]==1) {
            fr.copy(op0,pols[SP][i]);
            pols[inSP][i] = fr.one();
        } else {
            pols[inSP][i] = fr.zero();
        }

        if (l["inPC"]==1) {
            fr.copy(op0,pols[PC][i]);
            pols[inPC][i] = fr.one();
        } else {
            pols[inPC][i] = fr.zero();
        }
        
        if (l["inGAS"]==1) {
            fr.copy(op0,pols[GAS][i]);
            pols[inGAS][i] = fr.one();
        } else {
            pols[inGAS][i] = fr.zero();
        }

        if (l["inMAXMEM"]==1) {
            fr.copy(op0,pols[MAXMEM][i]);
            pols[inMAXMEM][i] = fr.one();
        } else {
            pols[inMAXMEM][i] = fr.zero();
        }

        if (l["inSTEP"]==1) {
            fr.fromUI(op0, i);  // TODO: Confirm with Jordi that this is the equivalent to fr.e(i)?
            pols[inSTEP][i] = fr.one();
        } else {
            pols[inSTEP][i] = fr.zero();
        }

        /*if (l.inSTEP == 1) {
            op0 = Fr.add(op0, Fr.e(i));
            pols.main.inSTEP[i] = Fr.one;
        } else {
            pols.main.inSTEP[i] = Fr.zero;
        }*/

        if (l["CONST"].is_number_unsigned()) {
            fr.fromUI(pols[CONST][i],l["CONST"]);
            pols[inSTEP][i] = fr.one();
        } else {
            pols[inSTEP][i] = fr.zero();
        }
        /*        if (!isNaN(l.CONST)) {
            pols.main.CONST[i] = Fr.e(l.CONST);
            op0 = Fr.add(op0, pols.main.CONST[i]);
        } else {
            pols.main.CONST[i] = Fr.zero;
        }*/

        int64_t addrRel = 0; // TODO: Check with Jordi if this is the right type for an address
        uint64_t addr = 0;
        /*
        let addrRel = 0;
        let addr = 0;
        */
        if (l["mRD"]==1 || l["mWR"]==1 || l["hashRD"]==1 || l["hashWR"]==1 || l["hashE"]==1 || l["JMP"]==1 || l["JMPC"]==1) {
            if (l["ind"]==1) ;// addrRel = fe2n(Fr, ctx.E[0]); // TODO: Migrate this
            if (l["offset"].is_number_integer())
            {
                int64_t offset = l["offset"];
                addrRel += offset;
            }
            if (addrRel>=0x100000000)
            {
                cerr << "Error: addrRel >= 0x100000000" << endl;
                exit(-1); // TODO: Should we kill the process?
            }
            if (addrRel<0)
            {
                cerr << "Error: addrRel < 0" << endl;
                exit(-1); // TODO: Should we kill the process?
            }
            addr = addrRel;
        }

        /*
        if (l.mRD || l.mWR || l.hashRD || l.hashWR || l.hashE || l.JMP || l.JMPC) {
            if (l.ind) addrRel = fe2n(Fr, ctx.E[0]);
            if (l.offset) addrRel += l.offset;
            if (addrRel >= 0x100000000) throw new Error(`Address too big: ${ctx.ln}`);
            if (addrRel <0 ) throw new Error(`Address can not be negative: ${ctx.ln}`);
            addr = addrRel;
        }
        */
        if (l["useCTX"]==1) {
            addr += 0x400000000;
            pols[useCTX][i] = fr.one();
        } else {
            pols[useCTX][i] = fr.zero();
        }
        /*
        if (l.useCTX==1) {
            addr += 0x400000000;
            pols.main.useCTX[i] = Fr.one;
        } else {
            pols.main.useCTX[i] = Fr.zero;
        }
        */
        if (l["isCode"]==1) {
            addr += 0x100000000;
            pols[isCode][i] = fr.one();
        } else {
            pols[isCode][i] = fr.zero();
        }
        /*
        if (l.isCode==1) {
            addr += 0x100000000;
            pols.main.isCode[i] = Fr.one;
        } else {
            pols.main.isCode[i] = Fr.zero;
        }*/

        if (l["isStack"]==1) {
            addr += 0x200000000;
            pols[isStack][i] = fr.one();
        } else {
            pols[isStack][i] = fr.zero();
        }
        /*
        if (l.isStack==1) {
            addr += 0x200000000;
            pols.main.isStack[i] = Fr.one;
        } else {
            pols.main.isStack[i] = Fr.zero;
        }*/
        if (l["isMem"]==1) {
            addr += 0x300000000;
            pols[isMem][i] = fr.one();
        } else {
            pols[isMem][i] = fr.zero();
        }
        /*
        if (l.isMem==1) {
            addr += 0x300000000;
            pols.main.isMem[i] = Fr.one;
        } else {
            pols.main.isMem[i] = Fr.zero;
        }*/
        if (l["inc"].is_number_unsigned()) {
            fr.fromUI(pols[inc][i],l["inc"]);
        } else {
            pols[inc][i] = fr.zero();
        }
        /*
        if (l.inc) {
            pols.main.inc[i] = Fr.e(l.inc);
        } else {
            pols.main.inc[i] = Fr.zero;
        }*/
        if (l["ind"].is_number_unsigned()) {
            fr.fromUI(pols[ind][i],l["ind"]);
        } else {
            pols[ind][i] = fr.zero();
        }
        /*
        if (l.ind) {
            pols.main.ind[i] = Fr.e(l.ind);
        } else {
            pols.main.ind[i] = Fr.zero;
        }*/
        if (l["offset"].is_number_unsigned()) {
            fr.fromUI(pols[offset][i],l["offset"]);
        } else {
            pols[offset][i] = fr.zero();
        }
        /*
        if (l.offset) {
            pols.main.offset[i] = Fr.e(l.offset);
        } else {
            pols.main.offset[i] = Fr.zero;
        }*/

        /*
        if (l.inFREE) {

            if (!l.freeInTag) {
                throw new Error(`Instruction with freeIn without freeInTag: ${ctx.ln}`);
            }
            
            let fi;
            if (l.freeInTag.op=="") {
                let nHits = 0;
                if (l.mRD == 1) {
                    if (typeof ctx.mem[addr] != "undefined") {
                        fi = ctx.mem[addr];
                    } else {
                        fi = [Fr.zero, Fr.zero, Fr.zero, Fr.zero];
                    }
                    nHits++;
                }
                if (l.sRD == 1) {
                    const saddr = fe2bns([ctx.A0, ctx.A1, ctx.A2, ctx.A3]);
                    if (typeof ctx.sto[saddr] === "undefined" ) throw new Error(`Storage not initialized: ${ctx.ln}`);
                    fi = ctx.sto[ saddr ];
                    nHits++;
                }
                if (l.hashRD == 1) {
                    if (!ctx.hash[addr]) throw new Error("Hash address not initialized");
                    if (typeof ctx.hash[addr].result == "undefined") throw new Error("Hash not finalized");
                    fi = bn2bna(Fr, ctx.hash[addr].result);
                    nHits++;
                }
                if (l.ecRecover == 1) {
                    const d = ethers.utils.hexlify(fea2bn(Fr, ctx.A));
                    const r = ethers.utils.hexlify(fea2bn(Fr, ctx.B));
                    const s = ethers.utils.hexlify(fea2bn(Fr, ctx.C));
                    const v = ethers.utils.hexlify(fe2n(Fr, ctx.D[0]));
                    const raddr =  ethers.utils.recoverAddress(d, {
                        r: r,
                        s: s,
                        v: v
                    });
                    fi = bn2bna(Fr, raddr);
                    nHits++;
                }
                if (l.shl == 1) {
                    const a = Scalar.e(fea2bn(Fr, ctx.A));
                    const s = fe2n(Fr, ctx.D[0]);
                    if ((s>32) || (s<0)) throw new Error(`SHL too big: ${ctx.ln}`);
                    fi = bn2bna(Fr, Scalar.band(Scalar.shl(a, s*8), Scalar.e("0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")));
                    nHits++;
                } 
                if (l.shr == 1) {
                    const a = Scalar.e(fea2bn(Fr, ctx.A));
                    const s = fe2n(Fr, ctx.D[0]);
                    if ((s>32) || (s<0)) throw new Error(`SHR too big: ${ctx.ln}`);
                    fi = bn2bna(Fr, Scalar.shr(a, s*8));
                    nHits++;
                } 
                if (nHits==0) {
                    throw new Error(`Empty freeIn without a valid instruction: ${ctx.ln}`);
                }
                if (nHits>1) {
                    throw new Error(`Only one instructuin that requires freeIn is alllowed: ${ctx.ln}`);
                }
            } else {
                fi = evalCommand(ctx, l.freeInTag);
            }
            [pols.main.FREE0[i], pols.main.FREE1[i], pols.main.FREE2[i], pols.main.FREE3[i]] = fi;
            [op0, op1, op2, op3] = [Fr.add(op0, fi[0]), Fr.add(op1, fi[1]), Fr.add(op2, fi[2]), Fr.add(op3, fi[3])];
            pols.main.inFREE[i] = Fr.one;

        } else {
            [pols.main.FREE0[i], pols.main.FREE1[i], pols.main.FREE2[i], pols.main.FREE3[i]] = [Fr.zero, Fr.zero, Fr.zero, Fr.zero];
            pols.main.inFREE[i] = Fr.zero;
        }*/
        if (l["neg"]==1) {
            fr.neg(op0,op0);
            pols[neg][i] = fr.one();
        } else {
            pols[neg][i] = fr.zero();
        }
        /*
        if (l.neg==1) {
            op0 = Fr.neg(op0);
            pols.main.neg[i] = Fr.one;
        } else {
            pols.main.neg[i] = Fr.one;
        }*/

        if (l["assert"]==1) {
            if ( (!fr.eq(pols[A0][i],op0)) ||
                 (!fr.eq(pols[A1][i],op1)) ||
                 (!fr.eq(pols[A2][i],op2)) ||
                 (!fr.eq(pols[A3][i],op3)) )
            {
                cerr << "Error: ROM assert failed: AN!=opN" << endl;
                // exit(-1); // TODO: Should we kill the process?
            }
            pols[assert][i] = fr.one();
        } else {
            pols[assert][i] = fr.zero();
        }
/*
        if (l.assert) {
            if ( 
                    (!Fr.eq(ctx.A[0], op0)) ||
                    (!Fr.eq(ctx.A[1], op1)) ||
                    (!Fr.eq(ctx.A[2], op2)) ||
                    (!Fr.eq(ctx.A[3], op3))
            ) {
                throw new Error(`Assert does not match: ${ctx.ln}`);
            }
            pols.main.assert[i] = Fr.one;
        } else {
            pols.main.assert[i] = Fr.zero;
        }

*/
        if (l["setA"]==1) {
            fr.copy(pols[A0][i+1],op0);
            fr.copy(pols[A1][i+1],op1);
            fr.copy(pols[A2][i+1],op2);
            fr.copy(pols[A3][i+1],op3);
            pols[setA][i] = fr.one(); // TODO: Should we save the flag before or after the action?  We need consistency.
        } else {
            fr.copy(pols[A0][i+1],pols[A0][i]);
            fr.copy(pols[A1][i+1],pols[A1][i]);
            fr.copy(pols[A2][i+1],pols[A2][i]);
            fr.copy(pols[A3][i+1],pols[A3][i]);
            pols[setA][i] = fr.zero();
        }
/*
        if (l.setA == 1) {
            pols.main.setA[i]=Fr.one;
            [pols.main.A0[i+1], pols.main.A1[i+1], pols.main.A2[i+1], pols.main.A3[i+1]] = [op0, op1, op2, op3];
        } else {
            pols.main.setA[i]=Fr.zero;
            [pols.main.A0[i+1], pols.main.A1[i+1], pols.main.A2[i+1], pols.main.A3[i+1]] = [pols.main.A0[i], pols.main.A1[i], pols.main.A2[i], pols.main.A3[i]];
        }
*/
        if (l["setB"]==1) {
            fr.copy(pols[B0][i+1],op0);
            fr.copy(pols[B1][i+1],op1);
            fr.copy(pols[B2][i+1],op2);
            fr.copy(pols[B3][i+1],op3);
            pols[setB][i] = fr.one();
        } else {
            fr.copy(pols[B0][i+1],pols[B0][i]);
            fr.copy(pols[B1][i+1],pols[B1][i]);
            fr.copy(pols[B2][i+1],pols[B2][i]);
            fr.copy(pols[B3][i+1],pols[B3][i]);
            pols[setB][i] = fr.zero();
        }

/*
        if (l.setB == 1) {
            pols.main.setB[i]=Fr.one;
            [pols.main.B0[i+1], pols.main.B1[i+1], pols.main.B2[i+1], pols.main.B3[i+1]] = [op0, op1, op2, op3];
        } else {
            pols.main.setB[i]=Fr.zero;
            [pols.main.B0[i+1], pols.main.B1[i+1], pols.main.B2[i+1], pols.main.B3[i+1]] = [pols.main.B0[i], pols.main.B1[i], pols.main.B2[i], pols.main.B3[i]];
        }
*/
        if (l["setC"]==1) {
            fr.copy(pols[C0][i+1],op0);
            fr.copy(pols[C1][i+1],op1);
            fr.copy(pols[C2][i+1],op2);
            fr.copy(pols[C3][i+1],op3);
            pols[setC][i] = fr.one();
        } else {
            fr.copy(pols[C0][i+1],pols[C0][i]);
            fr.copy(pols[C1][i+1],pols[C1][i]);
            fr.copy(pols[C2][i+1],pols[C2][i]);
            fr.copy(pols[C3][i+1],pols[C3][i]);
            pols[setC][i] = fr.zero();
        }
/*
        if (l.setC == 1) {
            pols.main.setC[i]=Fr.one;
            [pols.main.C0[i+1], pols.main.C1[i+1], pols.main.C2[i+1], pols.main.C3[i+1]] = [op0, op1, op2, op3];
        } else {
            pols.main.setC[i]=Fr.zero;
            [pols.main.C0[i+1], pols.main.C1[i+1], pols.main.C2[i+1], pols.main.C3[i+1]] = [pols.main.C0[i], pols.main.C1[i], pols.main.C2[i], pols.main.C3[i]];
        }
*/
        if (l["setD"]==1) {
            fr.copy(pols[D0][i+1],op0);
            fr.copy(pols[D1][i+1],op1);
            fr.copy(pols[D2][i+1],op2);
            fr.copy(pols[D3][i+1],op3);
            pols[setD][i] = fr.one();
        } else {
            fr.copy(pols[D0][i+1],pols[D0][i]);
            fr.copy(pols[D1][i+1],pols[D1][i]);
            fr.copy(pols[D2][i+1],pols[D2][i]);
            fr.copy(pols[D3][i+1],pols[D3][i]);
            pols[setD][i] = fr.zero();
        }
/*
        if (l.setD == 1) {
            pols.main.setD[i]=Fr.one;
            [pols.main.D0[i+1], pols.main.D1[i+1], pols.main.D2[i+1], pols.main.D3[i+1]] = [op0, op1, op2, op3];
        } else {
            pols.main.setD[i]=Fr.zero;
            [pols.main.D0[i+1], pols.main.D1[i+1], pols.main.D2[i+1], pols.main.D3[i+1]] = [pols.main.D0[i], pols.main.D1[i], pols.main.D2[i], pols.main.D3[i]];
        }
*/
        if (l["setE"]==1) {
            fr.copy(pols[E0][i+1],op0);
            fr.copy(pols[E1][i+1],op1);
            fr.copy(pols[E2][i+1],op2);
            fr.copy(pols[E3][i+1],op3);
            pols[setE][i] = fr.one();
        } else {
            fr.copy(pols[E0][i+1],pols[E0][i]);
            fr.copy(pols[E1][i+1],pols[E1][i]);
            fr.copy(pols[E2][i+1],pols[E2][i]);
            fr.copy(pols[E3][i+1],pols[E3][i]);
            pols[setE][i] = fr.zero();
        }
/*
        if (l.setE == 1) {
            pols.main.setE[i]=Fr.one;
            [pols.main.E0[i+1], pols.main.E1[i+1], pols.main.E2[i+1], pols.main.E3[i+1]] = [op0, op1, op2, op3];
        } else {
            pols.main.setE[i]=Fr.zero;
            [pols.main.E0[i+1], pols.main.E1[i+1], pols.main.E2[i+1], pols.main.E3[i+1]] = [pols.main.E0[i], pols.main.E1[i], pols.main.E2[i], pols.main.E3[i]];
        }
*/
        if (l["setSR"]==1) {
            fr.copy(pols[SR][i+1],op0);
            pols[setSR][i] = fr.one();
        } else {
            fr.copy(pols[SR][i+1],pols[SR][i]);
            pols[setSR][i] = fr.zero();
        }
/*
        if (l.setSR == 1) {
            pols.main.setSR[i]=Fr.one;
            pols.main.SR[i+1] = op0;
        } else {
            pols.main.setSR[i]=Fr.zero;
            pols.main.SR[i+1] = pols.main.SR[i];
        }
*/
        if (l["setCTX"]==1) {
            fr.copy(pols[CTX][i+1],op0);
            pols[setCTX][i] = fr.one();
        } else {
            fr.copy(pols[CTX][i+1],pols[CTX][i]);
            pols[setCTX][i] = fr.zero();
        }
/*
        if (l.setCTX == 1) {
            pols.main.setCTX[i]=Fr.one;
            pols.main.CTX[i+1] = op0;
        } else {
            pols.main.setCTX[i]=Fr.zero;
            pols.main.CTX[i+1] = pols.main.CTX[i];
        }
*/
        if (l["setSP"]==1) {
            fr.copy(pols[SP][i+1],op0);
            pols[setSP][i] = fr.one();
        } else {
            fr.copy(pols[SP][i+1],pols[SP][i]);
            pols[setSP][i] = fr.zero();
            if ((l["inc"]==1)&&(l["isStack"]==1)){
                RawFr::Element inc;
                fr.fromUI(inc,l["inc"]);
                fr.add(pols[SP][i+1], pols[SP][i+1], inc);
            }
            // TODO: Use variables for inc, etc., to avoid parsing twice the same JSON element
        }
/*
        if (l.setSP == 1) {
            pols.main.setSP[i]=Fr.one;
            pols.main.SP[i+1] = op0;
        } else {
            pols.main.setSP[i]=Fr.zero;
            pols.main.SP[i+1] = pols.main.SP[i];
            if ((l.inc==1)&&(l.isStack==1)) pols.main.SP[i+1] = Fr.add(pols.main.SP[i+1], Fr.e(l.inc))
        }
*/
        if (l["setPC"]==1) {
            fr.copy(pols[PC][i+1],op0);
            pols[setPC][i] = fr.one();
        } else {
            fr.copy(pols[PC][i+1],pols[PC][i]);
            pols[setPC][i] = fr.zero();
            if ((l["inc"]==1)&&(l["isCode"]==1)) {
                RawFr::Element inc;
                fr.fromUI(inc,l["inc"]);
                fr.add(pols[PC][i+1], pols[PC][i+1], inc);
            }
            // TODO: Use variables for inc, etc., to avoid parsing twice the same JSON element
        }

/*
        if (l.setPC == 1) {
            pols.main.setPC[i]=Fr.one;
            pols.main.PC[i+1] = op0;
        } else {
            pols.main.setPC[i]=Fr.zero;
            pols.main.PC[i+1] = pols.main.PC[i];
            if ((l.inc==1)&&(l.isCode==1)) pols.main.PC[i+1] = Fr.add(pols.main.PC[i+1], Fr.e(l.inc))
        }
*/
        if (l["JMPC"]==1) {

        } else if (l["JMP"]==1) {

        } else {

        }
/*

        if (l.JMPC) {
            const o = fe2n(Fr, op0);
            if (o<0) {
                pols.main.isNeg[i]=Fr.one;
                pols.main.zkPC[i+1] = Fr.e(addr);
            } else {
                pols.main.isNeg=Fr.zero;
                pols.main.zkPC[i+1] = Fr.add(pols.main.zkPC[i], Fr.one);
            }
            pols.main.JMP[i] = Fr.zero;
            pols.main.JMPC[i] = Fr.one;
        } else if (l.JMP) {
            pols.main.isNeg[i]=Fr.zero;
            pols.main.zkPC[i+1] = Fr.e(addr)
            pols.main.JMP[i] = Fr.one;
            pols.main.JMPC[i] = Fr.zero;
        } else {
            pols.main.isNeg[i]=Fr.zero;
            pols.main.zkPC[i+1] = Fr.add(pols.main.zkPC[i], Fr.one);
            pols.main.JMP[i] = Fr.zero;
            pols.main.JMPC[i] = Fr.zero;
        }
*/
        uint64_t maxMemCalculated;
/*
        const mm = fe2n(Fr, pols.main.MAXMEM[i]);
        if (l.isMem) {
            if (addrRel>mm) {
                pols.main.isMaxMem[i] = Fr.one;
                maxMemCalculated = addrRel;
            } else {
                pols.main.isMaxMem[i] = Fr.zero;
                maxMemCalculated = mm;
            }
        } else {
            pols.main.isMaxMem[i] = Fr.zero;
            maxMemCalculated = mm;
        }
*/
        if (l["setMAXMEM"]==1) { // TODO: Should this be ==1 or as a bool like in setGAS bellow?
            pols[setMAXMEM][i] = fr.one();
            pols[MAXMEM][i+1] = op0;
        } else {
            pols[setMAXMEM][i] = fr.zero();
            fr.fromUI(pols[MAXMEM][i+1],maxMemCalculated);
        }
/*
        if (l.setMAXMEM) {
            pols.main.setMAXMEM[i] = Fr.one;
            pols.main.MAXMEM[i+1] = op0;
        } else {
            pols.main.setMAXMEM[i] = Fr.zero;
            pols.main.MAXMEM[i+1] = Fr.e(maxMemCalculated);
        }
*/
        if (l["setGAS"]==1) {
            pols[setGAS][i] = fr.one();
            pols[GAS][i+1] = op0;
        } else {
            pols[setGAS][i] = fr.zero();
            pols[GAS][i+1] = pols[GAS][i];
        }
/*
        if (l.setGAS == 1) {
            pols.main.setGAS[i]=Fr.one;
            pols.main.GAS[i+1] = op0;
        } else {
            pols.main.setGAS[i]=Fr.zero;
            pols.main.GAS[i+1] = pols.main.GAS[i];
        }

*/
        if (l["mRD"]==1) {
            pols[mRD][i] = fr.one();
        } else {
            pols[mRD][i] = fr.zero();
        }
/*
        if (l.mRD) {
            pols.main.mRD[i] = Fr.one;
        } else {
            pols.main.mRD[i] = Fr.zero;
        }
*/
/*
        if (l.mWR) {
            pols.main.mWR[i] = Fr.one;
            ctx.mem[addr] = [op0, op1, op2, op3];
        } else {
            pols.main.mWR[i] = Fr.zero;
        }
*/
        if (l["sRD"]==1) {
            pols[sRD][i] = fr.one();
        } else {
            pols[sRD][i] = fr.zero();
        }
/*
        if (l.sRD) {
            pols.main.sRD[i] = Fr.one;
        } else {
            pols.main.sRD[i] = Fr.zero;
        }
*/
/*
        if (l.sWR) {
            pols.main.sWR[i] = Fr.one;
            if (typeof ctx.sto[addr] === "undefined" ) throw new Error(`Storage not initialized: ${ctx.ln}`);
            ctx.sto[ fe2bns([pols.A0[i], pols.A1[i], pols.A2[i], pols.A3[i]]) ] = op;
        } else {
            pols.main.sWR[i] = Fr.zero;
        }
*/
        if (l["hashRD"]==1) {
            pols[hashRD][i] = fr.one();
        } else {
            pols[hashRD][i] = fr.zero();
        }
/*
        if (l.hashRD) {
            pols.main.hashRD[i] = Fr.one;
        } else {
            pols.main.hashRD[i] = Fr.zero;
        }
*/
/*
        if (l.hashWR) {
            pols.main.hashWR[i] = Fr.one;

            size = fe2n(Fr, ctx.D[0]);
            if ((size<0) || (size>32)) throw new Error(`Invalid size for hash: ${ctx.ln}`);
            const a = fea2bn(Fr, [op0, op1, op2, op3]);
            if (!ctx.hash[addr]) ctx.hash[addr] = { data: [] } ;
            for (let i=0; i<size; i++) {
                ctx.hash[addr].data.push(Scalar.toNumber(Scalar.band( Scalar.shr( a, (size-i -1)*8 ) , Scalar.e("0xFF"))));
            }
        } else {
            pols.main.hashWR[i] = Fr.zero;
        }

        if (l.hashE) {
            pols.main.hashE[i] = Fr.one;
            
            ctx.hash[addr].result = ethers.utils.keccak256(ethers.utils.hexlify(ctx.hash[addr].data));
        } else {
            pols.main.hashE[i] = Fr.zero;
        }
*/
        if (l["ecRecover"]==1) { // TODO: Should we check that type is boolean?  Or treat it as an unsigned int?
            pols[ecRecover][i] = fr.one();
        } else {
            pols[ecRecover][i] = fr.zero();
        }
/*
        if (l.ecRecover) {
            pols.main.ecRecover[i] = Fr.one;
        } else {
            pols.main.ecRecover[i] = Fr.zero;
        }
*/
        if (l["arith"]==1) {
            pols[arith][i] = fr.one();
        } else {
            pols[arith][i] = fr.zero();
        }
/*
        if (l.arith) {
            pols.main.arith[i] = Fr.one;
        } else {
            pols.main.arith[i] = Fr.zero;
        }
*/
        if (l["shl"]==1) {
            pols[shl][i] = fr.one();
        } else {
            pols[shl][i] = fr.zero();
        }
/*
        if (l.shl) {
            pols.main.shl[i] = Fr.one;
        } else {
            pols.main.shl[i] = Fr.zero;
        }
*/
        if (l["shr"]==1) {
            pols[shr][i] = fr.one();
        } else {
            pols[shr][i] = fr.zero();
        }
/*
        if (l.shr) {
            pols.main.shr[i] = Fr.one;
        } else {
            pols.main.shr[i] = Fr.zero;
        }
*/
        if (l["bin"]==1) {
            pols[bin][i] = fr.one();
        } else {
            pols[bin][i] = fr.zero();
        }
/*
        if (l.bin) {
            pols.main.bin[i] = Fr.one;
        } else {
            pols.main.bin[i] = Fr.zero;
        }
*/
        if (l["comparator"]==1) {
            pols[comparator][i] = fr.one();
        } else {
            pols[comparator][i] = fr.zero();
        }
/*
        if (l.comparator) {
            pols.main.comparator[i] = Fr.one;
        } else {
            pols.main.comparator[i] = Fr.zero;
        }
*/
        if (l["opcodeRomMap"]==1) {
            pols[opcodeRomMap][i] = fr.one();
        } else {
            pols[opcodeRomMap][i] = fr.zero();
        }
/*        
        if (l.opcodeRomMap) {
            pols.main.opcodeRomMap[i] = Fr.one;
        } else {
            pols.main.opcodeRomMap[i] = Fr.zero;
        }
*/
        if (l["cmdAfter"].is_array()) {
            for (json::iterator it = l["cmdAfter"].begin(); it != l["cmdAfter"].end(); ++it) {
                std::cout << "cmdAfter: " << *it << '\n';
                evalCommand(ctx,*it);
            }
        }
/*
        if (l.cmdAfter) {
            for (let j=0; j< l.cmdAfter.length; j++) {
                evalCommand(ctx, l.cmdAfter[j]);
            }
        }
        */

    }
}

void createPols(tExecutorOutput &pols, json &pil)
{
    // PIL JSON file must contain a nCommitments key at the root level
    if ( !pil.contains("nCommitments") ||
         !pil["nCommitments"].is_number_unsigned() )
    {
        cerr << "Error: nCommitments key not found in PIL JSON file" << endl;
        exit(-1);
    }
    uint64_t nCommitments;
    nCommitments = pil["nCommitments"];
    cout << nCommitments << endl;

    // PIL JSON file must contain a references structure at the root level
    if ( !pil.contains("references") ||
         !pil["references"].is_structured() )
    {
        cerr << "Error: references key not found in PIL JSON file" << endl;
        exit(-1);
    }

    // Iterate the PIL JSON references array
    json references = pil["references"];
    //json kk = pil["kk"];
    //cout << "kk.is_object()=" << kk.is_object() << endl;
    //cout << "kk.is_structured()=" << kk.is_structured() << endl;
    //cout << "references.is_object()=" << references.is_object() << endl;
    //cout << "references.is_structured()=" << references.is_structured() << endl;
    uint64_t addedPols = 0;
    for (json::iterator it = references.begin(); it != references.end(); ++it) {
        string key = it.key();
        json value = it.value();
        if ( value.is_object() &&
             value.contains("type") && 
             value["type"].is_string() &&
             value.contains("id") &&
             value["id"].is_number_unsigned() ) 
        {
            string type = it.value()["type"];
            uint64_t id = it.value()["id"];
            //cout << key << " - " << type << " - " << id << endl;
            if (type=="cmP") { // TODO: check that there are exactly 2 substrings
                /*string nameSpace;
                string namePol;
                istringstream iss(key);
                getline(iss,nameSpace,'.');
                getline(iss,namePol,'.');
                if (nameSpace=="main") continue;
                uint64_t numPol = polmap(namePol.c_str());
                cout << "    " << nameSpace << " - " << namePol << " - " << type << " - " << id << " - " << numPol << endl;*/
                if (id>=NPOLS)
                {
                    cerr << "Error: polynomial " << key << " id(" << id << ") >= NPOLS(" << NPOLS << ")" << endl;
                    exit(-1);
                }
                addPol(key,id);
                addedPols++;
                cout << "Added polynomial " << addedPols << ": " << key << " with ID " << id << endl;
            }
        }

    }
}

/* 
    This function creates an array of polynomials and a mapping that maps the reference name in pil to the polynomial
*/
/*
function createPols(pil) {
    polsArray = [];
    pols = {};
    for (let i=0; i<pil.nCommitments; i++) polsArray.push([]);
    for (refName in pil.references) {
        if (pil.references.hasOwnProperty(refName)) {
            ref = pil.references[refName];
            if (ref.type == "cmP") {
                [nameSpace, namePol] = refName.split(".");
                if (!pols[nameSpace]) pols[nameSpace] = {};
                pols[nameSpace][namePol] = polsArray[ref.id];
            }
        }
    }

    return [pols, polsArray];
}*/

void initState(RawFr &fr, tExecutorOutput &pols)
{
    // Register value initial parameters
    pols[A0][0] = fr.zero();
    pols[A1][0] = fr.zero();
    pols[A2][0] = fr.zero();
    pols[A3][0] = fr.zero();
    pols[B0][0] = fr.zero();
    pols[B1][0] = fr.zero();
    pols[B2][0] = fr.zero();
    pols[B3][0] = fr.zero();
    pols[C0][0] = fr.zero();
    pols[C1][0] = fr.zero();
    pols[C2][0] = fr.zero();
    pols[C3][0] = fr.zero();
    pols[D0][0] = fr.zero();
    pols[D1][0] = fr.zero();
    pols[D2][0] = fr.zero();
    pols[D3][0] = fr.zero();
    pols[E0][0] = fr.zero();
    pols[E1][0] = fr.zero();
    pols[E2][0] = fr.zero();
    pols[E3][0] = fr.zero();
    pols[SR][0] = fr.zero();
    pols[CTX][0] = fr.zero();
    pols[SP][0] = fr.zero();
    pols[PC][0] = fr.zero();
    pols[MAXMEM][0] = fr.zero();
    pols[GAS][0] = fr.zero();
    pols[zkPC][0] = fr.zero();
}

RawFr::Element eval_number(tContext &ctx, json tag);
RawFr::Element eval_getReg(tContext &ctx, json tag);
RawFr::Element eval_declareVar(tContext &ctx, json tag);
RawFr::Element eval_setVar(tContext &ctx, json tag);
RawFr::Element eval_getVar(tContext &ctx, json tag);
RawFr::Element eval_add(tContext &ctx, json tag);
RawFr::Element eval_sub(tContext &ctx, json tag);
RawFr::Element eval_neg(tContext &ctx, json tag);
RawFr::Element eval_mul(tContext &ctx, json tag);
RawFr::Element eval_div(tContext &ctx, json tag);
RawFr::Element eval_mod(tContext &ctx, json tag);

RawFr::Element evalCommand(tContext &ctx, json tag) {
    string op = tag["op"]; // TODO: error if not present or different type
    if (op=="number") {
        return eval_number(ctx, tag);
    } else if (op=="declareVar") {
        return eval_declareVar(ctx, tag);
    } else if (op=="setVar") {
        return eval_setVar(ctx, tag);
    } else if (op=="getVar") {
        return eval_getVar(ctx, tag);
    } else if (op=="getReg") {
        return eval_getReg(ctx, tag);
    } else if (op=="functionCall") {
        //return eval_functionCall(ctx, tag);
    } else if (op=="add") {
        return eval_add(ctx, tag);
    } else if (op=="sub") {
        return eval_sub(ctx, tag);
    } else if (op=="neg") {
        return eval_neg(ctx, tag);
    } else if (op=="mul") {
        //return eval_mul(ctx, tag);
    } else if (op=="div") {
        return eval_div(ctx, tag);
    } else if (op=="mod") {
        return eval_mod(ctx, tag);
    }
    cerr << "Error: evalCommand() found invalid operation: " << op << endl;
    exit(-1);
}

/*function evalCommand(ctx, tag) {
    if (tag.op == "number") {
        return eval_number(ctx, tag);
    } else if (tag.op == "declareVar") {
        return eval_declareVar(ctx, tag);
    } else if (tag.op == "setVar") {
        return eval_setVar(ctx, tag);
    } else if (tag.op == "getVar") {
        return eval_getVar(ctx, tag);
    } else if (tag.op == "getReg") {
        return eval_getReg(ctx, tag);
    } else if (tag.op == "functionCall") {
        return eval_functionCall(ctx, tag);
    } else if (tag.op == "add") {
        return eval_add(ctx, tag);
    } else if (tag.op == "sub") {
        return eval_sub(ctx, tag);
    } else if (tag.op == "neg") {
        return eval_neg(ctx, tag);
    } else if (tag.op == "mul") {
        return eval_mul(ctx, tag);
    } else if (tag.op == "div") {
        return eval_div(ctx, tag);
    } else if (tag.op == "mod") {
        return eval_mod(ctx, tag);
    } else {
        throw new Error(`Invalid operation: ${ctx.ln}`);
    }

}*/

RawFr::Element eval_number(tContext &ctx, json tag) {
    RawFr::Element num;
    ctx.pFr->fromUI(num,tag["num"]); // TODO: Check existence and type of num element
    return num;
}

/*
function eval_number(ctx, tag) {
    return Scalar.e(tag.num);
}

*/
string eval_left(tContext &ctx, json tag);

RawFr::Element eval_setVar(tContext &ctx, json tag)
{
    // Check that tag contains a values array
    if (!tag.contains("values") || !tag["values"].is_array()) {
        cerr << "Error: eval_setVar() could not find array values in tag" << tag << endl;
        exit(-1);
    }

    // Get varName from the first element in values
    string varName = eval_left(ctx,tag["values"][0]);

    // Check that this variable exists
    if ( ctx.vars.find(varName) == ctx.vars.end() ) {
        cerr << "Error: eval_setVar() Undefined variable: " << varName << endl;
        exit(-1);
    }

    ctx.vars[varName] = evalCommand(ctx, tag["values"][1]);

    cout << "Set variable: " << varName << endl;

    return ctx.vars[varName];
}

/*
function eval_setVar(ctx, tag) {

    const varName = eval_left(ctx, tag.values[0]);

    if (typeof ctx.vars[varName] == "undefined") throw new Error(`Vaiable not defined ${ctx.ln}`);

    ctx.vars[varName] = evalCommand(ctx, tag.values[1]);
    return ctx.vars[varName];
}
*/
string eval_left(tContext &ctx, json tag)
{
    string op = tag["op"];
    if (op == "declareVar") {
        eval_declareVar(ctx, tag);
        return tag["varName"];
    } else if (op == "getVar") {
        return tag["varName"];
    }
    cerr << "Error: invalid left expression, op: " << op << "ln: " << ctx.ln << endl;
    exit(-1);
}

/*
function eval_left(ctx, tag) {
    if (tag.op == "declareVar") {
        eval_declareVar(ctx, tag);
        return tag.varName;
    } else if (tag.op == "getVar") {
        return tag.varName;
    } else {
        throw new Error(`Invalid left expression: ${ctx.ln}`);
    }
}*/
RawFr::Element eval_declareVar(tContext &ctx, json tag)
{
    // Get the variable name
    string varName = tag["varName"]; // TODO: Check existence and type

    // Check that this variable does not exists
    if ( ctx.vars.find(varName) != ctx.vars.end() ) {
        cerr << "Error: eval_declareVar() Variable already declared " << varName << endl;
        exit(-1);
    }

    // Create the new variable with a zero value
    ctx.vars[varName] = ctx.pFr->zero(); // TODO: Should it be Scalar.e(0)?

    cout << "Declare variable: " << varName << endl;

    return ctx.vars[varName];
}
/*
function eval_declareVar(ctx, tag) {
    if (typeof ctx.vars[tag.varName] != "undefined") throw new Error(`Vaiable already declared: ${ctx.ln}`);
    ctx.vars[tag.varName] = Scalar.e(0);
    return ctx.vars[tag.varName];
}
*/
RawFr::Element eval_getVar(tContext &ctx, json tag)
{
    // Get the variable name
    string varName = tag["varName"]; // TODO: Check existence and type

    // Check that this variable exists
    if ( ctx.vars.find(varName) == ctx.vars.end() ) {
        cerr << "Error: eval_getVar() Undefined variable: " << varName << endl;
        exit(-1);
    }

    cout << "Get variable: " << varName << endl;

    return ctx.vars[varName];
}
/*
function eval_getVar(ctx, tag) {
    if (typeof ctx.vars[tag.varName] == "undefined") throw new Error(`Vaiable not defined ${ctx.ln}`);
    return ctx.vars[tag.varName];
}
*/
RawFr::Element eval_getReg(tContext &ctx, json tag) {
    if (tag["regName"]=="A") { // TODO: Consider using a string local variable to avoid searching every time
        //return fea2bn(ctx.pFr,ctx.pols[]);
        return ctx.pFr->zero(); // TODO: migrate
    } else if (tag["regName"]=="B") {
        return ctx.pFr->zero(); // TODO: migrate
    } else if (tag["regName"]=="C") {
        return ctx.pFr->zero(); // TODO: migrate
    } else if (tag["regName"]=="D") {
        return ctx.pFr->zero(); // TODO: migrate
    } else if (tag["regName"]=="E") {
        return ctx.pFr->zero(); // TODO: migrate
    } else if (tag["regName"]=="SR") {
        return (*ctx.pPols)[SR][ctx.step];
    } else if (tag["regName"]=="CTX") {
        return (*ctx.pPols)[CTX][ctx.step];
    } else if (tag["regName"]=="SP") {
        return (*ctx.pPols)[SP][ctx.step];
    } else if (tag["regName"]=="PC") {
        return (*ctx.pPols)[PC][ctx.step];
    } else if (tag["regName"]=="MAXMEM") {
        return (*ctx.pPols)[MAXMEM][ctx.step];
    } else if (tag["regName"]=="GAS") {
        return (*ctx.pPols)[GAS][ctx.step];
    } else if (tag["regName"]=="zkPC") {
        return (*ctx.pPols)[zkPC][ctx.step];
    }
    cerr << "Error: eval_getReg() Invalid register: " << tag["regName"] << ": " << ctx.ln << endl;
    exit(-1);
}
/*
function eval_getReg(ctx, tag) {
    if (tag.regName == "A") {
        return fea2bn(ctx.Fr, ctx.A);
    } else if (tag.regName == "B") {
        return fea2bn(ctx.Fr, ctx.B);
    } else if (tag.regName == "C") {
        return fea2bn(ctx.Fr, ctx.C);
    } else if (tag.regName == "D") {
        return fea2bn(ctx.Fr, ctx.D);
    } else if (tag.regName == "E") {
        return fea2bn(ctx.Fr, ctx.E);
    } else if (tag.regName == "SR") {
        return ctx.SR;
    } else if (tag.regName == "CTX") {
        return ctx.CTX;
    } else if (tag.regName == "SP") {
        return ctx.SP;
    } else if (tag.regName == "PC") {
        return ctx.PC;
    } else if (tag.regName == "MAXMEM") {
        return ctx.MAXMEM;
    } else if (tag.regName == "GAS") {
        return ctx.GAS;
    } else if (tag.regName == "zkPC") {
        return ctx.zkPC;
    } else {
        throw new Error(`Invalid register ${tag.regName}:  ${ctx.ln}`);
    }
}
*/
RawFr::Element eval_add(tContext &ctx, json tag)
{
    RawFr::Element a = evalCommand(ctx,tag["values"][0]);
    RawFr::Element b = evalCommand(ctx,tag["values"][1]);
    RawFr::Element r;
    ctx.pFr->add(r,a,b);
    return r;
}
/*
function eval_add(ctx, tag) {
    const a = evalCommand(ctx, tag.values[0]);
    const b = evalCommand(ctx, tag.values[1]);
    return Scalar.add(a,b);
}*/
RawFr::Element eval_sub(tContext &ctx, json tag)
{
    RawFr::Element a = evalCommand(ctx,tag["values"][0]);
    RawFr::Element b = evalCommand(ctx,tag["values"][1]);
    RawFr::Element r;
    ctx.pFr->sub(r,a,b);
    return r;
}
/*
function eval_sub(ctx, tag) {
    const a = evalCommand(ctx, tag.values[0]);
    const b = evalCommand(ctx, tag.values[1]);
    return Scalar.sub(a,b);
}*/
RawFr::Element eval_neg(tContext &ctx, json tag)
{
    RawFr::Element a = evalCommand(ctx,tag["values"][0]);
    RawFr::Element r;
    ctx.pFr->neg(r,a);
    return r;
}
/*
function eval_neg(ctx, tag) {
    const a = evalCommand(ctx, values[0]);
    return Scalar.neg(a);
}*/

/*
function eval_mul(ctx, tag) {
    const a = evalCommand(ctx, tag.values[0]);
    const b = evalCommand(ctx, tag.values[1]);
    return Sacalar.and(Scalar.mul(a,b), Mask256);
}*/
RawFr::Element eval_div(tContext &ctx, json tag)
{
    RawFr::Element a = evalCommand(ctx,tag["values"][0]);
    RawFr::Element b = evalCommand(ctx,tag["values"][1]);
    RawFr::Element r;
    ctx.pFr->div(r,a,b);
    return r;
}
/*
function eval_div(ctx, tag) {
    const a = evalCommand(ctx, tag.values[0]);
    const b = evalCommand(ctx, tag.values[1]);
    return Sacalar.div(a,b);
}*/
RawFr::Element eval_mod(tContext &ctx, json tag)
{
    RawFr::Element a = evalCommand(ctx,tag["values"][0]);
    RawFr::Element b = evalCommand(ctx,tag["values"][1]);
    RawFr::Element r;
    //ctx.pFr->mod(r,a,b); // TODO: Migrate.  This method does not exist in C.
    return r;
}
/*
function eval_mod(ctx, tag) {
    const a = evalCommand(ctx, tag.values[0]);
    const b = evalCommand(ctx, tag.values[1]);
    return Sacalar.mod(a,b);
}
*/
RawFr::Element eval_functionCall(tContext &ctx, json tag) {
    string funcName = tag["funcName"]; // TODO: Check existance and type
    if (funcName == "getGlobalHash") {
        //return eval_getGlobalHash(ctx, tag);
    } else if (funcName == "getOldStateRoot") {
        //return eval_getOldStateRoot(ctx, tag);
    } else if (funcName == "getNewStateRoot") {
        //return eval_getNewStateRoot(ctx, tag);
    } else if (funcName == "getNTxs") {
        //return eval_getNTxs(ctx, tag);
    } else if (funcName == "getRawTx") {
        //return eval_getRawTx(ctx, tag);
    } else if (funcName == "getTxSigR") {
        //return eval_getTxSigR(ctx, tag);
    } else if (funcName == "getTxSigS") {
        //return eval_getTxSigS(ctx, tag);
    } else if (funcName == "getTxSigV") {
        //return eval_getTxSigV(ctx, tag);
    } else if (funcName == "getSequencerAddr") {
        //return eval_getSequencerAddr(ctx, tag);
    } else if (funcName == "getChainId") {
        //return eval_getChainId(ctx, tag);
    }
    cerr << "Error: eval_functionCall() function not defined: " << funcName << " line: " << ctx.ln << endl;
    exit(-1); 
}

/*
function eval_functionCall(ctx, tag) {
    if (tag.funcName == "getGlobalHash") {
        return eval_getGlobalHash(ctx, tag);
    } else if (tag.funcName == "getOldStateRoot") {
        return eval_getOldStateRoot(ctx, tag);
    } else if (tag.funcName == "getNewStateRoot") {
        return eval_getNewStateRoot(ctx, tag);
    } else if (tag.funcName == "getNTxs") {
        return eval_getNTxs(ctx, tag);
    } else if (tag.funcName == "getRawTx") {
        return eval_getRawTx(ctx, tag);
    } else if (tag.funcName == "getTxSigR") {
        return eval_getTxSigR(ctx, tag);
    } else if (tag.funcName == "getTxSigS") {
        return eval_getTxSigS(ctx, tag);
    } else if (tag.funcName == "getTxSigV") {
        return eval_getTxSigV(ctx, tag);
    } else if (tag.funcName == "getSequencerAddr") {
        return eval_getSequencerAddr(ctx, tag);
    } else if (tag.funcName == "getChainId") {
        return eval_getChainId(ctx, tag);
    } else {
        throw new Error(`function not defined ${tag.funcName}:  ${ctx.ln}`);
    }
}
*/
/*

function eval_getGlobalHash(ctx, tag) {
    if (tag.params.length != 0) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    return bn2bna(ctx.Fr, Scalar.e(ctx.globalHash));
}

function eval_getSequencerAddr(ctx, tag) {
    if (tag.params.length != 0) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    return bn2bna(ctx.Fr, Scalar.e(ctx.input.sequencerAddr));
}

function eval_getChainId(ctx, tag) {
    if (tag.params.length != 0) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    return [ctx.Fr.e(ctx.input.chainId), ctx.Fr.zero, ctx.Fr.zero, ctx.Fr.zero];
}

function eval_getOldStateRoot(ctx, tag) {
    if (tag.params.length != 0) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    return [ctx.Fr.e(ctx.input.oldStateRoot), ctx.Fr.zero, ctx.Fr.zero, ctx.Fr.zero];
}

function eval_getNewStateRoot(ctx, tag) {
    if (tag.params.length != 0) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    return [ctx.Fr.e(ctx.input.newStateRoot), ctx.Fr.zero, ctx.Fr.zero, ctx.Fr.zero];
}

function eval_getNTxs(ctx, tag) {
    if (tag.params.length != 0) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    return [ctx.Fr.e(ctx.pTxs.length), ctx.Fr.zero, ctx.Fr.zero, ctx.Fr.zero];
}

function eval_getRawTx(ctx, tag) {
    if (tag.params.length != 3) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    const txId = Number(evalCommand(ctx,tag.params[0]));
    const offset = Number(evalCommand(ctx,tag.params[1]));
    const len = Number(evalCommand(ctx,tag.params[2]));
    let d = "0x" +ctx.pTxs[txId].signData.slice(2+offset*2, 2+offset*2 + len*2);
    if (d.length == 2) d = d+'0';
    return bn2bna(ctx.Fr, Scalar.e(d));
}

function eval_getTxSigR(ctx, tag) {
    if (tag.params.length != 1) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    const txId = Number(evalCommand(ctx,tag.params[0]));
    return bn2bna(ctx.Fr, Scalar.e(ctx.pTxs[txId].signature.r));
}

function eval_getTxSigS(ctx, tag) {
    if (tag.params.length != 1) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    const txId = Number(evalCommand(ctx,tag.params[0]));
    return bn2bna(ctx.Fr, Scalar.e(ctx.pTxs[txId].signature.s));
}

function eval_getTxSigV(ctx, tag) {
    if (tag.params.length != 1) throw new Error(`Invalid number of parameters function ${tag.funcName}: ${ctx.ln}`)
    const txId = Number(evalCommand(ctx,tag.params[0]));
    return bn2bna(ctx.Fr, Scalar.e(ctx.pTxs[txId].signature.v));
}
*/

void preprocessTxs(tContext &ctx, json &input)
{
    // Input JSON file must contain a oldStateRoot key at the root level
    if ( !input.contains("oldStateRoot") ||
         !input["oldStateRoot"].is_string() )
    {
        cerr << "Error: oldStateRoot key not found in input JSON file" << endl;
        exit(-1);
    }
    string oldStateRoot = input["oldStateRoot"];
    cout << "preprocessTxs(): oldStateRoot=" << oldStateRoot << endl;

    // Input JSON file must contain a oldStateRoot key at the root level
    if ( !input.contains("newStateRoot") ||
         !input["newStateRoot"].is_string() )
    {
        cerr << "Error: newStateRoot key not found in input JSON file" << endl;
        exit(-1);
    }
    string newStateRoot = input["newStateRoot"];
    cout << "preprocessTxs(): newStateRoot=" << newStateRoot << endl;

    // Input JSON file must contain a sequencerAddr key at the root level
    if ( !input.contains("sequencerAddr") ||
         !input["sequencerAddr"].is_string() )
    {
        cerr << "Error: sequencerAddr key not found in input JSON file" << endl;
        exit(-1);
    }
    string sequencerAddr = input["sequencerAddr"];
    cout << "preprocessTxs(): sequencerAddr=" << sequencerAddr << endl;

    // Input JSON file must contain a chainId key at the root level
    if ( !input.contains("chainId") ||
         !input["chainId"].is_number_unsigned() )
    {
        cerr << "Error: chainId key not found in input JSON file" << endl;
        exit(-1);
    }
    uint64_t chainId = input["chainId"];
    cout << "preprocessTxs(): chainId=" << chainId << endl;

    // Input JSON file must contain a txs structure at the root level
    if ( !input.contains("txs") ||
         !input["txs"].is_array() )
    {
        cerr << "Error: txs key not found in input JSON file" << endl;
        exit(-1);
    }
    vector<string> txs = input["txs"]; // TODO: check that all array values are strings
    for (std::vector<string>::iterator it = txs.begin() ; it != txs.end(); ++it)
    {
        cout << "preprocessTxs(): tx=" << *it << endl;
    }

}
/*
function preprocessTxs(ctx) {
    ctx.pTxs = [];
    const d = [];
    d.push(ethers.utils.hexZeroPad(ethers.utils.hexlify(ethers.BigNumber.from(ctx.input.oldStateRoot)), 32));
    d.push(ethers.utils.hexZeroPad(ethers.utils.hexlify(ethers.BigNumber.from(ctx.input.newStateRoot)), 32));
    for (let i=0; i<ctx.input.txs.length; i++) {
        const rtx = ethers.utils.RLP.decode(ctx.input.txs[i]);
        const chainId = (Number(rtx[6]) - 35) >> 1;
        const sign = Number(rtx[6])  & 1;
        const e =[rtx[0], rtx[1], rtx[2], rtx[3], rtx[4], rtx[5], ethers.utils.hexlify(chainId), "0x", "0x"];
        const signData = ethers.utils.RLP.encode( e );
        ctx.pTxs.push({
            signData: signData,
            signature: {
                r: rtx[7],k
                s: rtx[8],
                v: sign + 26
            }
        });
        d.push(signData);
    }
    ctx.globalHash = ethers.utils.keccak256(ctx.globalHash = ethers.utils.concat(d));
}*/

// Field Element to Number
int64_t fe2n(RawFr &fr, RawFr::Element &fe) {
    return 0;
    /*
    int64_t maxInt = 0x7FFFFFFF; //    const maxInt = Scalar.e("0x7FFFFFFF");
    int64_t minInt = fr.p // const minInt = Scalar.sub(Fr.p, Scalar.e("0x80000000"));

    const o = Fr.toObject(fe);
    if (Scalar.gt(o, maxInt)) {
        const on = Scalar.sub(Fr.p, o);
        if (Scalar.gt(o, minInt)) {
            return -Scalar.toNumber(on);
        }
        throw new Error(`Accessing a no 32bit value: ${ctx.ln}`);
    } else {
        return Scalar.toNumber(o);
    }*/
}

/*
// Field Element to Number
function fe2n(Fr, fe) {
    const maxInt = Scalar.e("0x7FFFFFFF");
    const minInt = Scalar.sub(Fr.p, Scalar.e("0x80000000"));
    const o = Fr.toObject(fe);
    if (Scalar.gt(o, maxInt)) {
        const on = Scalar.sub(Fr.p, o);
        if (Scalar.gt(o, minInt)) {
            return -Scalar.toNumber(on);
        }
        throw new Error(`Accessing a no 32bit value: ${ctx.ln}`);
    } else {
        return Scalar.toNumber(o);
    }
}
*/