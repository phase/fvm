#include <stdio.h>

/* Registers */
#define NUM_REGS 4
unsigned regs[NUM_REGS];

/* Program Counter */
int pc = 0;

/* Fields */
int instruction = 0;
int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;

void decode(int in){
  instruction = (in & 0xF000) >> 12;
  reg1 = (in & 0xF00 ) >>  8;
  reg2 = (in & 0xF0  ) >>  4;
  reg3 = (in & 0xF   );
  imm = (in & 0xFF  );
}

/* Is the VM running? */
int running = 0;

void eval(){
  switch(instruction){
    case 0:
      running = 0;
      break;
    case 1:
      regs[reg1] = imm;
      break;
  }
}
