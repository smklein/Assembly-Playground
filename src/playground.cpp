#include <iostream>
#include <string>
#include <sstream>

#include "inputoutput.h"
#include "parsing.h"
#include "shared_constants.h"
#include "opcodes.h"
#include "x86.h"

using namespace std;

/**
 * Given a piece of possibly malformed assembly from the user,
 * operate on the given registers and execute the command.
 */
int evaluate_command(VirtualSystem &vs, string raw_command) {
    string instruction, src_operand, dest_operand;
    output_dbg_eval_start(raw_command);


    /*
     * Parse out the instruction and operands from the input string.
     *
     * Since we are using move semantics, we can no longer use the
     * "raw command" after this point.
     */
    int num_args = parse_command(vs, std::move(raw_command),
                                 instruction, src_operand, dest_operand);
    if (num_args == -1) {
        output_err_command_invalid();
        return -1;
    }

    output_dbg_command_info(instruction, num_args, src_operand, dest_operand);

    // TODO: command is verified here, num args verified, args themselves
    // are not verified yet.
    
    // TODO: Filter the args. Identify information. Make them "trusted".
    ::operand src_operand_info;
    ::operand dest_operand_info;
    
    // TODO Call this
    int retval;
    if (num_args >= 1) {
        output_dbg_parse_src();
        retval = parse_operand(vs, src_operand, src_operand_info);
        if (retval)
            return -1;
    }
    if (num_args == 2) {
        output_dbg_parse_dest();
        retval = parse_operand(vs, dest_operand, dest_operand_info);
        if (retval)
            return -1;
    }

    // Handoff the operation to the virtual system, which actually acts
    // on the system state.
    vs.execute_command(instruction, src_operand_info, dest_operand_info);
    
    return 0;
}

// TODO: allow for AT&T vs intel conventions.
// For now? Using AT&T's version... CMD SRC, DEST
void assembly_playground() {
    string command;
    VirtualSystem vs;
    
    while (true) {
        output_msg_command_prompt();
        getline (cin, command);
        if (command.compare(QUIT_STRING) == 0) {
            /*  QUIT  */
            output_msg_exit();
            exit(0);
        } else if (command.compare(REGISTERS_STRING) == 0) {
            /*  REGISTER DUMP  */
            vs.get_registers()->print();
        } else if (command.find(PRINT_STRING) == 0) {
            /*  MEMORY DUMP  */
            string arg = command.substr(strlen(PRINT_STRING));
            replace_hex(arg);
            trim(arg);
            stringstream str(arg);
            int address;
            str >> address;
            if (!str) {
                cout << "[ERROR] Observing memory: Conversion to int failed\n";
            } else {
                cout << hex << "MEM[ 0x" << address << " ]: ";
                cout << "0x" << hex << (int) vs.get_memory(address) << endl;
            }   
        } else if (command.compare(HELP_STRING) == 0) {
            /*  HELP  */
            output_msg_help();
        } else if (command.compare("") == 0) {
            /*  IGNORE  */
        } else {
            /*  EVALUATE  */
            evaluate_command(vs, command);
        }
    }

}

int main() {
    output_msg_start();
    assembly_playground();
}
