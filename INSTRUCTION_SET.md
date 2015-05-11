# FVM Instruction Set
Thr instruction set of the Flower Virtual Machine.

###Notation
* Registers begin with `r`: `r0`
* Scalar values begin with `#`: `#100`
  * Hex scalar values begin with `$`: `$1a0`
* Memory addresses begin with `@`: `@100`

###Instructions
* `reg` : Register
* `num` : Number

```fvm
0 : stp                   :: Stops the program
1 : ldi <reg> <num>       :: Load number to register
2 : rst <reg>             :: Reset register to zero
3 : add <reg> <reg> <reg> :: Add value in register one to value in register two and put it in register three
4 : sub <reg> <reg> <reg> :: Subtract value in register one from value in register two and put it in register three
```
