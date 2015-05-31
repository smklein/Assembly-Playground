#include <iostream>
#include <string>
#include "parsing.h"

using namespace std;

struct registers_x86 {
    // General registers
    int eax;
    int ebx;
    int ecx;
    int edx;
    
    // Segment registers
    int cs;
    int ds;
    int es;
    int fs;
    int gs;
    int ss;
    
    // Index and pointers
    int esi;
    int edi;
    int ebp;
    int eip;
    int esp;
    
    int eflags;

    void print() {
        cout << "[GENERAL REGISTERS]\n";
        cout << "eax: " << eax << ", ebx: " << ebx << ", ecx: " << ecx 
             << ", edx: " << edx << endl;
        cout << "[SEGMENT REGISTERS]\n";
        cout << "cs: " << cs << ", ds: " << ds << ", es: " << es << ", fs: "
             << fs << ", gs: " << gs << ", ss: " << ss << endl;
        cout << "[INDEX AND POINTER REGISTERS]\n";
        cout << "esi: " << esi << ", edi: " << edi << ", ebp: " << ebp
             << ", eip: " << eip << ", esp: " << esp << endl;
        cout << "[EFLAGS]\n";
        cout << eflags << endl;
    }
} ;


int evaluate_command(registers_x86 &regs, string &raw_command) {
    cout << "Evaluating: " << raw_command << endl;
    parse_command(raw_command);
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
            regs.print();
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
