#include <stdio.h>

#define NUM_REGS 4
unsigned regs[NUM_REGS];
unsigned memory[4096];

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
  reg1 = (in & 0xF00) >>  8;
  reg2 = (in & 0xF0) >>  4;
  reg3 = (in & 0xF);
  imm = (in & 0xFF);
}

/* Is the VM running? */
int running = 0;

void eval(){
  switch(instruction){
    case 0: /*stp*/
      running = 0;
      break;
    case 1: /*ldi*/
      regs[reg1] = imm;
      break;
    case 2: /*rst*/
      regs[reg1] = 0;
      break;
    case 3: /*gto*/
      pc = imm;
      break;
    case 4: /*add*/
      regs[reg3] = regs[reg1] + regs[reg2];
      break;
    case 5: /*sub*/
      regs[reg3] = regs[reg1] - regs[reg2];
      break;
    case 6: /*mul*/
      regs[reg3] = regs[reg1] * regs[reg2];
      break;
    case 7: /*div*/
      regs[reg3] = regs[reg1] / regs[reg2];
      break;
    default:
      printf("Error: Instruction %n not found!", instruction);
      exit(1);
  }
}

int prog[] = { 0x1064, 0x11C8, 0x2201, 0x0000 };

int fetch(){
  return prog[pc++];
}

void run(){
  while(running){
    int i = fetch();
    decode(i);
    eval();
  }
}

int main(int argc, const char *argv[]){
  run();
  return 0;
}
