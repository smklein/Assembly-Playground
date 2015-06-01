#ifndef __OPCODES_H__
#define __OPCODES_H__

#include <string>
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

enum arg_type { IMM, ADDR };

struct argument {
    arg_type type;
    union {
        int32_t immediate;
        int32_t *address;
    };
} ;

void print(registers_x86 &reg);

int execute_command(registers_x86 &reg,
                    string &cmd, argument &arg1, argument &arg2);
int get_num_args(string opcode);

#endif
