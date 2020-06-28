#pragma once
#include "vectorNd.h"
#include <optional>

typedef uint64_t id_t;

/*
 * object represented by rectangle with size and place in the space
 */
class Object {
	static id_t next_id;

public:
	const id_t id;

protected:
	vector2d r_;	// rectangle (size of rectangle)
	vector2d p_;	// point (left up coner)

public:
	Object(const vector2d& r = { 1, 1 }, const vector2d& p = { 0, 0 }) : id(next_id++), r_(r), p_(p) {
		if (r_[0] < 0 || r_[1] < 0) {
			throw std::logic_error("Rectangle vector can't have negative coordinates. vector: " + r_.to_string());
		}
	}
	Object(const Object& other) = default;
	// Object(double_i r_width = 1, double_i r_height = 1 , double_i p_x = 0, double_i p_y =0) : id(next_id++), r_(r_width, r_height), p_(p_x, p_y) {}
	virtual ~Object() = default;

	// Get
	vector2d r() const;
	vector2d p() const;
	// right down corner
	vector2d rc() const;

	// Set
	void SetP(const vector2d& new_p);
	void SetR(const vector2d& new_r);

	bool operator==(const Object& other) const;
};

std::ostream& operator<<(std::ostream& sout, const Object& obj);
std::optional<Object> ObjectInterception(const Object& obj1, const Object& obj2);

/*
 * dynamic object
 * In addition to regular object it has: speed, mass, force, elastic
 */
class DynObject : public Object {
protected:
	double_i mass_;
	double_i bouncy_;
	vector2d speed_;
	vector2d force_;

public:
	DynObject(const vector2d& r = { 1, 1 }, const vector2d& p = { 0, 0 }, double_i mass = 1, double_i elastic = 1)
		: Object(r, p), mass_(mass), bouncy_(elastic), speed_(), force_() {}

	DynObject(const Object& obj, double_i mass = 1, double_i elastic = 1)
		: Object(obj), mass_(mass), bouncy_(elastic), speed_(), force_() {}

	double_i mass() const;
	double_i elastic() const;
	vector2d speed() const;
	vector2d force() const;

	vector2d Impulse() const;

	DynObject& AddForce(vector2d force);
	DynObject& AddSpeed(vector2d force);

	void Tick(double delta);
};

std::ostream& operator<<(std::ostream& sout, const DynObject& obj);