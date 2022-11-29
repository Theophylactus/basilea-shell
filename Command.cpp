#include <vector>
#include "parse_command.h"
#include "Command.h"
#include "extra.h"
#include "Function.h"

Command::Command(const std::string& txt, size_t l, size_t c) : text(txt), line(l), col(c) { }

Arglist Command::get_args() const {
	Arglist args;
	
	bool is_double_quoted = false,
		is_single_quoted = false;
	
	for(size_t x = 0; x < text.length(); ++x) {
		if(text.at(x) == '\'')
			is_single_quoted = !is_single_quoted;
		
		if(text.at(x) == '"')
			is_double_quoted = !is_double_quoted;
			
		if(is_double_quoted || is_single_quoted) continue;
			
		if(text.at(x) == ' ') {
			size_t next_ws = extra::find_unquoted(text, ' ', x+1);
			
			// If there are no further found whitespaces, we set the end of
			// the argument to the end of the string
			if(next_ws == std::string::npos)
				next_ws = text.length();
			
			std::string arg = text.substr(x+1, next_ws-x-1);
			
			/* Detects subcommands in the argument and replaces them with their output. It is important to perform this in this 
			 * specific part of the parsing rather than on the raw text of the command, as the subcommand output could contain 
			 * quotes and break the following parsing procedures. Notice also how we only look for commands where the argument
			 * is not single-quoted, that is, it is not a string literal */
			if(arg.front() != '\'' && arg.back() != '\'' && (arg.find('[') | arg.find(']')) != std::string::npos) {
				std::vector<Command> subcommands = get_script_commands(arg, line, col);
				
				for(Command& subcmd : subcommands) {
					size_t pos = arg.find(subcmd.text);
					arg.replace(pos - 1, subcmd.text.length() + 2, parse_command(subcmd));
				}
			}
			
			if(arg.back() == '"') arg.pop_back();
			if(arg.front() == '"') arg.erase(0, 1);
			if(arg.back() == '\'') arg.pop_back();
			if(arg.front() == '\'') arg.erase(0, 1);
			
			args.add(arg);
			
			// As we already found the next whitespace, we proceed with the iteration from there
			x = next_ws-1;
		}
	}
		
	return args;
}

std::string Command::get_function() const {
	return text.substr(0, extra::find_unquoted(text, ' '));
}
