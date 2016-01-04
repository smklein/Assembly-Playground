#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "parsing.h"
#include "opcodes.h"

using namespace std;

#define OPERAND_SEPARATOR '+'

// trim from start
static inline void ltrim(string &s) {
    s.erase(s.begin(), // Start of string
            find_if(s.begin(), // End at the first non-space character
                    s.end(),
                    not1(ptr_fun<int, int>(isspace))));
}

// trim from end
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), // Same as ltrim, but reversed
                    s.rend(),
                    not1(ptr_fun<int, int>(isspace))).base(),
            s.end());
}

// trim from both ends
void trim(string &s) {
    ltrim(s);
    rtrim(s);
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
    // Before we manipulate the string, it should not contain OPERAND_SEPARATOR
    if (command.find(OPERAND_SEPARATOR) != string::npos)
        return -1;
    for (int i = 0; i < command.size(); i++) {
        if (command[i] == '(') {
            parens_count++;
        } else if (command[i] == ')') {
            parens_count--;
            if (parens_count < 0) // Should not happen -- malformed input.
                return -1;
        } else if (command[i] == ',' && (parens_count > 0)) {
            command[i] = OPERAND_SEPARATOR;
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
 * Split "command" based on comma, trim, return two arguments. 
 */
int get_two_arguments(string &command, string &src, string &dest) {
    size_t src_start = command.find_first_not_of(" \t");
    size_t src_end = command.find(",");
    if (src_end == string::npos) {
        return -1;
    }
    src.assign(command, src_start, src_end - src_start);
    trim(src);
    cout << "\t[PARSING] src: [" << src << "]\n";
    dest.assign(command, src_end + 1, command.size() - (src_end + 1));
    trim(dest);
    cout << "\t[PARSING] dest: [" << dest << "]\n";
    return 0;
}

/**
 * Given a full command, parse out the opcode, the source, and the destination
 * arguments. Do not interpret the arguments yet.
 */
int parse_command(VirtualSystem &vs,
                  string &raw_command, string &cmd,
                  string &src, string &dest) {
    int retval;
    trim(raw_command);
    cout << "\t[PARSING] Evaluating: " << raw_command << endl;
    replace_hex(raw_command);
    cout << "\t[PARSING] Sans hex: " << raw_command << endl;
    retval = replace_parens_commas(raw_command);
    cout << "\t[PARSING] With updated commas: " << raw_command << endl;
    if (retval)
        return retval;
    retval = get_command(raw_command, cmd);
    trim(raw_command);
    cout << "\t[PARSING] New raw: " << raw_command << endl;
    cout << "\t[PARSING] Cmd: " << cmd << endl;
    if (retval == -1) {
        cout << "[ERROR]" << endl;
        return retval;
    }
    int num_expected_args = vs.get_registers()->get_num_args(cmd);
    cout << "\t[PARSING] Number of args expected: " << num_expected_args << endl;
    switch (num_expected_args) {
        case 2:
            if (get_two_arguments(raw_command, src, dest)) {
                return -1;
            } else {
                return 2;
            }
        case 1:
            src.assign(raw_command);
            return 1;
        case 0:
            return 0;
        default:
            return -1;
    }
}

/**
 * Given an argument "arg", determine the matching "arg_info"
 * for this arg by parsing out the required info.
 *
 * TODO: Later, identify if arg is compatible with opcode given.
 */
int parse_argument(VirtualSystem &vs, string &arg, argument &arg_info) {
    if (arg.length() == 0) {
        cout << "[ERROR] Zero length argument. Invalid\n";
        return -1;
    }
    if (arg.at(0) == '$') { // Operand: Immediate.
        string immediate_str = arg.substr(1);
        stringstream str(immediate_str);
        int val;
        str >> val;
        if (!str) {
            cout << "Conversion to int failed\n";
            return -1;
        } else {
            cout << "Converted to int: " << val << endl;
            arg_info.type = IMM;
            arg_info.immediate = val;
            return 0;
        }
    } else if (arg.find("%") != string::npos) { // Operand: Register (?)
        cout << "\tIdentifying arg as containing reg, possibly memory\n";
        registers_type reg = vs.get_registers()->get_reg_type(arg);
        if (reg != INVALID) {
            // Operand: Register (for certain)
            cout << "\tInterpreted arg: " << arg << " as a register...\n";
            arg_info.type = REG;
            arg_info.reg = reg;
            return 0;
        }
    }
    // Operand: Memory or error
    int l_paren_count = count(arg.begin(), arg.end(), '(');
    int l_paren_pos = arg.find("(");
    int r_paren_count = count(arg.begin(), arg.end(), ')');
    int r_paren_pos = arg.find(")");
    if ((l_paren_count == 0) && (r_paren_count == 0)) {
        // Absolute Addressing mode. Arg: Imm. Value: MEM[Imm].
        stringstream str(arg);
        int val;
        str >> val;
        if (!str) {
            cout << "[ERROR] Conversion to int failed\n";
            return -1;
        } else {
            cout << "\tConverted to direct memory address: " << val << endl;
            arg_info.type = ADDR;
            arg_info.address = val;
            return 0;
        }

    } else if ((l_paren_count == 1) && (r_paren_count == 1) &&
        (l_paren_pos < r_paren_pos)) {
        cout << "\tIdentified parentheses. Memory?\n";
        // TODO parse address of memory. a(b, c, d)
        // TODO FOR NOW, assuming (reg).

    } else if ((l_paren_count > 0) || (r_paren_count > 0)) {
        cout << "[ERROR] Used parens incorrectly\n";
        return -1;
    }
    
    cout << "Err -- addressing mode not identified\n";
    return -1;
}

