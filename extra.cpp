#include "extra.h"
#include <sys/stat.h>
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include <random>
#include <vector>

using std::string;
using std::vector;

// Returns a random string, valid as filename, in the folder /tmp/
string extra::temp_file_name() {
	string result = "";
	for(int x = 0; x < 24; x++)
		result += (char)(rand() % 15 + 65);
	
	result = "/tmp/" + result;
	
	struct stat buffer;
	if(stat(result.c_str(), &buffer) == 0)
		return extra::temp_file_name();
	else
		return result;
}

// Turns "    hello " into "hello"
string extra::trim(const string& subject) {
	std::stringstream result;
	bool ended_initial_space = false;
	for(unsigned x = 0; x < subject.length(); ++x) {
		// If from this point of the iteration, the rest of the string is all whitespaces, stop the loop
		if(subject.substr(x, subject.length() - x).find_first_not_of(' ') == string::npos) break;
		// Start reading the string's characters as soon as non-whitespaces are found
		if(ended_initial_space)
			result << subject.at(x);
		else if(subject.at(x) != ' ') {
			result << subject.at(x);
			ended_initial_space = true;
		}
	}
	return result.str();
}

string extra::replace_all(string main_str, const string& target, const string& replacement) {
	while(main_str.find(target) != string::npos)
		main_str.replace(main_str.find(target), target.length(), replacement);
		
	return main_str;
}

/* Returns the sub-string delimited by a given delimiter that has an beginning and an ending character (braces).
 * In the case of nested expressions, the "outer shell" of braced content will be returned. Example:
 * 3-(90*(3+5)) would return 90*(3+5).
 * Remember that T could be a either std::string::iterator or a std::string::const_iterator */
template<typename T>
std::pair<T, T> extra::find_delimiters(const T& begin, const T& end, char delimiter) {
	char open_delim, closing_delim;
	
	switch(delimiter) {
		case ')':
		case '(':
			open_delim = '(', closing_delim = ')';
		break;
		
		case ']':
		case '[':
			open_delim = '[', closing_delim = ']';
		break;
		
		case '}':
		case '{':
			open_delim = '{', closing_delim = '}';
		break;
		
		default:
			throw std::runtime_error("Internal error: called extra::find_delimiters with an unrecognised delimiter. Available delimiters are '(', '[' and '{'");
		break;
	}
	
	T open_delim_pos = end, closing_delim_pos = end;
	
	bool is_first_open_delim = true,
		is_singlequoted = false;
		
	unsigned continue_count = 0;
	
	for(T it = begin; it != end; ++it) {
		if(*it == '\'')
			is_singlequoted = !is_singlequoted;
		
		/* Don't parse quoted text */
		if(is_singlequoted) continue;
			
		if(*it == open_delim) {
			if(is_first_open_delim) {
				open_delim_pos = it;
				is_first_open_delim = false;
			} else
				++continue_count;	
		}	
			
		if(*it == closing_delim) {
			if(continue_count == 0) {
				closing_delim_pos = it;
				break;
			} else --continue_count;
		}
	}
	
	return std::pair<T, T>(open_delim_pos, closing_delim_pos);
}

template std::pair<string::iterator, string::iterator> extra::find_delimiters<string::iterator>(const string::iterator&, const string::iterator&, char);
template std::pair<string::const_iterator, string::const_iterator> extra::find_delimiters<string::const_iterator>(const string::const_iterator&, const string::const_iterator&, char);


// Finds the first occurrence of a given character in a string which is not between double quotes
size_t extra::find_undoublequoted(const string& str, char target, size_t search_begin) {
	bool is_doublequoted = false;
	
	for(size_t x = search_begin; x < str.length(); ++x) {
		if(str.at(x) == '"')
			is_doublequoted = !is_doublequoted;
			
		if(!is_doublequoted) {
			if(str.at(x) == target) {
				return x;
			}
		}
	}

	return std::string::npos;
}
size_t extra::find_unsinglequoted(const string& str, char target, size_t search_begin) {
	bool is_singlequoted = false;
	
	for(size_t x = search_begin; x < str.length(); ++x) {
		if(str.at(x) == '\'')
			is_singlequoted = !is_singlequoted;
			
		if(!is_singlequoted) {
			if(str.at(x) == target) {
				return x;
			}
		}
	}

	return std::string::npos;
}
size_t extra::find_unquoted(const string& str, char target, size_t search_begin) {
	bool is_singlequoted = false, is_doublequoted = false;
	
	for(size_t x = search_begin; x < str.length(); ++x) {
		if(str.at(x) == '"')
			is_doublequoted = !is_doublequoted;
		if(str.at(x) == '\'')
			is_singlequoted = !is_singlequoted;
			
		if(!is_doublequoted && !is_singlequoted) {
			if(str.at(x) == target) {
				return x;
			}
		}
	}

	return std::string::npos;
}

/*
 _____ _ _ _          _  ____                          _ 
|_   _(_) | | ___  __| |/ ___|__ _ _ ____   ____ _ ___| |
  | | | | | |/ _ \/ _` | |   / _` | '_ \ \ / / _` / __| |
  | | | | | |  __/ (_| | |__| (_| | | | \ V / (_| \__ \_|
  |_| |_|_|_|\___|\__,_|\____\__,_|_| |_|\_/ \__,_|___(_)
	
	...starts now!
*/

// Paints a pixel in the canvas. Tiles will be ignored here
bool extra::TilledCanvas::paint_pixel(unsigned x, unsigned y, const Color& c) {
	if(x < canv.at(0).size() && y < canv.size()) {
		canv.at(y).at(x) = c;
		return true;
	} else
		return false;
}

// Initializes the object by filling the canvas with black and adding a gray 5x5 tile grid
// w and h are the height and width of the canvas in term of tiles
// Whilst width and height will represent the width and height of the canvas in term of pixels
extra::TilledCanvas::TilledCanvas(unsigned w, unsigned h, const Color& bg_color, unsigned t_size)
								 : width(w), height(h), tile_size(t_size) {
	width *= tile_size;
	height *= tile_size;
	
	canv.reserve(height);
	
	// Fills the canvas with the background color
	std::vector<Color> r;
	r.reserve(width);
	for(unsigned x = 0; x < width; ++x)
		r.push_back(bg_color);
	
	for(unsigned y = 0; y < height; ++y)
		canv.push_back(r);
	
	// Draws a grid
	for(unsigned y = 0; y < height; y += t_size)
		for(unsigned x = 0; x < width; ++x)
			paint_pixel(x, y, gray);
	
	for(unsigned x = 0; x < width; x += t_size)
		for(unsigned y = 0; y < height; ++y)
			paint_pixel(x, y, gray);
	
}

// Paints a single tile of the grid, given the x and y coordinates in terms of the grid's tiles,
// not in terms of the pixels of the image
void extra::TilledCanvas::fill_tile(unsigned x, unsigned y, const Color& c) {
	int x_beg = x * tile_size + 1;
	int y_beg = y * tile_size + 1;
	
	for(unsigned y = 0; y < tile_size-1; ++y)
		for(unsigned x = 0; x < tile_size-1; ++x)
			paint_pixel(x_beg + x, y_beg + y, c);
}

// Saves the canvas to a PPM file and then tries converting it to PNG
bool extra::TilledCanvas::save(std::string fname) {
	FILE *fp = fopen(fname.c_str(), "wb");

	// Writes the PPM header
	fprintf(fp, "P6\n%d %d\n255\n", width, height);
	
	// Dumps the entire canvas into the file
	for(std::vector<Color>& r : canv) {
		for(Color& c : r)
			// Writes the color pixel to the PPM file
			fwrite(c.data(), 1, 3, fp);
	}
	fclose(fp);
	
	// Converts the image to PNG using imagemagick: if successful, deletes the PPM
	if(system(std::string("convert '" + fname + "' '" + fname + ".png'").c_str()) == 0)
		remove(fname.c_str());
			
	return true;
}
