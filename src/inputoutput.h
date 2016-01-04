#ifndef __INPUTOUTPUT_H__
#define __INPUTOUTPUT_H__

#include <string>

#include "shared_constants.h"

using namespace std;

/*
 * I will attempt to follow a convention for I/O in this file.
 *
 * INPUT:
 *  TODO
 *
 * OUTPUT:
 *  output_msg_*: Output which is printed to stdout.
 *  outupt_err_*: Output which is printed to stderr.
 *  output_dbg_*: Output which is printed when debugging.
 *  TODO actually toggle debug
 *
 */

/*      output_msg_*        */

void output_msg_start() {
    cout << "[ASM PLAYGROUND STARTING]\n";
    cout << "Commands include "
         << "[" << HELP_STRING << "],"
         << "[" << QUIT_STRING << "], etc...\n";
}

void output_msg_command_prompt() {
    cout << ">> ";
}

void output_msg_exit() {
    cout << "[EXIT] Exiting playground\n";
}

void output_msg_help() {
    cout << "[HELP] Commands:\n";
    cout << "   Calling convention: AT&T. [CMD   SRC, DEST]\n";
    cout << "   Arch: x86.\n";
    cout << "   Endianness: Little endian.\n";
    cout << REGISTERS_STRING << " -- Print out all register values\n";
    cout << PRINT_STRING << " ADDR -- Print out value at memory address ADDR\n";
    cout << QUIT_STRING << " -- Exit the assembly playground\n";
}

/*      output_err_*        */

void output_err_command_invalid() {
    cerr << "[INVALID COMMAND]" << endl;
}

/*      output_dbg_*        */

void output_dbg_eval_start(const string& cmd) {
    cout << "\t[EVAL] Evaluating: " << cmd << endl;
}

void output_dbg_command_info(const string& cmd, int num_args,
                             const string& src_arg, const string& dest_arg) {
    cout << "\t[EVAL][CMD]: [" << cmd << "]\n";
    cout << "\t[EVAL][# ARGS]: " << num_args << endl;
    if (num_args >= 1)
        cout << "\t[EVAL][SRC]: [" << src_arg << "]\n";
    if (num_args == 2)
        cout << "\t[EVAL][DEST]: [" << dest_arg << "]\n";
}

void output_dbg_parse_src() {
    cout << "\t[EVAL] Parsing src\n";
}

void output_dbg_parse_dest() {
    cout << "\t[EVAL] Parsing dest\n";
}

#endif
