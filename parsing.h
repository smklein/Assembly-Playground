#ifndef __PARSING_H__
#define __PARSING_H__

#include <string>
using namespace std;

enum arg_type { IMM, ADDR, REG };

enum registers_x86_type {
    EAX, EBX, ECX, EDX,
    ESI, EDI, EBP, EIP, ESP,
    CS, DS, ES, FS, GS, SS, EFLAGS,
    INVALID
};

struct argument {
    arg_type type;
    union {
        int32_t immediate;
        int32_t address; // This acts as an index into memory.
        registers_x86_type reg;
    };  
} ; 


string &trim(string &s);
void replace_hex(string &s);

int parse_command(string &raw_command, string &cmd,
                  string &arg1, string &arg2);
int parse_argument(string &arg, argument &arg_info);

#endif
