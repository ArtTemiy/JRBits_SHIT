#pragma once
#include "object.h"

#include <unordered_map>
#include <memory>

typedef std::shared_ptr<DynObject> DynObjectP;

class World : Object {
protected:
	// fields
	std::unordered_map<uint64_t, DynObjectP> objects_;
	vector2d default_force_;

private:
	// methods
	void DeleteOutOfBoundObjects();
	void ProccessCollisions(DynObjectP& o1, DynObjectP& o2);

public:
	World(vector2d world_size, vector2d default_force = { 0, 0 }) : Object(world_size), default_force_(default_force) {}

	DynObject& AddObject(DynObject* new_object_ptr, bool is_static = false);
	DynObject& AddObject(DynObjectP new_object, bool is_static = false);

	DynObjectP GetObject(id_t id);

	vector2d GetDefaultForce() const;
	void SetDefaulrForce(const vector2d& new_force);

	void Tick(double delta);
};