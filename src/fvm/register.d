module fvm.register;
import fvm.std;
import std.algorithm;

class Register {
    enum Type : string {
        NUMBER = "Number", ARRAY = "Array", FLOAT = "Float"
    }
    
    static Register[] registers;
    string id;
    Type type;
    long nvalue = 0;
    float fvalue = 0;
    ubyte[] values;
    
    this(string id, ubyte[] values) {
       /* if(registerExists(id))
            throw new Exception("RegisterError: Register with id " ~ id ~ " already exists");*/
        this.id = id;
        this.values = values;
        this.type = Type.ARRAY;
        registers ~= this;
    }
    
    this(string id, long nvalue) {
       /* if(registerExists(id))
            throw new Exception("RegisterError: Register with id " ~ id ~ " already exists");*/
        this.id = id;
        this.nvalue = nvalue;
        this.type = Type.NUMBER;
        registers ~= this;
    }
    
    this(string id, float f) {
        this.id = id;
        this.fvalue = f;
        this.type = Type.FLOAT;
        registers ~= this;
    }
    
    string getId() {
        return id;
    }
    
    Type getType() {
        return type;
    }
    
    long getNumberValue() {
        if(type != Type.NUMBER)
            throw new Exception("RegisterTypeError: Tried to get number value from a register with type " ~ type);
        return nvalue;
    }
    
    float getFloatValue() {
        if(type != Type.FLOAT)
            throw new Exception("RegisterTypeError: Tried to get number value from a register with type " ~ type);
        return fvalue;
    }
    
    ubyte[] getValues() {
        if(type != Type.ARRAY)
            throw new Exception("RegisterTypeError: Tried to get array value from a register with type " ~ type);
        return values;
    }
    
    override string toString() {
        return type ~ "Register[" ~ id ~ "]";
    }
    
    static Register getRegister(string id) {
        foreach(register; registers)
            if(register.getId() == id)
                return register;
        return new Register(id, 0);
    }
    
    static void deallocateRegister(string id) {
        Register reg = getRegister(id);
        if(reg is null)
            throw new Exception("DeallocRegisterError: Register with id " ~ to!string(id) ~ " does not exist");
        auto index = countUntil(registers, reg);
        registers = remove(registers, index);
    }
    
    bool registerExists(string id) {
        return getRegister(id) !is null;
    }
}