module fvm.routine;
import fvm.register;
import fvm.instructions;
import std.stdio;
import std.file;
import std.conv;
import std.string;
import std.algorithm;

class Routine {
    static Routine[] globalRoutines;
    static Routine[] path;
    static Register[] globalRegisters;
    string id;
    ubyte[] instructions;
    Register[] localRegisters;
    
    this(string id, ubyte[] instructions) {
        this.id = id;
        this.instructions = instructions;
    }
    
    string getId() {
        return id;
    }
    
    ubyte[] getInstructions() {
        return instructions;
    }
    
    void run() {
        readInstructions(instructions);
    }
    
    void decompose() {
        path = path[0..$-1];
    }
    
    static Register getRegister(string id) {
        if(path.length < 1) {
            foreach(register; globalRegisters)
                if(register.getId() == id)
                    return register;
            return new Register(id, 0);
        } else {
            foreach(register; getCurrentRoutine().localRegisters)
                if(register.getId() == id)
                    return register;
            return new Register(id, 0);
        }
    }
    
    void deallocateRegister(string id) {
        deallocateRegister(getRegister(id));
    }
    
    void deallocateRegister(Register reg) {
        if(reg is null)
            throw new Exception("DeallocRegisterError: Register with id " ~ to!string(id) ~ " does not exist");
        auto index = countUntil(localRegisters, reg);
        localRegisters = remove(localRegisters, index);
    }
    
    static Routine getCurrentRoutine() {
        return path[$-1];
    }
    
    static void addGlobalRoutine(Routine routine) {
        globalRoutines ~= routine;
    }
    
    static void addSubRoutine(Routine routine) {
        path ~= routine;
    }
    
    static Routine getRoutine(string id) {
        foreach(routine; globalRoutines)
            if(routine.getId() == id)
                return routine;
        return null;
    }
    
    static void addRegisterToCurrentRoutine(Register reg) {
        if(path.length < 1) {
            globalRegisters ~= reg;
        } else {
            path[$-1].localRegisters ~= reg;
        }
    }
}

void parseRoutines(ubyte[] ins) {
    ubyte[] currentRoutine;
    for(int i = 0; i < ins.length; i++) {
        ubyte j = ins[i];
        if(j == 14) { //0x0E
            char[] routineName;
            while(ins[++i] != 0) routineName ~= ins[i]; //read string
            ubyte[] instructions;
            while(i + 1 < ins.length && ins[++i] != 15) //0x0F
                instructions ~= ins[i];
            Routine.addGlobalRoutine(new Routine(routineName.idup, instructions));
        }
    }
}