#include "world.h"
#include "world.h"
#include "../Utils/logger.hpp"
Logger world_logger("WORLD");

#include <unordered_set>

void World::DeleteOutOfBoundObjects() {
	std::unordered_set<id_t> objects_for_delete;
	for (auto& object : objects_) {
		if (ObjectInterception(*dynamic_cast<Object*>(this), *std::dynamic_pointer_cast<Object>(object.second)) == std::nullopt) {
			objects_for_delete.insert(object.first);
		}
	}

	// LOGGING
	if (!objects_for_delete.empty()) {
		world_logger << "objects to delete: ";
		for (auto id : objects_for_delete) {
			world_logger << id << ", ";
		}
		world_logger << std::endl;
	}

	for (auto id : objects_for_delete) {
		objects_.erase(id);
	}
}

void World::ProccessCollisions(DynObjectP& o1, DynObjectP& o2) {
	auto interception_optional = ObjectInterception(*o1, *o2);
	if (!interception_optional.has_value()) {
		return;
	}
	auto interception = interception_optional.value();
	// dimention of interception
	size_t interception_dimention;
	if (interception.r()[0] < interception.r()[1]) {
		interception_dimention = 0;
	} else {
		interception_dimention = 1;
	}

	// new coordinates
	// o1 is left to o2
	int o1_o2 = o1->p()[interception_dimention] < o2->p()[interception_dimention];
	o1->SetP(o1->p() + (interception.r() * o2->mass() / (o1->mass() + o2->mass())).Projection(interception_dimention) * (1 - 2 * o1_o2));
	o2->SetP(o2->p() + (interception.r() * o1->mass() / (o1->mass() + o2->mass())).Projection(interception_dimention) * (-1 + 2 * o1_o2));

	// new speeds
	//auto common_bouncy = std::min(o1->elastic(), o2->elastic());
	auto common_bouncy = (o1->elastic() + o2->elastic()) / 2;

	// v1 + dv1 = v1'
	// dv1 = v1' - v1
	vector2d bouncy_delta_v1 = (o2->speed() - o1->speed()).Projection(interception_dimention) * 2 * o2->mass() / (o1->mass() + o2->mass());
	vector2d bouncy_delta_v2 = (o1->speed() - o2->speed()).Projection(interception_dimention) * 2 * o1->mass() / (o1->mass() + o2->mass());
	// v'(m1 + m2) == v1m1 + m2v2
	// v' = (v1m1 + m2v2) / (m1 + m2)
	vector2d nonbouncy_delta_v1 = (o1->Impulse() + o2->Impulse()).Projection(interception_dimention) / (o1->mass() + o2->mass()) - o1->speed().Projection(interception_dimention);
	vector2d nonbouncy_delta_v2 = (o1->Impulse() + o2->Impulse()).Projection(interception_dimention) / (o1->mass() + o2->mass()) - o2->speed().Projection(interception_dimention);

	o1->AddSpeed(bouncy_delta_v1 * common_bouncy + nonbouncy_delta_v1 * (1 - common_bouncy));
	o2->AddSpeed(bouncy_delta_v2 * common_bouncy + nonbouncy_delta_v2 * (1 - common_bouncy));
}

DynObject& World::AddObject(DynObject* new_object_ptr, bool is_static) {
	return AddObject(std::shared_ptr<DynObject>(new_object_ptr), is_static);
}

DynObject& World::AddObject(DynObjectP new_object, bool is_static) {
	auto id = new_object->id;
	objects_[id] = new_object;
	if (!is_static) {
		objects_[id]->AddForce(default_force_);
	}
	return *objects_[id];
}

DynObjectP World::GetObject(id_t id) {
	return objects_[id];
}

vector2d World::GetDefaultForce() const {
	return default_force_;
}

void World::SetDefaulrForce(const vector2d& new_force) {
	default_force_ = new_force;
}

void World::Tick(double delta) {
	for (auto& obj : objects_) {
		obj.second->Tick(delta);
	}
	for (auto o1 = objects_.begin(); o1 != objects_.end(); ++o1) {
		auto o2 = o1;
		++o2;
		for (; o2 != objects_.end(); ++o2) {
			ProccessCollisions(o1->second, o2->second);
		}
	}

	DeleteOutOfBoundObjects();
}
