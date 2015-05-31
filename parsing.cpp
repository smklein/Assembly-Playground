#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace std;

/**
 * Turns all "0x..." instances into decimal in the command string.
 */
void replace_hex(string &command) {
    string hex_string;
    size_t hex_start = command.find("0x");
    size_t hex_end;
    while (hex_start != string::npos) {
        hex_end = hex_start + 2;
        while (hex_end < command.size() && isxdigit(command[hex_end]))
            hex_end++;
        hex_string.assign(command, hex_start + 2, hex_end - (hex_start + 2));
        command.erase(hex_start, hex_string.size() + 2);
        stringstream ss;
        int decimal;
        ss << std::hex << hex_string;
        ss >> decimal;
        command.insert(hex_start, to_string(decimal));
        hex_start = command.find("0x");
    }
}

/**
 * Replaces all commas inside parenthases with the "+" delimiter instead.
 * This helps me parse arguments.
 */
int replace_parens_commas(string &command) {
    int parens_count = 0;
    for (int i = 0; i < command.size(); i++) {
        if (command[i] == '(') {
            parens_count++;
        } else if (command[i] == ')') {
            parens_count--;
            if (parens_count < 0) // Should not happen -- malformed input.
                return -1;
        } else if (command[i] == ',' && (parens_count > 0)) {
            command[i] = '+';
        }
    }
    return 0;
}

int parse_command(string &raw_command) {
    int retval;
    string cmd, arg1, arg2;
    cout << "[PARSING] Evaluating: " << raw_command << endl;
    replace_hex(raw_command);
    cout << "[PARSING] Sans hex: " << raw_command << endl;
    retval = replace_parens_commas(raw_command);
    if (retval)
        return retval;
    cout << "[PARSING] With updated commas: " << raw_command << endl;
    
    cout << "CMD: " << cmd << endl;
    cout << "arg1: " << arg1 << endl;
    cout << "arg2: " << arg2 << endl;
    
    return 0;
}

