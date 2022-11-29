#include "../Function.h"
#include "../extra.h"
#include "../Warningstream.h"
#include "letters.h"
#include <sstream>
#include <iostream>
#include <vector>

using extra::TilledCanvas;

class Letter {
private:
	char symbol;
	unsigned width;
	std::stringstream pattern;
	
public:
	Letter(char symb) : symbol(toupper(symb)) {
		switch(symbol) {
			case 'A':
				 pattern << std::string(reinterpret_cast<char const*>(A), A_len);
			break;
			case 'B':
				 pattern << std::string(reinterpret_cast<char const*>(B), B_len);
			break;
			case 'C':
				 pattern << std::string(reinterpret_cast<char const*>(C), C_len);
			break;
			case 'D':
				 pattern << std::string(reinterpret_cast<char const*>(D), D_len);
			break;
			case 'E':
				 pattern << std::string(reinterpret_cast<char const*>(E), E_len);
			break;
			case 'F':
				 pattern << std::string(reinterpret_cast<char const*>(F), F_len);
			break;
			case 'G':
				 pattern << std::string(reinterpret_cast<char const*>(G), G_len);
			break;
			case 'H':
				 pattern << std::string(reinterpret_cast<char const*>(H), H_len);
			break;
			case 'I':
				 pattern << std::string(reinterpret_cast<char const*>(I), I_len);
			break;
			case 'K':
				 pattern << std::string(reinterpret_cast<char const*>(K), K_len);
			break;
			case 'L':
				 pattern << std::string(reinterpret_cast<char const*>(L), L_len);
			break;
			case 'M':
				 pattern << std::string(reinterpret_cast<char const*>(M), M_len);
			break;
			case 'N':
				 pattern << std::string(reinterpret_cast<char const*>(N), N_len);
			break;
			case 'O':
				 pattern << std::string(reinterpret_cast<char const*>(O), O_len);
			break;
			case 'P':
				 pattern << std::string(reinterpret_cast<char const*>(P), P_len);
			break;
			case 'Q':
				 pattern << std::string(reinterpret_cast<char const*>(Q), Q_len);
			break;
			case 'R':
				 pattern << std::string(reinterpret_cast<char const*>(R), R_len);
			break;
			case 'S':
				 pattern << std::string(reinterpret_cast<char const*>(S), S_len);
			break;
			case 'T':
				 pattern << std::string(reinterpret_cast<char const*>(T), T_len);
			break;
			case 'V':
				 pattern << std::string(reinterpret_cast<char const*>(V), V_len);
			break;
			case 'X':
				 pattern << std::string(reinterpret_cast<char const*>(X), X_len);
			break;
			case 'Y':
				 pattern << std::string(reinterpret_cast<char const*>(Y), Y_len);
			break;
			case 'Z':
				 pattern << std::string(reinterpret_cast<char const*>(Z), Z_len);
			break;
			
			/* Special characters begin here */
			case ',':
				 pattern << std::string(reinterpret_cast<char const*>(COMMA), COMMA_len);
			break;
			case '.':
				 pattern << std::string(reinterpret_cast<char const*>(DOT), DOT_len);
			break;
			case ':':
				 pattern << std::string(reinterpret_cast<char const*>(COLON), COLON_len);
			break;
			case '?':
				 pattern << std::string(reinterpret_cast<char const*>(QUMARK), QUMARK_len);
			break;
			case ' ':
				 pattern << std::string(reinterpret_cast<char const*>(WHITESPACE), WHITESPACE_len);
			break;
			
			default:
				general_warnstream << std::string("Warning: Unknown character '") + symbol + "'";
				symbol = '?';
				pattern << std::string(reinterpret_cast<char const*>(QUMARK), QUMARK_len);
			break;
		}
		
		/* Gets the width of the character, whose pattern is stores in Letter::pattern */
		std::string line;
		std::stringstream pat_copy(pattern.str());
		unsigned width = 0;
		while(getline(pat_copy, line)) {
			/* We get the length of the longest line of the pattern */
			if(line.length() > width)
				width = line.length();
		}
		Letter::width = width;
	}
	
	/* Paints this letter, tile by tile, on a given canvas */
	void paint(TilledCanvas* canv, unsigned beg_x, unsigned beg_y) {
		std::string line;
		unsigned y = 0;
		
		while(getline(Letter::pattern, line)) {
			for(unsigned x = 0; x < line.length(); ++x) {
				if(line.at(x) == '#')
					canv->fill_tile(beg_x + x, beg_y + y, TilledCanvas::golden);
			}
			++y;
		}
	}
	
	/* Returns the amount of tiles that a letter should be distanced from the next char
	 * A's should be -2 tiles appart from V and 0 tiles appart from T's and so on 
	 * Omitting this step would lead to some of the letters looking exageratedly separated from each other */
	int get_spacing(char next_c) {
		next_c = toupper(next_c);
		switch(symbol) {
			case 'A':
				if(next_c == 'V')
					return -2;
				else if(next_c == 'T')
					return 0;
			break;

			case 'V':
				if(next_c == 'A')
					return -2;
			break;
				
			case 'Y':
			case 'T':
				if(next_c == 'A')
					return 0;
			break;
			
			case 'R':
				if(next_c == 'C' || next_c == 'Y' || next_c == 'V')
					return 0;
			break;
			
			case 'O':
				if(next_c == '.')
					return 3;
				if(next_c == 'A')
					return 1;
			break;
			
			case 'L':
				if(next_c == 'V')
					return 0;
			break;
			case ' ':
				return 0;
			break;
		}
		return 2;
	}
	
	// Each character patterns consists of several lines. The longest line determines the width of the character,
	// and it is returned in this function
	unsigned get_width() {
		return width;
	}
	
	// Returns the width (in term of tiles) of a given piece of text
	static unsigned get_txt_width(const std::string& text) {
		unsigned width = 0;
		for(auto it = text.begin(); it != text.end(); ++it) {
			Letter letter(*it);
			width += letter.get_width();
			
			// Adds the spacing from this letter to the following
			if(it < text.end()-1) {
				width += letter.get_spacing(*(it + 1));
			}
		}

		return width;
	}
	
	char get_symbol() {
		return symbol;
	}
};

const Params_data Scriptor::params_data = {
											Param_data("text-to-be-written", typeid(const char*)),
											Param_data("centered", false),
											Param_data("output-filename", "text")
											};
			
std::string Scriptor::run(Arglist& args) const {
	prepare_params(&args, params_data);
	
	constexpr int PADDING = 5;
	
	std::string text_str = args.next();
	
	text_str = extra::replace_all(text_str, "U", "V");
	text_str = extra::replace_all(text_str, "u", "V");
	text_str = extra::replace_all(text_str, "J", "I");
	text_str = extra::replace_all(text_str, "j", "I");
	text_str = extra::replace_all(text_str, "W", "V");
	text_str = extra::replace_all(text_str, "w", "V");
	text_str = extra::replace_all(text_str, "\\n", "\n");
	
	/* Segments the string into a vector containing its lines.
	 * We also store the length of the longest line */
	std::string line;
	std::stringstream text(text_str);
	std::vector<std::string> lines;
	unsigned line_count = 0, width = 0;
	while(getline(text, line)) {
		lines.push_back(line);
		++line_count;
		
		unsigned line_w = Letter::get_txt_width(line);
		if(line_w > width)
			width = line_w;
	}

	// Number of lines times the height of each line (argv[0] is omitted, hence the - 1)
	const unsigned height = line_count * (17 + PADDING*2);
	
	// We do not add height padding, as each letter already has padding on its bottom and it's enough for the lower
	// part of the image to have an esthetical padding
	TilledCanvas canv(width + PADDING*2, height);
	
	if((width | height) > 2500)
		canv = TilledCanvas(width + PADDING*2, height, TilledCanvas::black, 5);
		
	
	bool centered = args.next() == "true" ? true : false;
	
	/* Starts drawing the text, line by line, letter by letter, into the canvas.
	 * pen_x and pen_y serve as reference coordinates for the letters to be drawn */
	unsigned pen_x = PADDING, pen_y = PADDING;
	for(unsigned y = 0; y < line_count; ++y) {
		int linelen = lines.at(y).length();
			
		// Places the horizontal pen in a coordinate for the text to be centered
		if(centered)
			pen_x += (width - Letter::get_txt_width(lines.at(y))) / 2;
		
		/* Paints each letter of this line */
		for(int x = 0; x < linelen; ++x) {
			Letter letter(lines.at(y).at(x));
			
			letter.paint(&canv, pen_x, pen_y);
			
			// Moves the drawing pen
			pen_x += letter.get_width();
			if(x < linelen-1)
				pen_x += letter.get_spacing(lines.at(y).at(x+1));
		}
		pen_x = PADDING;
		pen_y += 17 + PADDING * 2;
	}
	
	canv.save(args.next());
	
	return "true";
}
