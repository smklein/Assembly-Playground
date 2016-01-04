#ifndef __PARSING_H__
#define __PARSING_H__

#include <string>
#include "opcodes.h"
#include "virtual_system.h"

using namespace std;

/**
 * @param[in/out] s String which is trimmed (no whitespace at start/end).
 */
void trim(string &s);

/**
 * @param[in/out] s String which has all "0x" instances replaced with decimal.
 */
void replace_hex(string &s);

/**
 * Given a raw string representation of an instruction (which opcodes),
 * extract the pieces. Verifies that the instruction has the appropraite
 * number of opcodes.
 *
 * @param[in] vs System (registers + memory).
 * @param[in] raw_command Command which is used to extract components of cmd.
 * @param[out] cmd String version of instruction.
 * @param[out] arg1 String version of first operand (updated if used).
 * @param[out] arg2 String version of second operand (updated if used).
 *
 * @returns Number of operands used on success, -1 on error.
 */
int parse_command(VirtualSystem &vs,
                  string raw_command, string &instruction,
                  string &src_operand, string &dest_operand);

/**
 * Parse an operand string, extracting information about it.
 *
 * @param[in] vs System (registers + memory).
 * @param[in] operand
 * @param[out] operand_info
 */
int parse_operand(VirtualSystem &vs,
                  string &op, ::operand &operand_info);

#endif
