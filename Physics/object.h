#pragma once
#include "vectorNd.h"

/*
 * object represented by rectangle with size and place in the space
 */
class Object {
	vector2d r_;	// rectangle (size of rectangle)
	vector2d p_;	// point (left up coner)

public:
	Object() : r_(), p_() {}
	Object(vector2d r = { 1, 1 }, vector2d p = { 0, 0 }) : r_(r), p_(p) {}
	Object(double_i r_width(1), double_i r_height(1), double_i p_x, double_i p_y(0)) : r_(r_width, r_height), p_(p_x, p_y) {}

	vector2d r() const;
	vector2d p() const;
};

/*
 * dynamic object
 * In addition to regular object it has: speed, mass, force, elastic
 */
class DynObject : public Object {
	double_i mass_;
	double_i elastic_;
	vector2d speed_;
	vector2d force_;

public:
	DynObject(vector2d r_ = { 1, 1 }, vector2d p = { 0, 0 }, double_i mass = 1, double_i elastic = 1)
		: Object(r, p), mass_(mass), elastic_(elastic), speed_(), force_() {}

	double_i mass() const;
	double_i elastic() const;
	vector2d speed() const;
	vector2d force() const;

};