/*

   Copyright 2015 Jadon Fowler

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_REGS 16
#define PROG_LENGTH 4096
unsigned regs[NUM_REGS];
unsigned memory[0xFFF];
unsigned int prog[PROG_LENGTH];

/* Program Counter */
int pc = 0;

int comment = 0;

/* Fields */
int instruction = 0;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int l2 = 0;
int l3 = 0;
int l4 = 0;
int t1 = 0;
int t2 = 0;
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
  t1 = (in & 0xFFF);
  t2 = (in & 0xFFF0) >> 4;
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
      memory[t1] = regs[n1];
      break;
    case 16: /*get*/
      regs[n3] = memory[t2];
      break;
    case 17: /*red*/
      scanf("%d", &regs[n1]);
      break;
    case 18: /*prt*/
      printf("%d", regs[n1]);
      break;
    case 19: /*prc*/
      printf("%c", regs[n1]);
      break;
    case 20: /*trn*/
      regs[n2] = regs[n1];
      break;
    default:
      printf("Error: Instruction %X not found!", instruction);
      exit(EXIT_FAILURE);
  }
}

int fetch(){
  return prog[pc++];
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
    printf("%X\n", prog[l]);
    if(prog[l] == 0) break;
  }
  printf("\n");

  running = 1;
  run();
  return 0;
}
