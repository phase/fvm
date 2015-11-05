module fvm.instructions;
import fvm.register;
import fvm.std;

void readInstructions(ubyte[] ins) {
    for(int i = 0; i < ins.length; i++) {
        ubyte j = ins[i];
        writeln("ubyte: " ~ to!string(j));
        //commands
        if(j == 0) { ///load <reg> <#>
            if(ins.length < i + 2) ///if the program doesn't have enough arguments for the instruction
                throw new Exception("Malformed bytecode @ " ~ to!string(i) ~ "/" ~ to!string(ins.length));
            ubyte register = ins[i+1];
            long value = cast(long) ins[i+2];
            new Register(register, value);
            i += 2;
        }
        else if(j == 10) {
            if(ins.length < i + 1)
                throw new Exception("Malformed bytecode @ " ~ to!string(i));
            ubyte register = ins[i+1];
            write(Register.getValue(register));
        }
        else {
            throw new Exception("Malformed bytecode @ " ~ to!string(i));
        }
    }
}