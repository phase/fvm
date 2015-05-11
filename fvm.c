#include <stdio.h>

/* Registers */
#define NUM_REGS 4
unsigned regs[NUM_REGS];

/* Program Counter */
int pc = 0;

/* Fields */
int num = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;

void decode(int in){
  num = (in & 0xF000) >> 12;
  reg1     = (in & 0xF00 ) >>  8;
  reg2     = (in & 0xF0  ) >>  4;
  reg3     = (in & 0xF   );
  imm      = (in & 0xFF  );
}

/* Is the VM running? */
int running = 0;
