#include <string>
#include <vector>
#include "Command.h"

std::vector<Command> get_script_commands(const std::string& script, size_t origin_line = 1,  size_t origin_col = 0);

std::string parse_command(Command command);
