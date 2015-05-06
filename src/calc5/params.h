#if !defined PARAMS_H
#define PARAMS_H
//------------------------------------
//  (c) Bartosz Milewski, 1994
//------------------------------------

#if 1
const int maxBuf = 100; // size of input buffer 
const int maxSymbols = 40; // size of symbol table 
const int maxSymLen = 80; // max length of symbol name 
#else
const int maxBuf = 8;     // size of input buffer
const int maxSymbols = 5;  // size of symbol table
const int maxSymLen = 4;   // max length of symbol name
#endif

#endif