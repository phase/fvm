module fvm.fvm;
import fvm.register;
import fvm.instructions;
import fvm.routine;
import std.stdio;
import std.file;
import std.conv;
import std.string;

int main(char[][] args) {
    if(args.length < 1) {
        writeln(" File not specified.");
        return 1;
    }
    string fileName = args[1].idup;
    ubyte[] instructions = cast(ubyte[])read(fileName);
    parseRoutines(instructions);
    Routine.getRoutine("main").run();
    return 0;
}