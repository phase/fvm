module fvm.instructions;
import fvm.register;
import fvm.std;

void readInstructions(ubyte[] ins) {
    for(int i = 0; i < ins.length; i++) {
        ubyte j = ins[i];
        //writeln("instruction: " ~ to!string(j));
        //commands
        if(j == 0) { ///load <reg> <#>
            if(ins.length < i + 2) ///if the program doesn't have enough arguments for the instruction
                throw new Exception("LoadError: Malformed bytecode @ " ~ to!string(i) ~ "/" ~ to!string(ins.length));
            ubyte register = ins[++i];
            long value = cast(long) ins[++i];
            new Register(register, value);
        }
        else if(j == 10) { ///print <reg>
            if(ins.length < i + 1)
                throw new Exception("PrintError: Malformed bytecode @ " ~ to!string(i));
            ubyte register = ins[++i];
            write(cast(char)Register.getValue(register));
        }
        else {
            throw new Exception("ParseError: Malformed bytecode @ " ~ to!string(i));
        }
    }
}