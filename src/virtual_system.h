#ifndef __VIRTUAL_SYSTEM_H__
#define __VIRTUAL_SYSTEM_H__

#include <memory>
#include <string>
#include "opcodes.h"
#include "shared_constants.h"
#include "x86.h"
using namespace std;

class VirtualSystem {
  public:
    VirtualSystem() : memory(make_unique<char[]>(MEMORY_SIZE_BYTES)) {
      memset(memory.get(), 0, MEMORY_SIZE_BYTES);

      // TODO make this set up via appropriate arg
      regs = unique_ptr<Registers>(new Registers_x86);
    }
    
    char get_memory(int address) const {
      return memory.get()[address];
    }

    void set_memory(int address, char value) {
      memory.get()[address] = value;
    }

    Registers *get_registers() {
      return regs.get();
    }

    /**
     * Function which actually modifies system state based on a single
     * operation.
     *
     * @param[in] cmd: String representation of opcode
     * @param[in] src: Source argument
     * @param[in] dest: Dest argument
     *
     * @return 0 on success, -1 on error.
     */
    int execute_command(string &cmd, operand &src, operand &dest) {
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
                int *r_loc = regs.get()->register_location(src.reg);
                if (r_loc == NULL)
                    return -1; 
                *r_loc += 1;
            } else {
                // TODO change this use of address! ALso, overflow of char into int?
                // (figure it out)
                cout << "Incrementing memory address\n";
                memory.get()[src.address] = memory.get()[src.address] + 1; 
                //int32_t *addr = src.address;
                //*addr += 1;
            }   
            return 0;
        } else if (cmd.compare("mov") == 0) {
            return -1; 
            /*  
            int src_val;
            if (src.type == IMM) src_val = src.immediate;
            else if (src.type == ADDR) src_val = *(int *)(memory + src.address);
            else if (src.type == REG) src_val = *regs.register_location(src.reg);
            else return -1;
            cout << "MOV. SRC: " << src_val << endl;
            
            if (dest.type == IMM) return -1;
            else if (dest.type == ADDR) ((int *)memory)[dest.address] = src_val;
            else if (dest.type == REG) *regs.register_location(dest.reg) = src_val;
            else return -1;

            return 0; */
        }
        return -1;
    }

  private:
    unique_ptr<Registers> regs;
    unique_ptr<char[]> memory;
} ;



#endif
