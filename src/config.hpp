#ifndef CONFIG_HPP
#define CONFIG_HPP

#define NEVALUATIONS 65536 //1<<16, i.e. 1<<NBITS
#define NPOLS 85 //Up to 512 in the future
#define NCONSTPOLS 57
#define ARITY 4
#define NBITS 16
#define EXTENDED_BITS 1
#define MERKLE_ARITY 16

//#define LOG_STEPS
//#define LOG_INX
//#define LOG_ADDR
//#define LOG_ASSERT
//#define LOG_SETX
//#define LOG_JMP
//#define LOG_STORAGE
//#define LOG_MEMORY
//#define LOG_HASH
//#define LOG_POLS
//#define LOG_VARIABLES // If defined, logs variable declaration, get and set actions
//#define LOG_FILENAME // If defined, logs ROM compilation file name and line number
#define LOG_TIME // If defined, logs time differences to measure performance
//#define LOG_TXS
//#define LOG_SERVICE
//#define LOG_BME
//#define LOG_SCRIPT_OUTPUT
#define LOG_RPC_INPUT

#define DEBUG
#ifdef DEBUG
#define zkassert(a) {if (!(a)) {cerr << "Error: assert failed: " << (#a) << endl; exit(-1);}}
#else
#define zkassert(a)
#endif

//#define USE_LOCAL_STORAGE // If defined, use ctx.sto[], else, use smt.get()

/* Database defines */
#define DATABASE_USER "prover" //"test_user" //"hermez"
#define DATABASE_PASSWORD "V9FLqRCUNu6nakNV" //"test_password" //"polygon"
#define DATABASE_HOST "54.171.70.11" //"localhost"
#define DATABASE_NAME "test_db" //"polygon-hermez"
#define DATABASE_PORT 5432
#define DATABASE_TABLE_NAME "state.merkletree" // "state_merkletree"

/* Prover defines */
//#define PROVER_SAVE_STARK_PROOF_TO_DISK
//#define PROVER_SAVE_ZKIN_PROOF_TO_DISK
//#define PROVER_SAVE_PROOF_TO_DISK
//#define PROVER_SAVE_WITNESS_TO_DISK
//#define PROVER_USE_PROOF_GOOD_JSON
//#define PROVER_INJECT_ZKIN_JSON

#endif