#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../object.h"

TEST_CASE("Objects constructors") {
	Object o1({ 3, 4 }, { 5, 6 });
	Object o2({ 1, 2 });
	Object o3;
	REQUIRE(o1.p() == vector2d{ 5, 6 });
	REQUIRE(o1.r() == vector2d{ 3, 4 });
	REQUIRE(o2.p() == vector2d{ 0, 0 });
	REQUIRE(o2.r() == vector2d{ 1, 2 });
	REQUIRE(o3.p() == vector2d{ 0, 0 });
	REQUIRE(o3.r() == vector2d{ 1, 1 });

	REQUIRE_THROWS(Object({ -1, 1 }, { -5, 0 }));
	REQUIRE_THROWS(Object({ 1, -1 }, { -5, 0 }));
	REQUIRE_THROWS(Object({ -1, -2 }, { -5, 0 }));
	REQUIRE_NOTHROW(Object({ 0, 1 }, { -5, 0 }));
	REQUIRE_NOTHROW(Object({ 0, 0 }, { -5, 0 }));
	REQUIRE_THROWS(Object({ 0, -1 }, { -5, 0 }));
}

TEST_CASE("Objects Interception") {
	REQUIRE(ObjectInterception(Object(), Object()).value() == Object());
	REQUIRE(ObjectInterception(Object({ 5, 4 }, { 0, 0 }), Object({ 3, 3 }, { 4, 2 })).value() == Object({ 1, 2 }, { 4, 2 }));
	REQUIRE(ObjectInterception(Object({ 5, 2 }, { 1, 0 }), Object({ 2, 4 }, { 0, 1 })).value() == Object({ 1, 1 }, { 1, 1 }));
	REQUIRE(ObjectInterception(Object({ 3, 3 }, { 0, 0 }), Object({ 1, 2 }, { 1, 2 })).value() == Object({ 1, 1 }, { 1, 2 }));
	REQUIRE(ObjectInterception(Object({ 4, 4 }, { 0, 0 }), Object({ 3, 2 }, { 3, 1 })).value() == Object({ 1, 2 }, { 3, 1 }));
	REQUIRE(ObjectInterception(Object({ 5, 6 }, { 0, 0 }), Object({ 2, 3 }, { 1, 2 })).value() == Object({ 2, 3 }, { 1, 2 }));
	REQUIRE(ObjectInterception(Object({ 2, 2 }, { 0, 1 }), Object({ 2, 1 }, { 3, 0 })).has_value() == false);
	REQUIRE(ObjectInterception(Object({ 2, 2 }, { 0, 1 }), Object({ 2, 1 }, { 3, 0 })) == std::nullopt);
	REQUIRE(ObjectInterception(Object({ 2, 3 }, { 0, 0 }), Object({ 1, 2 }, { 2, 1 })).value() == Object({ 0, 2 }, { 2, 1 }));
	REQUIRE(ObjectInterception(Object({ 2, 3 }, { 0, 0 }), Object({ 2, 1 }, { 1, 3 })).value() == Object({ 1, 0 }, { 1, 3 }));
	REQUIRE(ObjectInterception(Object({ 2, 3 }, { 0, 0 }), Object({ 2, 1 }, { 2, 3 })).value() == Object({ 0, 0 }, { 2, 3 }));
}

TEST_CASE("Dynamic objects") {
	DynObject obj({ 1, 1 }, { 3, 4 }, 10, 0.5);
	REQUIRE(obj.r() == vector2d{ 1, 1 });
	REQUIRE(obj.p() == vector2d{ 3, 4 });
	REQUIRE(obj.mass() == 10);
	REQUIRE(obj.elastic() == 0.5);
	REQUIRE(obj.speed() == vector2d());
	REQUIRE(obj.force() == vector2d());
	obj.AddSpeed({ 1, 1 });
	REQUIRE(obj.speed() == vector2d{ 1, 1 });
	obj.AddForce({ 1, 1 });
	REQUIRE(obj.force() == vector2d{ 1, 1 });
}