#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../vectorNd.h"

TEST_CASE("Constructors") {
	std::array<double_i, 2> std_array_initializer = { 1, 3 };
	vector2d expected(std_array_initializer);
	vector2d v1(1, 3);
	vector2d v2{ 1, 3 };
	vector2d v3{ 1., 3 };
	vector2d v4{ 1, double_i(3) };
	vector2d v5(v1);
	vector2d v6 = v1;
	REQUIRE(v1 == expected);
	REQUIRE(v2 == expected);
	REQUIRE(v3 == expected);
	REQUIRE(v4 == expected);
	REQUIRE(v5 == expected);
	REQUIRE(v6 == expected);
}

TEST_CASE("Arithmetics") {
	REQUIRE(-vector2d{ 1, 3 } == vector2d{ -1, -3 });
	// basic cases
	REQUIRE(vector2d{ 1, 3 } + vector2d{ 5, -2 } == vector2d{ 6, 1 });
	REQUIRE(vector2d{ 1, 3 } - vector2d{ 5, -2 } == vector2d{ -4, 5 });
	REQUIRE(vector2d{ 1, 3 } * 5 == vector2d{ 5, 15 });
	REQUIRE(vector2d{ 1, 2 } / double_i(2) == vector2d{ 0.5, 1 });
	// special cases inf
	REQUIRE(vector2d{ 1, 3 } + vector2d{ double_i(5, true), -3 } == vector2d{ double_i(5, true), 0 });
	REQUIRE(vector2d{ 1, 3 } * double_i(5, true) == vector2d{ double_i(5, true), double_i(15, true) });
	REQUIRE(vector2d{ 1, double_i(4, true) } / double_i(2, true) == vector2d{ 0, 2 });
	REQUIRE(vector2d{ 1, 3 } / 0 == vector2d{ double_i(1, true), double_i(3, true) });
}

TEST_CASE("Compare") {
	REQUIRE(vector2d{ 1, 3 } == vector2d{ 1, 3 });
	REQUIRE(vector2d{ 1, 3 } != vector2d{ 1, 4 });
}

TEST_CASE("Functional methods and other operators") {
	// [] operator
	vector2d v{ 3, 4 };
	REQUIRE(v[0] == 3);
	REQUIRE(v[1] == 4);
	// Norm
	REQUIRE(v.Norm() == 5);
	REQUIRE(vector2d{ 1, 1 }.Norm() > 1.4);
	REQUIRE(vector2d{ 1, 1 }.Norm() < 1.5);
	// Projection
	REQUIRE(v.Projection(0) == vector2d{ 3, 0 });
	REQUIRE(v.Projection(1) == vector2d{ 0, 4 });
}

TEST_CASE("Special vectors") {
	REQUIRE(V2dOnes() == vector2d{ 1, 1 });
	REQUIRE(V2dE(0) == vector2d{ 1, 0 });
	REQUIRE(V2dE(1) == vector2d{ 0, 1 });
}