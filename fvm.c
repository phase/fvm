#include <stdio.h>

#define NUM_REGS 16
unsigned regs[NUM_REGS];
unsigned memory[0xFF];

/* Program Counter */
int pc = 0;

/* Fields */
int instruction = 0;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int l2 = 0;
int l3 = 0;
int l4 = 0;
int w = 0;

void decode(int in){
  instruction = (in & 0xFF0000) >> 16;
  n1 = (in & 0xF000) >> 12;
  n2 = (in & 0xF00) >>  8;
  n3 = (in & 0xF0) >>  4;
  n4 = (in & 0xF);
  l2 = (in & 0xFF);
  l3 = (in & 0xFF0) >> 4;
  l4 = (in & 0xFF00) >> 8;
  w = (in & 0x00FFFF);
}

/* Is the VM running? */
int running = 0;

void eval(){
  switch(instruction){
    case 0: /*stp*/
      running = 0;
      break;
    case 1: /*ldi*/
      regs[n1] = l3;
      break;
    case 2: /*rst*/
      regs[n1] = 0;
      break;
    case 3: /*gto*/
      pc = l4;
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
    case 8: /*mod*/
      regs[n3] = regs[n1] % regs[n2];
      break;
    case 9: /*and*/
      regs[n3] = regs[n1] & regs[n2];
      break;
    case 10: /*or*/
      regs[n3] = regs[n1] | regs[n2];
      break;
    case 11: /*xor*/
      regs[n3] = regs[n1] ^ regs[n2];
      break;
    case 12: /*not*/
      regs[n2] = !regs[n1];
      break;
    case 13: /*shl*/
      regs[n3] = regs[n1] << regs[n2];
      break;
    case 14: /*shr*/
      regs[n3] = regs[n1] >> regs[n2];
      break;
    case 15: /*str*/
      memory[l3] = regs[n1];
      break;
    case 16: /*get*/
      regs[n3] = memory[l4];
      break;
    default:
      printf("Error: Instruction %X not found!", instruction);
      exit(1);
  }
}

int prog[] = { 0x010640, 0x011C80, 0x022010, 0x000000 };

int fetch(){
  return prog[pc++];
}

void showRegs(){
  int i;
  printf( "regs = " );
  for( i=0; i<NUM_REGS; i++ )
    printf( "%04X ", regs[ i ] );
  printf( "\n" );
}

void run(){
  while(running){
    showRegs();
    int i = fetch();
    decode(i);
    eval();
  }
}

int main(int argc, const char *argv[]){
  run();
  return 0;
}
