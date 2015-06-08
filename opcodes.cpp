#include <iostream>
#include <string>
#include "opcodes.h"

using namespace std;


void print(registers_x86 &reg) {
    cout << "[GENERAL REGISTERS]\n";
    cout << hex << "eax: 0x" << reg.eax << ", ebx: 0x" << reg.ebx
         << ", ecx: 0x" << reg.ecx << ", edx: 0x" << reg.edx << endl;
    cout << "[SEGMENT REGISTERS]\n";
    cout << hex << "cs: 0x" << reg.cs << ", ds: 0x" << reg.ds << ", es: 0x"
         << reg.es << ", fs: 0x" << reg.fs << ", gs: 0x" << reg.gs
         << ", ss: 0x" << reg.ss << endl;
    cout << "[INDEX AND POINTER REGISTERS]\n";
    cout << hex << "esi: 0x" << reg.esi << ", edi: 0x" << reg.edi
         << ", ebp: 0x" << reg.ebp << ", eip: 0x" << reg.eip << ", esp: 0x"
         << reg.esp << endl;
    cout << "[EFLAGS]\n";
    cout << hex << "0x" << reg.eflags << endl;
}   

/**
 * String --> Register enum converter.
 */
registers_x86_type get_reg_type(string &reg) {
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

/**
 * Register enum --> Struct address converter.
 */
int *get_register_location(registers_x86 &regs, registers_x86_type reg) {
    if (reg == EAX) return &regs.eax;
    if (reg == EBX) return &regs.ebx;
    if (reg == ECX) return &regs.ecx;
    if (reg == EDX) return &regs.edx;
    if (reg == ESI) return &regs.esi;
    if (reg == EDI) return &regs.edi;
    if (reg == EBP) return &regs.ebp;
    if (reg == EIP) return &regs.eip;
    if (reg == ESP) return &regs.esp;
    if (reg == CS) return &regs.cs;
    if (reg == DS) return &regs.ds;
    if (reg == FS) return &regs.fs;
    if (reg == GS) return &regs.gs;
    if (reg == SS) return &regs.ss;
    if (reg == EFLAGS) return &regs.eflags;
    return NULL;
}

int execute_command(char memory[], registers_x86 &regs,
                    string &cmd, argument &src, argument &dest) {
    // Arg1 / 2 can be
    // (1) Register
    // (2) Memory
    // (3) Immediate
    // (4) N/A
    // TODO. Make this work generally.
    
    // TODO: Endianness. x86 is LITTLE ENDIAN.
    if (cmd.compare("inc") == 0) {
        if (src.type == IMM) {
            cout << "Cannot increment immediate\n";
            return -1; // Cannot increment an immediate...
        } else if (src.type == REG) {
            cout << "Incrementing register\n";
            int *addr = get_register_location(regs, src.reg);
            if (addr == NULL)
                return -1;
            *addr += 1;
        } else {
            // TODO change this use of address!
            cout << "Incrementing memory address\n";
            int *mem = (int *)&memory[src.address];
            *mem += 1;
            //int32_t *addr = src.address;
            //*addr += 1;
        }
        return 0;
    } else if (cmd.compare("mov") == 0) {
        int src_val;
        if (src.type == IMM) src_val = src.immediate;
        else if (src.type == ADDR) src_val = *(int *)(memory + src.address);
        else if (src.type == REG) src_val = *get_register_location(regs, src.reg);
        else return -1;
        cout << "MOV. SRC: " << src_val << endl;
        
        if (dest.type == IMM) return -1;
        else if (dest.type == ADDR) ((int *)memory)[dest.address] = src_val;
        else if (dest.type == REG) *get_register_location(regs, dest.reg) = src_val;
        else return -1;

        return 0;
    }

    return -1;
}


int get_num_args(string opcode) {
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
