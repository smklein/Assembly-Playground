#ifndef __x86_H__
#define __x86_H__

#include <string>
#include "opcodes.h"
using namespace std;

class Registers_x86 : public Registers {
  public:
    Registers_x86();

    // Given a particular "reg" enumeration code, return access to that
    // register.
    int *register_location(registers_type reg) override;

    // Pretty print the registers
    void print() const override;
    
    /**
     * @param[in] reg: percent escaped register name (i.e., "%eax").
     * 
     * @return Enumeration of register type (or INVALID on error).
     */
    registers_type get_reg_type(const string &reg) override;

    /**
    * @param[in] opcode: string (i.e., "mov").
    *
    * @return Number of opcodes required for the supplied opcode.
    */
    int get_num_args(const string &opcode) override;
  private:
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

#endif
