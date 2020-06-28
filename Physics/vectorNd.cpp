#include "vectorNd.h"
// Everything implemented in .h file
// Templates sucks((

vector2d V2dOnes() {
	return VNdOnes<double_i, 2>();
}

vector2d V2dE(size_t i) {
	return VNdE<double_i, 2>(i);
}