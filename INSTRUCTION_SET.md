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
ldi <reg> <num>       :: Load number to register
rst <reg>             :: Reset register to zero
add <reg> <reg> <reg> :: Add value in register one to value in register two and put it in register three
sub <reg> <reg> <reg> :: Subtract value in register one from value in register two and put it in register three
```
