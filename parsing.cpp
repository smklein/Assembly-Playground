#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "opcodes.h"

using namespace std;


// trim from start
static inline string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}

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

/**
 * Gets command from "full command". Cuts out command, leaving args.
 * Returns 0 on success, -1 on failure.
 */
int get_command(string &s, string &command) {
    int cmd_start;
    int cmd_end;
    cmd_start = s.find_first_not_of(" \t\n");
    if (cmd_start == string::npos) {
        return -1;
    }
    cmd_end = s.find_first_of(" \t", cmd_start + 1);
    if ((cmd_end == string::npos) || (cmd_end == -1)) {
        cmd_end = s.size();
    }
    command.assign(s, cmd_start, cmd_end - cmd_start);
    s.erase(0, cmd_end);
    return 0;
}


/**
 * 
 */
int get_two_arguments(string &command, string &arg1, string &arg2) {
    size_t arg1_start = command.find_first_not_of(" \t");
    size_t arg1_end = command.find(",");
    if (arg1_end == string::npos) {
        return -1;
    }
    arg1.assign(command, arg1_start, arg1_end - arg1_start);
    trim(arg1);
    cout << "arg 1: [" << arg1 << "]\n";
    arg2.assign(command, arg1_end + 1, command.size() - (arg1_end + 1));
    trim(arg2);
    cout << "arg 2: [" << arg2 << "]\n";
    return 0;
}

/**
 * TODO DOX
 */
int parse_command(string &raw_command, string &cmd,
                  string &arg1, string &arg2) {
    int retval;
    trim(raw_command);
    cout << "[PARSING] Evaluating: " << raw_command << endl;
    replace_hex(raw_command);
    cout << "[PARSING] Sans hex: " << raw_command << endl;
    retval = replace_parens_commas(raw_command);
    cout << "[PARSING] With updated commas: " << raw_command << endl;
    if (retval)
        return retval;
    retval = get_command(raw_command, cmd);
    trim(raw_command);
    cout << "[PARSING] New raw: " << raw_command << endl;
    cout << "[PARSING] Cmd: " << cmd << endl;
    if (retval == -1) {
        cout << "[ERROR]" << endl;
        return retval;
    }
    int num_expected_args = get_num_args(cmd);
    cout << "Number of args expected: " << num_expected_args << endl;
    switch (num_expected_args) {
        case 2:
            if (get_two_arguments(raw_command, arg1, arg2)) {
                return -1;
            } else {
                return 2;
            }
        case 1:
            arg1.assign(raw_command);
            return 1;
        case 0:
            return 0;
        default:
            return -1;
    }
}

