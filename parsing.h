#ifndef __PARSING_H__
#define __PARSING_H__

#include <string>
#include "opcodes.h"
#include "virtual_system.h"

using namespace std;

void trim(string &s);
void replace_hex(string &s);

int parse_command(VirtualSystem &vs,
                  string &raw_command, string &cmd,
                  string &arg1, string &arg2);
int parse_argument(VirtualSystem &vs,
                   string &arg, argument &arg_info);

#endif
