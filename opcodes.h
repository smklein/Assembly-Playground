#ifndef __OPCODES_H__
#define __OPCODES_H__

#include <string>
#include "parsing.h"
using namespace std;

struct registers_x86 {
    // General registers
    int eax;
    int ebx;
    int ecx;
    int edx;
    
    // Index and pointers
    int esi;
    int edi;
    int ebp;
    int eip;
    int esp;
    
    // Segment registers
    int cs; 
    int ds; 
    int es; 
    int fs; 
    int gs; 
    int ss; 
       
    int eflags;
} ;

void print(registers_x86 &reg);

registers_x86_type get_reg_type(string &reg);
int *get_register_location(registers_x86 &regs, registers_x86_type reg);

int execute_command(char memory[], registers_x86 &reg,
                    string &cmd, argument &src, argument &dest);
int get_num_args(string opcode);

#endif
