module fvm.fvm;
import fvm.register;
import std.stdio;
import std.file;
import std.conv;
import std.string;

int main(char[][] args) {
    if(args.length < 1) {
        writeln(" File not specified.");
        return 1;
    }
    string fileName = args[0].idup;
    ubyte[] instructions = cast(ubyte[])read(fileName);
    return 0;
}