#include <stdio.h>

#define NUM_REGS 4
unsigned regs[NUM_REGS];
unsigned memory[4096];

/* Program Counter */
int pc = 0;

/* Fields */
int instruction = 0;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int imm = 0;

void decode(int in){
  instruction = (in & 0xFF000) >> 16;
  n1 = (in & 0xF00) >>  8;
  n2 = (in & 0xF0) >>  4;
  n3 = (in & 0xF);
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
      regs[n1] = imm;
      break;
    case 2: /*rst*/
      regs[n1] = 0;
      break;
    case 3: /*gto*/
      pc = imm;
      break;
    case 4: /*add*/
      regs[n3] = regs[n1] + regs[n2];
      break;
    case 5: /*sub*/
      regs[n3] = regs[n1] - regs[n2];
      break;
    case 6: /*mul*/
      regs[n3] = regs[n1] * regs[n2];
      break;
    case 7: /*div*/
      regs[n3] = regs[n1] / regs[n2];
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
