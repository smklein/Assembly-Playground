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
int evaluate_command(VirtualSystem &vs, string &raw_command) {
    string cmd, src_arg, dest_arg;
    output_dbg_eval_start(raw_command);
    int num_args;
    if ((num_args = parse_command(vs, raw_command, cmd, src_arg, dest_arg)) == -1) {
        output_err_command_invalid();
        return -1;
    }

    output_dbg_command_info(cmd, num_args, src_arg, dest_arg);

    // TODO: command is verified here, num args verified, args themselves
    // are not verified yet.
    
    // TODO: Filter the args. Identify information. Make them "trusted".
    argument src_arg_info;
    argument dest_arg_info;
    
    // TODO Call this
    int retval;
    if (num_args >= 1) {
        output_dbg_parse_src();
        retval = parse_argument(vs, src_arg, src_arg_info);
        if (retval)
            return -1;
    }
    if (num_args == 2) {
        output_dbg_parse_dest();
        retval = parse_argument(vs, dest_arg, dest_arg_info);
        if (retval)
            return -1;
    }

    // Handoff the operation to opcodes.cpp, which actually acts
    // on the system state.
    vs.execute_command(cmd, src_arg_info, dest_arg_info);
    
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
                cout << "[ERROR] Conversion to int failed\n";
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
