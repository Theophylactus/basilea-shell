#include "extra.h"
#include "run_control.h"
#include "parse_command.h"
#include <algorithm>
#include <iostream>
#include <array>
#include <chrono>
#include <thread>

using std::string;

inline void parse_commands(const std::vector<Command>* commands) {
	for(const auto& cmd : *commands)
		parse_command(cmd);
}

unsigned pending_threads = 0;

static void parse_commands_detached(const std::vector<Command>& commands) {
	parse_commands(&commands);
	--pending_threads;
}

void run_control(const string& script) {
	size_t line_count = 1, col = 0;
	bool is_singlequoted = false, is_doublequoted = false;
	
	for(auto i = script.begin(); i < script.end(); ++i) {
		++col;
		switch(*i) {
			/* For debug purposes, we keep track of which line and column we are in */
			case '\n':
				++line_count;
				col = 0;
			break;
			
			case '\'':
				is_singlequoted = !is_singlequoted;
			break;
			
			case '"':
				is_doublequoted = !is_doublequoted;
			break;
			
			if(is_singlequoted || is_doublequoted) continue;
			
			case '@':
				auto brackets_positions = extra::find_delimiters(i + 1, script.end(), '{');
				auto f_curly = brackets_positions.first;
				auto l_curly = brackets_positions.second;
				
				string controller = extra::trim(string(i + 1, f_curly));
				
				string controlled_code(f_curly + 1, l_curly);
				
				// Finds the controller params, which are different from the controlled code
				/*
				brackets_positions = extra::find_delimiters(i, f_curly, '(');
				string parameter(brackets_positions.first + 1, brackets_positions.second);*/
				
				// If the snippet of contolled code contains another control structure, run it as such
				if(extra::find_unquoted(controlled_code, '@') != string::npos) {
					run_control(controlled_code);
				}
				
				std::vector<Command> commands = get_script_commands(controlled_code, line_count, col);
				
				/* We run the controlled code in the way its controller is supposed to */
				if(controller == "exercere") {
					while(true)
						parse_commands(&commands);
				}
				else if(controller == "agere") {
					parse_commands(&commands);
				}
				else if(controller == "solvere") {
					/* We increase the counter here and not in parse_commands_detached(), because this current thread may finish 
					 * before the new detached thread has time to increase the pending_threads. This would cause the entire 
					 * program to end its execution normally... and also forget about the detached threads */
					++pending_threads;
					std::thread(parse_commands_detached, commands).detach();
				}
				else {
					std::cout << "Error: estructura de control no reconocida: '" << controller << "'\n";
					exit(2);
				}

			break;
		}
	}
	
	/* Waits for the ongoing threads to finish. When a thread is created, we increase the counter by one. When such thread 
	 * finishes, it decreses it by one */
	while(pending_threads != 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		
	// https://www.youtube.com/watch?v=3ZxZPeXPaM4
}
