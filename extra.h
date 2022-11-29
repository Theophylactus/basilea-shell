#pragma once

#include <string>
#include <vector>
#include <array>
#include <utility>

namespace extra {
	std::string temp_file_name();
	
	std::string trim(const std::string& subject);
	
	std::string replace_all(std::string main_str, const std::string& target, const std::string& replacement);
	
	template<typename T>
	std::pair<T, T> find_delimiters(const T& begin, const T& end, char delim);
	
	/*template<typename T>
	size_t find_unquoted(const std::string& str, T target, size_t search_begin = 0);*/
	size_t find_unquoted(const std::string& str, char target, size_t search_begin = 0);
	size_t find_undoublequoted(const std::string& str, char target, size_t search_begin = 0);
	size_t find_unsinglequoted(const std::string& str, char target, size_t search_begin = 0);
	
	using Color = std::array<unsigned char, 3>;
	
	class TilledCanvas {
	private:
		std::vector<std::vector<Color>> canv;
		unsigned width, height, tile_size;
		
	public:
		static constexpr Color white = {255, 255, 255},
								black = {0, 0, 0},
								gray = {100, 100, 100},
								blue = {0, 0, 255},
								golden = {255, 255, 128};
		
		bool paint_pixel(unsigned x, unsigned y, const Color& c);
		
		TilledCanvas(unsigned w, unsigned h, const Color& bg_color = black, unsigned t_size = 10);
		
		void fill_tile(unsigned x, unsigned y, const Color& c = white);
		
		bool save(std::string fname = "canvas");
	};
}
