# FVM Instruction Set
Thr instruction set of the Flower Virtual Machine.

##Hex Formatting
The FVM reads each 6-bit set of numbers as an instruction. The instructions are listed below with their specified numbers. Here's the formatting for the numbers:
```fvm
00 0 0 0 00
|  | | | |- Data
|  | | |--- Register/Data
|  | |----- Register/Data
|  |------- Register/Data
|---------- Instruction
```
If there aren't enough arguments to fill 6 bits, fill the remaining bits with zeros.

###Variables
*This has to do with the inside architecture of the FVM. This is not needed to produce FVM bytecode or FVM hex code.*

Registers and Memory have their own arrays.
```c
#define NUM_REGS 16
unsigned regs[NUM_REGS];
unsigned memory[0xFF];
```
There is also a program counter to keep track of where the program is.
```c
int pc = 0;
```

Each hex instruction has different variables for different parts of it.
```fvm
0 0  0  0  0  0
| |  |  |  |  |
-i-  n1 n2 n3 n4
     |  |  -l2-
     |  -l3- |
     -l4- |  |
     ---- w ----
```
These variables are used within the evaluation of each instruction.
```c   
void gto() {
    pc = l4;
}
```

##FVM Bytecode
###Notation
* Registers begin with `r`: `r0`
* Scalar values begin with `#`: `#100`
  * Hex scalar values begin with `$`: `$1a0`
* Memory addresses begin with `@`: `@100`

###Instructions
* `reg` : Register : 1 bit
* `num` : Number : 2 bits
* `mem` : Memory Address : 3 bits
* `prg` : Step nunmber in the program : 3 bits

Number (in hex)| Syntax | Hex Example | Description
-------|--------|-------------|------------
0 | `stp`                     | 000000 | Stops the program
1 | `ldi <reg> <num>`         | 010640 | Load number to register
2 | `rst <reg>`               | 025000 | Reset register to zero
3 | `gto <num>`               | 037700 | Go to the number of the program counter
4 | `add <reg> <reg> <reg>`   | 041230 | Add value in register one to value in register two and put it in register three
5 | `sub <reg> <reg> <reg>`   | 051230 | Subtract value in register one from value in register two and put it in register three
6 | `mul <reg> <reg> <reg>`   | 061230 | Multiply "
7 | `div <reg> <reg> <reg>`   | 071230 | Divide "
8 | `mod <reg> <reg> <reg>`   | 081230 | Modulus "
9 | `and <reg> <reg> <reg>`   | 091230 | AND the first two registers and store it in the second register
A | `or <reg> <reg> <reg>`    | 0A1230 | OR the first two registers and store it in the second register
B | `xor <reg> <reg> <reg>`   | 0B1230 | XOR the first two registers and store it in the second register
C | `not <reg> <reg> `        | 0C1100 | NOT the first register and store it in the second register
D | `shl <reg> <reg> <reg>`   | 0D1230 | Shift Left the first register by the second register's value
E | `shr <reg> <reg> <reg>`   | 0E1230 | Shift Right the first register by the second register's value
F | `str <reg> <mem>`         | 0F3FFE | Store the value in the register in the memory address
10 | `get <mem> <reg>`        | 10FFE2 | Get the value in the memory address and put it in the register
11 | `red <reg>`              | 11A000 | Read an input from the console and set it to the register
12 | `prt <reg>`              | 12A000 | Prints numeric value of the register
13 | `prc <reg>`              | 13A000 | Prints char value of the register
14 | `trn <reg> <reg>`        | 14AB00 | Transfers the value of the first register to the second register
15 | `bnz <reg> <num>`        | 15A001 | Branch if the number in the register is not equal to zero
16 | `biz <reg> <num>`        | 16A001 | Branch if the number in the register is equal to zero
17 | `neg <reg> <reg>`        | 17AB00 | Negate the number in the first register and store it in the second register
18 | `btc <reg> <reg>`        | 18AB00 | Two's Complement the number inthe first register and store it in the second register
