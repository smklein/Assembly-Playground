#include <iostream>
#include <string>
#include "parsing.h"
#include "opcodes.h"

using namespace std;

int evaluate_command(registers_x86 &regs, string &raw_command) {
    cout << "Evaluating: " << raw_command << endl;
    string cmd, arg1, arg2;
    int num_args;
    if ((num_args = parse_command(raw_command, cmd, arg1, arg2)) == -1) {
        cout << "[INVALID COMMAND]" << endl;
        return -1;
    }
    cout << "[EVAL][CMD]: [" << cmd << "]\n";
    cout << "[EVAL][# ARGS]: " << num_args << endl;
    if (num_args >= 1)
        cout << "[EVAL][ARG1]: [" << arg1 << "]\n";
    if (num_args == 2)
        cout << "[EVAL][ARG2]: [" << arg2 << "]\n";
    // TODO: command is verified here, num args verified, args themselves
    // are not verified yet.
    
    // TODO: Filter the args. Identify information. Make them "trusted".
    argument arg1_info;
    argument arg2_info;

    arg1_info.type = ADDR;
    arg1_info.address = &regs.eax;
    execute_command(regs, cmd, arg1_info, arg2_info);
    
    return 0;
}

// TODO: allow for AT&T vs intel conventions.
// For now? Using AT&T's version... CMD SRC, DEST
void assembly_playground() {
    string command;
    registers_x86 regs;
    memset(&regs, 0, sizeof(regs));
    while (true) {
        cout << ">> ";
        getline (cin, command);
        // TODO parse command
        if (command.compare("quit") == 0) {
            cout << "[EXIT] Exiting playground\n";
            exit(0);
        } else if (command.compare("help") == 0) {
            cout << "[HELP] Help message here\n"; // TODO
            cout << "regs -- Print out all register values\n";
        } else if (command.compare("regs") == 0) {
            print(regs);
        } else if (command.compare("") == 0) {
            // Desired behavior: do nothing.
        } else {
            cout << "Command Attempted\n";
            evaluate_command(regs, command);
            //cout << "[COMMAND] Okay, I need to parse this out...\n";
        }
    }

}

int main() {
    cout << "[ASM PLAYGROUND STARTING]\n";
    cout << "Commands include [help], [quit], etc...\n";
    assembly_playground();
}
