#include "../Function.h"
#include "../extra.h"
#include <stdexcept>
#include <unistd.h>
#include <memory>
#include <string>
#include <vector>
#include <cmath>

using std::string;
using std::vector;
using namespace extra;

/* Defined in Compute.cpp - we're borrowing this function here for internal usage */
long double compute(string expresion);

inline long double workout(const std::string& f, long double x) {
	return compute(replace_all(f, "x", std::to_string(x)));
}

const Params_data Plot::params_data = {
										Param_data("function", typeid(const char*)),
										Param_data("dimensions", 2000ULL),
										Param_data("output-filename", "graph")
										};

string Plot::run(Arglist& args) const {
	prepare_params(&args, params_data);
		
	string f = args.next();
	
	const int WIDTH = std::stoi(args.next());
	
	TilledCanvas canvas(WIDTH/100, WIDTH/100, TilledCanvas::white, 100);
		
	// Draws central axis lines
	for(int x = 0; x < WIDTH; ++x) {
		// X axis
		canvas.paint_pixel(WIDTH/2, x, TilledCanvas::black);

		// Y axis
		canvas.paint_pixel(x, WIDTH/2, TilledCanvas::black);
	}
	
	// Paints each pixel of the line
	// We add 0.0001 in each iteration instead of 1 so that we get more points drawn, 
	// hence rendering a smooth line instead of a dashed line
	for(double x = -WIDTH/200; x < WIDTH/200; x += 0.0001)
		canvas.paint_pixel(x*100 + WIDTH/2, WIDTH/2 - round(workout(f, x) * 100), TilledCanvas::blue);
	
	// Now we proceed to save the canvas
	string out_fname = args.next();
	
	canvas.save(out_fname);
	
	return out_fname + ".png";
}
