module fvm.fvm;
import fvm.register;
import fvm.instructions;
import fvm.std;

int main(char[][] args) {
    if(args.length < 1) {
        writeln(" File not specified.");
        return 1;
    }
    string fileName = args[1].idup;
    ubyte[] instructions = cast(ubyte[])read(fileName);
    readInstructions(instructions);
    return 0;
}