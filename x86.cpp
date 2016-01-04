#include <iostream>
#include <string>
#include "x86.h"
#include "virtual_system.h"

using namespace std;

Registers_x86::Registers_x86() :
    eax(0), ebx(0), ecx(0), edx(0),
    esi(0), edi(0), ebp(0), eip(0), esp(0),
    cs(0), ds(0), es(0), fs(0), gs(0), ss(0), eflags(0) {
}

// Register enum --> Struct address converter.
int *Registers_x86::register_location(registers_type reg) {
    if (reg == EAX) return &eax;
    if (reg == EBX) return &ebx;
    if (reg == ECX) return &ecx;
    if (reg == EDX) return &edx;
    if (reg == ESI) return &esi;
    if (reg == EDI) return &edi;
    if (reg == EBP) return &ebp;
    if (reg == EIP) return &eip;
    if (reg == ESP) return &esp;
    if (reg == CS) return &cs;
    if (reg == DS) return &ds;
    if (reg == FS) return &fs;
    if (reg == GS) return &gs;
    if (reg == SS) return &ss;
    if (reg == EFLAGS) return &eflags;
    return NULL;
}

// Pretty printer.
void Registers_x86::print() const {
    cout << "[GENERAL REGISTERS]\n";
    cout << hex << "eax: 0x" << eax << ", ebx: 0x" << ebx
         << ", ecx: 0x" << ecx << ", edx: 0x" << edx << endl;
    cout << "[SEGMENT REGISTERS]\n";
    cout << hex << "cs: 0x" << cs << ", ds: 0x" << ds << ", es: 0x"
         << es << ", fs: 0x" << fs << ", gs: 0x" << gs
         << ", ss: 0x" << ss << endl;
    cout << "[INDEX AND POINTER REGISTERS]\n";
    cout << hex << "esi: 0x" << esi << ", edi: 0x" << edi
         << ", ebp: 0x" << ebp << ", eip: 0x" << eip << ", esp: 0x"
         << esp << endl;
    cout << "[EFLAGS]\n";
    cout << hex << "0x" << eflags << endl;
}   

// String Register name --> Register enum.
registers_type Registers_x86::get_reg_type(const string &reg) {
    if (reg.compare("%eax") == 0) return EAX;
    if (reg.compare("%ebx") == 0) return EBX;
    if (reg.compare("%ecx") == 0) return ECX;
    if (reg.compare("%edx") == 0) return EDX;
    if (reg.compare("%esi") == 0) return ESI;
    if (reg.compare("%edi") == 0) return EDI;
    if (reg.compare("%ebp") == 0) return EBP;
    if (reg.compare("%eip") == 0) return EIP;
    if (reg.compare("%esp") == 0) return ESP;
    if (reg.compare("%cs") == 0) return CS;
    if (reg.compare("%ds") == 0) return DS;
    if (reg.compare("%es") == 0) return ES;
    if (reg.compare("%fs") == 0) return FS;
    if (reg.compare("%gs") == 0) return GS;
    if (reg.compare("%ss") == 0) return SS;
    if (reg.compare("%eflags") == 0) return EFLAGS;
    return INVALID;
}

// String Opcode --> Number of arguments.
int Registers_x86::get_num_args(const string &opcode) {
    if (opcode.compare("mov") == 0) { return 2; }
    if (opcode.compare("movl") == 0) { return 2; }
    if (opcode.compare("add") == 0) { return 2; }
    if (opcode.compare("inc") == 0) { return 1; }
    if (opcode.compare("dec") == 0) { return 1; }
    if (opcode.compare("neg") == 0) { return 1; }
    if (opcode.compare("not") == 0) { return 1; }
    if (opcode.compare("pop") == 0) { return 1; }

    return -1;
}
