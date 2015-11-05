module fvm.register;
import fvm.std;
import std.algorithm;

class Register {
    enum Type : string {
        NUMBER = "Number", ARRAY = "Array"
    }
    
    static Register[] registers;
    ubyte id;
    Type type;
    long value = 0;
    int[] values;
    
    this(ubyte id, int[] values) {
        this.id = id;
        this.values = values;
        this.type = Type.ARRAY;
        registers ~= this;
    }
    
    this(ubyte id, long value) {
        this.id = id;
        this.value = value;
        this.type = Type.NUMBER;
        registers ~= this;
    }
    
    ubyte getId() {
        return id;
    }
    
    Type getType() {
        return type;
    }
    
    long getValue() {
        if(type != Type.NUMBER)
            throw new Exception("RegisterTypeError: Tried to get number value from a register with type " ~ type);
        return value;
    }
    
    int[] getValues() {
        if(type != Type.ARRAY)
            throw new Exception("RegisterTypeError: Tried to get array value from a register with type " ~ type);
        return values;
    }
    
    override string toString() {
        return type ~ "Register[" ~ to!string(id) ~ "]";
    }
    
    static Register getRegister(ubyte id) {
        foreach(register; registers)
            if(register.getId() == id)
                return register;
        return new Register(id, 0);
    }
    
    static void deallocateRegister(ubyte id) {
        Register reg = getRegister(id);
        if(reg is null)
            throw new Exception("DeallocRegisterError: Register with id " ~ to!string(id) ~ " does not exist");
        auto index = countUntil(registers, reg);
        registers = remove(registers, index);
    }
}