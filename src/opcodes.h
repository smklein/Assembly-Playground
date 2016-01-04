#ifndef __OPCODES_H__
#define __OPCODES_H__

#include <string>
using namespace std;

enum arg_type { IMM, ADDR, REG };

enum registers_type {
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
        registers_type reg;
    };  
} ;

class Registers {
  public:
    // Given a particular "reg" enumeration code, return access to that
    // register.
    virtual int *register_location(registers_type reg) = 0;

    // Pretty print the registers
    virtual void print() const = 0;
    
    /**
     * @param[in] reg: percent escaped register name (i.e., "%eax").
     * 
     * @return Enumeration of register type (or INVALID on error).
     */
    virtual registers_type get_reg_type(const string &reg) = 0;

    /**
     * @param[in] opcode: string (i.e., "mov").
     *
     * @return Number of opcodes required for the supplied opcode.
     */
    virtual int get_num_args(const string &opcode) = 0;
} ;

#endif
