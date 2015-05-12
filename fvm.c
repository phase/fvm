#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_REGS 16
#define PROG_LENGTH 4096
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
      exit(EXIT_FAILURE);
  }
}

int prog[PROG_LENGTH];

int fetch(){
  return prog[pc++];
}

void showRegs(){
  int i;
  printf( "regs = " );
  for(i=0; i<NUM_REGS; i++ )
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
  if(argc < 1){
    printf("You need to specify a file!");
    exit(EXIT_FAILURE);
  }
  char ch;
  char chars[6];
  int charCount = 0;
  FILE *f;
  f = fopen(argv[1], "r");
  int i = 0, j = 0;
  while((ch = fgetc(f)) != EOF){
    if(ch == '\n') continue;
    printf("%c", ch);
    chars[i] = (char)ch;
    i++;
    if(i <= 6){
      i = 0;
      int hex[6];
      int m;
      for(m = 0; m < 6; m++){
        char buffer[1];
        buffer[0] = chars[m];
        hex[m] = (int) strtol(buffer, NULL, 16);
      }
      int k = (hex[2]<<24)|(hex[3]<<16)|(hex[4]<<8)|hex[5];
      prog[j++] = k;
      memset(&chars[0], 0, sizeof(chars));
    }
  }
  
  int l;
  for(l = 0; l < PROG_LENGTH; l++){
    printf("%X", prog[l]);
    if(prog[l] == 0) break;
  }
  printf("\n");

  running = 1;
  run();
  return 0;
}
