#include <iostream>
#include <string>
#include "opcodes.h"

using namespace std;


void print(registers_x86 &reg) {
    cout << "[GENERAL REGISTERS]\n";
    cout << "eax: " << reg.eax << ", ebx: " << reg.ebx << ", ecx: " << reg.ecx 
         << ", edx: " << reg.edx << endl;
    cout << "[SEGMENT REGISTERS]\n";
    cout << "cs: " << reg.cs << ", ds: " << reg.ds << ", es: " << reg.es << ", fs: "
         << reg.fs << ", gs: " << reg.gs << ", ss: " << reg.ss << endl;
    cout << "[INDEX AND POINTER REGISTERS]\n";
    cout << "esi: " << reg.esi << ", edi: " << reg.edi << ", ebp: " << reg.ebp 
         << ", eip: " << reg.eip << ", esp: " << reg.esp << endl;
    cout << "[EFLAGS]\n";
    cout << reg.eflags << endl;
}   

int execute_command(registers_x86 &reg,
                    string &cmd, argument &arg1, argument &arg2) {
    // Arg1 / 2 can be
    // (1) Register
    // (2) Memory
    // (3) Immediate
    // (4) N/A
    // TODO. Make this work generally.
    
    if (cmd.compare("inc") == 0) {
        if (arg1.type == IMM) {
            return -1; // Cannot increment an immediate...
        } else {
            int32_t *addr = arg1.address;
            *addr += 1;
        }
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
