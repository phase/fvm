#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"

#define PROG_LENGTH 4096

unsigned int prog[PROG_LENGTH];

int comment = 0;

/* Gets all the information out of the instruction */
void decode(int in){
  instruction = (in & 0xFF0000) >> 16;
  n1 = (in & 0xF000) >> 12;
  n2 = (in & 0xF00) >>  8;
  n3 = (in & 0xF0) >>  4;
  n4 = (in & 0xF);
  l2 = (in & 0xFF);
  l3 = (in & 0xFF0) >> 4;
  l4 = (in & 0xFF00) >> 8;
  t1 = (in & 0xFFF);
  t2 = (in & 0xFFF0) >> 4;
  w = (in & 0x00FFFF);
  m1 = (in & 0xFFF0) >> 4;
  m2 = (in & 0xFFF);
}

void eval(){
    if (instruction > -1 && instruction < 25) {
        operations[instruction]();
    }
    else {
        error();
    }
}

int fetch(){
  return prog[pc++ - 1];
}

void showRegs(){
  int i;
  printf("regs = ");
  for(i = 0; i < NUM_REGS; i++)
    printf("%04X ", regs[i]);
  printf( "\n" );
}

void run(){
  while(running){
    /*showRegs();*/
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
  FILE *f;
  f = fopen(argv[1], "r");
  char ch;
  int i = 0, j = 0;
  char buffer[7];
  buffer[6] = '\0';
  while((ch = fgetc(f)) != EOF){
    if(ch == '\n'){
      comment = 0;
      continue;
    }
    if(ch == ' ' || comment != 0) continue;
    if(ch == ';'){
      comment = !comment;
      continue;
    }
    buffer[i++] = ch;
    if(i == 6) {
      i = 0;
      prog[j++] = (int)strtol(buffer, NULL, 16);
    }
  }

  int l;
  for(l = 0; l < PROG_LENGTH; l++){
    /*printf("%X\n", prog[l]);*/
    if(prog[l] == 0) break;
  }
  printf("\n");

  running = 1;
  run();
  return 0;
}
