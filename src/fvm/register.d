module fvm.register;
import std.conv;

class Register {
    static Register[] registers;
    ubyte id;
    long value = 0;
    
    this(ubyte id) {
        this.id = id;
        registers ~= this;
    }
    
    this(ubyte id, long value) {
        this.id = id;
        this.value = value;
        registers ~= this;
    }
    
    ubyte getId() {
        return id;
    }
    
    long getValue() {
        return value;
    }
    
    override string toString() {
        return "Register[" ~ to!string(id) ~ "]: " ~ to!string(value);
    }
    
    static getRegister(ubyte id) {
        foreach(register; registers)
            if(register.getId() == id)
                return register;
        return new Register(id);
    }
    
    static getValue(ubyte id) {
        getRegister(id).getValue();
    }
}