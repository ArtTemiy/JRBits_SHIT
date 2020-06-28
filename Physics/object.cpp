#include "object.h"

uint64_t Object::next_id = 0;

vector2d Object::r() const {
	return r_;
}

vector2d Object::p() const {
	return p_;
}

vector2d Object::rc() const {
	return p_ + r_;
}

void Object::SetP(const vector2d& new_p) {
	p_ = new_p;
}

void Object::SetR(const vector2d& new_r) {
	r_ = new_r;
}

bool Object::operator==(const Object& other) const {
	return r_ == other.r_ && p_ == other.p_;
}

std::ostream& operator<<(std::ostream& sout, const Object& obj) {
	sout << "Obj:{ p:" << obj.p() << " r:" << obj.r() << " id:" << obj.id << " }";
	return sout;
}

std::optional<Object> ObjectInterception(const Object& o1, const Object& o2) {
	vector2d r = {
		std::min(o1.rc()[0], o2.rc()[0]) - std::max(o1.p()[0], o2.p()[0]),
		std::min(o1.rc()[1], o2.rc()[1]) - std::max(o1.p()[1], o2.p()[1])
	}, p = {
		std::max(o1.p()[0], o2.p()[0]),
		std::max(o1.p()[1], o2.p()[1])
	};
	if (r[0] < 0 || r[1] < 0) {
		return std::nullopt;
	}
	return Object(r, p);
}

double_i DynObject::mass() const {
	return mass_;
}

double_i DynObject::elastic() const {
	return bouncy_;
}

vector2d DynObject::speed() const {
	return speed_;
}

vector2d DynObject::force() const {
	return force_;
}

vector2d DynObject::Impulse() const {
	return speed_ * mass_;
}

DynObject& DynObject::AddForce(vector2d force) {
	force_ += force;
	return *this;
}

DynObject& DynObject::AddSpeed(vector2d speed) {
	speed_ += speed;
	return *this;
}

void DynObject::Tick(double delta) {
	p_ += speed_ * delta + force_ * delta * delta / 2;
	speed_ += force_ * delta;
}

std::ostream& operator<<(std::ostream& sout, const DynObject& obj) {
	sout << "dObj:{ " << *dynamic_cast<const Object*>(&obj) << " mass:" << obj.mass() << " elastic:" << obj.elastic() << " speed:" << obj.speed() << " force:" << obj.force() << " }";
	return sout;
}