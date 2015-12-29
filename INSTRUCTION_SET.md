# Instruction Set
The instruction set for the FVM.

Do note that:
* All strings are null-terminated
* All numbers are storred as longs in the VM (except floats);

| Value | Name | Syntax | Description |
|-------|------|--------|-------------|
| 0x0   | loadi | loadi <reg> <#> | Loads byte into register |
| 0x1   | loads | loads <reg> <str> | Loads string into register |
| 0x2   | loadf | loadf <reg> <str> | Loads string as float into register |
| 0x3   |  |  |  |
| 0x4   |  |  |  |
| 0x5   |  |  |  |
| 0x6   |  |  |  |
| 0x7   |  |  |  |
| 0x8   |  |  |  |
| 0x9   |  |  |  |
| 0xa   | printc | printc <reg> | Prints register as character |
| 0xb   | printn | printn <reg> | Prints register as number |
| 0xc   | input | input <reg> | Load string from stdin into register |
| 0xd   | call | call <routine> | Call routine |
| 0xe   | routinestart | routinestart <str> | Start routine named str |
| 0xf   | routineend | routineend | Ends routine |