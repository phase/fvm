ldi r0 #12   ; Load 12 into register 0
ldi r1 #21   ; Load 21 into register 1
add r0 r1 r2 ; Add register 0 and register 1 and store it in register 2
str r2 @FF   ; Store register 2 at memory cell FF
stp          ; Stop the program
