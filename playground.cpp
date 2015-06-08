#include <iostream>
#include <string>
#include <sstream>
#include "shared_constants.h"
#include "parsing.h"
#include "opcodes.h"

using namespace std;

/**
 * Given a piece of possibly malformed assembly from the user,
 * operate on the given registers and execute the command.
 */
int evaluate_command(char memory[], registers_x86 &regs, string &raw_command) {
    cout << "\t[EVAL] Evaluating: " << raw_command << endl;
    string cmd, src_arg, dest_arg;
    int num_args;
    if ((num_args = parse_command(raw_command, cmd, src_arg, dest_arg)) == -1) {
        cout << "[INVALID COMMAND]" << endl;
        return -1;
    }
    cout << "\t[EVAL][CMD]: [" << cmd << "]\n";
    cout << "\t[EVAL][# ARGS]: " << num_args << endl;
    if (num_args >= 1)
        cout << "\t[EVAL][SRC]: [" << src_arg << "]\n";
    if (num_args == 2)
        cout << "\t[EVAL][DEST]: [" << dest_arg << "]\n";
    // TODO: command is verified here, num args verified, args themselves
    // are not verified yet.
    
    // TODO: Filter the args. Identify information. Make them "trusted".
    argument src_arg_info;
    argument dest_arg_info;
    
    // TODO Call this
    int retval;
    if (num_args >= 1) {
        cout << "\t[EVAL] Parsing src\n";
        retval = parse_argument(src_arg, src_arg_info);
        if (retval)
            return -1;
    }
    if (num_args == 2) {
        cout << "\t[EVAL] Parsing dest\n";
        retval = parse_argument(dest_arg, dest_arg_info);
        if (retval)
            return -1;
    }

    // Handoff the operation to opcodes.cpp, which actually acts
    // on the system state.
    execute_command(memory, regs, cmd, src_arg_info, dest_arg_info);
    
    return 0;
}

// TODO: allow for AT&T vs intel conventions.
// For now? Using AT&T's version... CMD SRC, DEST
void assembly_playground() {
    string command;
    registers_x86 regs;
    char *memory = new char[MEMORY_SIZE_BYTES];
    
    memset(&regs, 0, sizeof(regs));
    memset(memory, 0, MEMORY_SIZE_BYTES);
    while (true) {
        cout << ">> ";
        getline (cin, command);
        if (command.compare("quit") == 0) {
            cout << "[EXIT] Exiting playground\n";
            delete[] memory;
            exit(0);
        } else if (command.compare("regs") == 0) {
            print(regs);
        } else if (command.find("print") == 0) {
            string arg = command.substr(strlen("print"));
            replace_hex(arg);
            trim(arg);
            stringstream str(arg);
            int val;
            str >> val;
            if (!str) {
                cout << "[ERROR] Conversion to int failed\n";
            } else {
                cout << hex << "MEM[ 0x" << val << " ]: ";
                cout << "0x" << hex << (int) memory[val] << endl;
            }   
        } else if (command.compare("help") == 0) {
            cout << "[HELP] Commands:\n";
            cout << "   Calling convention: AT&T. [CMD   SRC, DEST]\n";
            cout << "   Arch: x86.\n";
            cout << "   Endianness: Little endian.\n";
            cout << "regs -- Print out all register values\n";
            cout << "print ADDR -- Print out value at memory address ADDR\n";
            cout << "quit -- Exit the assembly playground\n";
        } else if (command.compare("") == 0) {
            // Desired behavior: do nothing.
        } else {
            evaluate_command(memory, regs, command);
        }
    }

}

int main() {
    cout << "[ASM PLAYGROUND STARTING]\n";
    cout << "Commands include [help], [quit], etc...\n";
    assembly_playground();
}
