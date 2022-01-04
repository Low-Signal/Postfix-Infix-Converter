#ifndef OPNUM_H 
#define OPNUM_H

#define register

#define SYM_NULL   0x0
#define SYM_NAME   0x1
#define SYM_INTEG  0x2
#define SYM_FLOAT  0x3
#define SYM_NUMBER 0x3

#define SYM_OPCODE 0x4 
#define SYM_ADD   0x4 
#define SYM_SUB   0x5 
#define SYM_MUL   0x6
#define SYM_DIV   0x7

#define SYM_ENDLN  0x8
#define SYM_INVAL  0x9

extern void set_input(int argc, char ** argv);
extern char * get_opnum(int *val);
#endif
