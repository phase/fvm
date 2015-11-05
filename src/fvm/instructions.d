module fvm.instructions;
import fvm.register;
import fvm.std;

void readInstructions(ubyte[] ins) {
    for(int i = 0; i < ins.length; i++) {
        ubyte j = ins[i];
        //writeln("instruction: " ~ to!string(j));
        //commands
        if(j == 0) { ///loadi <reg> <#>
            if(ins.length < i + 2) ///if the program doesn't have enough arguments for the instruction
                throw new Exception("LoadError: Malformed bytecode @ " ~ to!string(i) ~ "/" ~ to!string(ins.length));
            ubyte register = ins[++i];
            long value = cast(long) ins[++i];
            new Register(register, value);
        }
        else if(j == 1) { ///loada <reg> <#...
            if(ins.length < i + 2)
                throw new Exception("LoadError: Malformed bytecode @ " ~ to!string(i) ~ "/" ~ to!string(ins.length));
            ubyte register = ins[++i];
        }
        else if(j == 10) { ///print <reg>
            if(ins.length < i + 1)
                throw new Exception("PrintError: Malformed bytecode @ " ~ to!string(i));
            ubyte register = ins[++i];
            Register reg = Register.getRegister(register);
            switch(reg.getType()) {
                case Register.Type.NUMBER:
                    write(cast(char)reg.getValue());
                case Register.Type.ARRAY:
                    write(cast(char[])reg.getValues());
                default: break;
            }
        }
        else {
            throw new Exception("ParseError: Malformed bytecode @ " ~ to!string(i));
        }
    }
}