#define _USE_MATH_DEFINES
#include <cmath>

typedef double Cell;

double					
	X0 = 200,
	Y0 = 200,
	px = 50,
	py = 50;

Cell f_1(Cell x) {
	return sin(x);
}

Cell x_t(Cell t) {
	return cos(t);
}

Cell y_t(Cell t) {
	return sin(t);
}