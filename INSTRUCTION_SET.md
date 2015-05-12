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
If there aren't enough argument sto fill 6 bits, fill the remaining bits with zeros.

###Variables
*This has to do with the inside architecture of the FVM. This is not needed to produce FVM bytecode or FVM hex code.*

There are many different variables in the FVM, each corresponding to a different number in each instruction.
```fvm
0 0  0  0  0  0
| |  |  |  |  |
-i-  n1 n2 n3 n4
     |  |  -l2-
     |  -l3-
     -l4-
     - w ------
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
* `mem` : Memory Address : 2 bits

Number | Syntax | Hex Example | Description
-------|--------|-------------|------------
0 | `stp`                     | 000000 | Stops the program
1 | `ldi <reg> <num>`         | 010640 | Load number to register
2 | `rst <reg>`               | 025000 | Reset register to zero
3 | `gto <num>`               | 037700 | Go to the number of the program counter
4 | `add <reg> <reg> <reg>`   | 041230 | Add value in register one to value in register two and put it in register three
5 | `sub <reg> <reg> <reg>`   | 051230 | Subtract value in register one from value in register two and put it in register three
6 | `mul <reg> <reg> <reg>`   | 061230 | Multiply "
7 | `div <reg> <reg> <reg>`   | 071230 | Divide "
8 | `and <reg> <reg> <reg>`   | 081230 | AND the first two registers and store it in the second register
9 | `or <reg> <reg> <reg>`    | 091230 | OR the first two registers and store it in the second register
10 | `xor <reg> <reg> <reg>`  | 0A1230 | XOR the first two registers and store it in the second register
11 | `shl <reg> <reg> <reg>`  | 0B1230 | Shift Left the first register by the second register's value
12 | `shr <reg> <reg> <reg>`  | 0C1230 | Shift Right the first register by the second register's value
13 | `str <reg> <mem>`        | 0D3FF0 | Store the value in the register in the memory address
14 | `get <mem> <reg>`        | 0EFF20 | Get the value in the memory address and put it in the register
