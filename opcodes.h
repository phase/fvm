/* Registers for VM */
#define NUM_REGS 16
unsigned regs[NUM_REGS];

unsigned memory[0xFFF];

/* Program Counter */
int pc = 1;

/* Fields */
int instruction = 0;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int n4 = 0;
int l2 = 0;
int l3 = 0;
int l4 = 0;
int t1 = 0;
int t2 = 0;
int w = 0;
int m1 = 0;
int m2 = 0;

/* Is the program running? */
int running = 0;

typedef void (*func)();


void stp() {
    running = 0;
}

void ldi() {
    regs[n1] = l3;
}

void rst() {
    regs[n1] = 0;
}

void gto() {
    pc = l4;
}

void add() {
    regs[n3] = regs[n1] + regs[n2];
}

void sub() {
    regs[n3] = regs[n1] - regs[n2];
}

void mul() {
    regs[n3] = regs[n1] * regs[n2];
}

void divide() {
    regs[n3] = regs[n1] / regs[n2];
}

void mod() {
    regs[n3] = regs[n1] % regs[n2];
}

void and() {
    regs[n3] = regs[n1] & regs[n2];
}

void or() {
    regs[n3] = regs[n1] | regs[n2];
}

void xor() {
    regs[n3] = regs[n1] ^ regs[n2];
}

void not() {
    regs[n2] = !regs[n1];
}

void shl() {
    regs[n3] = regs[n1] << regs[n2];
}

void shr() {
    regs[n3] = regs[n1] >> regs[n2];
}

void str() {
    memory[t1] = regs[n1];
}

void get() {
    regs[n3] = memory[t2];
}

void red() {
    scanf("%d", &regs[n1]);
}

void prt() {
    printf("%d", regs[n1]);
}

void prc() {
    printf("%c", regs[n1]);
}

void trn() {
    regs[n2] = regs[n1];
}

void bnz() {
    if (regs[n1] != 0) pc = m2;
}

void biz() {
    if (regs[n1] == 0) pc = m2;
}

void neg() {
    regs[n2] = -regs[n1];
}

void btc() {
    regs[n2] = ~regs[n1];
}

void error() {
    printf("Error: Instruction %X not found!", instruction);
    exit(EXIT_FAILURE);
}

func operations[] = {
    stp,
    ldi,
    rst,
    gto,
    add,
    sub,
    mul,
    divide,
    mod,
    and,
    or,
    xor,
    not,
    shl,
    shr,
    str,
    get,
    red,
    prt,
    prc,
    trn,
    bnz,
    biz,
    neg,
    btc
};