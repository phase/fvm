module fvm.instructions;
import fvm.register;
import fvm.std;

void readInstructions(ubyte[] ins) {
    for(int i = 0; i < ins.length; i++) {
        ubyte j = ins[i];
        //writeln("instruction: " ~ to!string(j) ~ " : " ~ to!string(i) ~ "/" ~ to!string(ins.length));
        //commands
        if(j == 0) { ///loadi <reg> <#>
            if(ins.length < i + 2) ///if the program doesn't have enough arguments for the instruction
                throw new Exception("LoadError: Malformed bytecode @ " ~ to!string(i) ~ "/" ~ to!string(ins.length));
            char[] register;
            while(ins[++i] != 0) register ~= ins[i]; ///read string
            long value = cast(long) ins[++i];
            new Register(register.idup, value);
        }
        else if(j == 1) { ///loada <reg> <#...
            if(ins.length < i + 2)
                throw new Exception("LoadError: Malformed bytecode @ " ~ to!string(i) ~ "/" ~ to!string(ins.length));
            char[] register;
            while(ins[++i] != 0) register ~= ins[i]; ///read string
            ubyte[] data;
            while(ins[++i] != 0) data ~= ins[i]; ///read string
            new Register(register.idup, data);
        }
        else if(j == 2) { ///loadf <reg> <##>
            if(ins.length < i + 2)
                throw new Exception("LoadError: Malformed bytecode @ " ~ to!string(i) ~ "/" ~ to!string(ins.length));
            char[] register;
            while(ins[++i] != 0) register ~= ins[i]; ///read string
            char[] data;
            while(ins[++i] != 0) data ~= ins[i]; ///read string
            new Register(register.idup, to!float(data));
        }
        else if(j == 10) { ///printc <reg>
            if(ins.length < i + 1)
                throw new Exception("PrintError: Malformed bytecode @ " ~ to!string(i));
            char[] register;
            while(ins[++i] != 0) register ~= ins[i]; ///read string
            Register reg = Register.getRegister(register.idup);
            switch(reg.getType()) {
                case Register.Type.NUMBER:
                    write(cast(char)reg.getNumberValue()); break;
                case Register.Type.ARRAY:
                    write(cast(char[]) reg.getValues()); break;
                case Register.Type.FLOAT:
                    throw new Exception("TypeError: Register of type Float cannot be printed as a character");
                    break;
                default: break;
            }
        }
        else if(j == 11) { ///printn <reg>
            if(ins.length < i + 1)
                throw new Exception("PrintError: Malformed bytecode @ " ~ to!string(i));
            char[] register;
            while(ins[++i] != 0) register ~= ins[i]; ///read string
            Register reg = Register.getRegister(register.idup);
            switch(reg.getType()) {
                case Register.Type.NUMBER:
                    write(to!string(reg.getNumberValue())); break;
                case Register.Type.ARRAY:
                    write(to!string(reg.getValues())); break;
                case Register.Type.FLOAT:
                    write(to!string(reg.getFloatValue())); break;
                default: break;
            }
        }
        else if(j == 12) { ///input <reg>
            char[] register;
            while(ins[++i] != 0) register ~= ins[i]; ///read string
            ubyte[] input = cast(ubyte[])(readln().dup);
            new Register(register.idup, input);
        }
        else {
            throw new Exception("ParseError: Malformed bytecode @ " ~ to!string(i));
        }
    }
}