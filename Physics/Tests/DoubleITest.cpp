#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../double_i.cpp"

#include <cstdint>
#include <iostream>
#include <vector>
#include <random>

TEST_CASE("FromNumbers_Constructors", "[Constructors]") {
	int a_int = 134;
	float a_float = 179.456;
	double a_double = 38475.38475;
	uint64_t a_uint64_t = 2836412387;
	SECTION("Operator-like") {
		REQUIRE(double_i(a_int) == double_i(static_cast<double>(134)));
		REQUIRE(double_i(a_float) == double_i(static_cast<double>(static_cast<float>(179.456))));
		REQUIRE(double_i(a_double) == double_i(38475.38475));
		REQUIRE(double_i(a_uint64_t) == double_i(2836412387));
		REQUIRE(double_i() == double_i(0.0));
		REQUIRE(double_i(134) == double_i(static_cast<double>(134)));
		REQUIRE(double_i(38475.38475) == double_i(38475.38475));
		REQUIRE(double_i(2836412387) == double_i(2836412387));
		REQUIRE(double_i(0) == double_i(0.0));
	}
	SECTION("Assignment operator [variables]") {
		double_i di_int = a_int;
		double_i di_int_req(static_cast<double>(134));
		double_i di_float = a_float;
		double_i di_float_req(static_cast<double>(static_cast<float>(179.456)));
		double_i di_double = a_double;
		double_i di_double_req(38475.38475);
		double_i di_uint64_t = a_uint64_t;
		double_i di_uint64_t_req(2836412387);
		REQUIRE(di_int == di_int_req);
		REQUIRE(di_float == di_float_req);
		REQUIRE(di_double == di_double_req);
		REQUIRE(di_uint64_t == di_uint64_t_req);
	}
	SECTION("Assignment operator") {
		double_i di_int = 134;
		double_i di_int_req = double_i(static_cast<double>(134));
		double_i di_double = -38475.38475;
		double_i di_uint64_t = 2836412387;
		REQUIRE(di_int == di_int_req);
		REQUIRE(di_double == double_i(static_cast<double>(-38475.38475)));
		REQUIRE(di_uint64_t == double_i(2836412387));
	}
}

TEST_CASE("Copy_Constructors", "[Constructors]") {
	double_i d_i(12378);
	double_i d_i_copy = d_i;
	REQUIRE(d_i == d_i_copy);
}
TEST_CASE("Move_Constructors", "[Constructors]") {
	double_i d_i(57, true);
	double_i d_i_move(57, true);

	REQUIRE(d_i_move == double_i(57, true));
	REQUIRE(d_i == double_i(57, true));
}


// Arithmetics double with double
const int kTestsIterationsNumber = 500;
TEST_CASE("ArithmeticsDoubleDouble", "[Arithmetics]") {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> rand_lims(
		std::numeric_limits<double>::min() + 5,
		std::numeric_limits<double>::max() - 5
	);
	std::uniform_real_distribution<> rand_half(
		std::numeric_limits<double>::min() / 2,
		std::numeric_limits<double>::max() / 2
	);
	std::uniform_real_distribution<> rand_sqrt(
		-(sqrt(std::numeric_limits<double>::max()) - 5),
		sqrt(std::numeric_limits<double>::max()) - 5
	);

	// +, - [basic]
	SECTION("+- basic") {
		for (int i = 0; i < kTestsIterationsNumber; ++i) {
			double a = rand_half(gen), b = rand_half(gen);
			REQUIRE((double_i(a) + double_i(b)).x_ == a + b);
			REQUIRE((double_i(a) + double_i(b)) == double_i(a + b));
			REQUIRE((double_i(a) - double_i(b)).x_ == a - b);
			REQUIRE((double_i(a) - double_i(b)) == double_i(a - b));
		}
	}
	SECTION("*/ basic") {
		for (int i = 0; i < kTestsIterationsNumber; ++i) {
			double a = rand_sqrt(gen), b = rand_sqrt(gen);
			while (b == 0) {
				b = rand_sqrt(gen);
			}
			REQUIRE((double_i(a) * double_i(b)).x_ == a * b);
			REQUIRE((double_i(a) / double_i(b)).x_ == a / b);
		}
	}
	SECTION("*/ special; division by 0") {
		REQUIRE(double_i(5) / double_i() == double_i(5, true));
		REQUIRE(double_i() / double_i() == double_i(1));
		REQUIRE(double_i(1, true) / double_i() == double_i(1, true));
		// devide by inf_
		REQUIRE(double_i(1) / double_i(57, true) == double_i());
		REQUIRE(double_i(0) / double_i(57, true) == double_i());
	}
	SECTION("+- inf") {
		REQUIRE(double_i(30, true) + double_i(5, true) == double_i(35, true));
		REQUIRE(double_i(30, true) + double_i(5) == double_i(30, true));
		REQUIRE(double_i(30, true) + double_i(-30, true) == double_i());
		REQUIRE(double_i(30, true) - double_i(5, true) == double_i(25, true));
		REQUIRE(double_i(30, true) - double_i(5) == double_i(30, true));
		REQUIRE(double_i(30, true) - double_i(30, true) == double_i());
	}
	SECTION("*/ inf") {
		REQUIRE(double_i(30, true) * double_i(5, true) == double_i(150, true));
		REQUIRE(double_i(30, true) * double_i(10) == double_i(300, true));
		REQUIRE(double_i(30) * double_i(10, true) == double_i(300, true));
		REQUIRE(double_i(30, true) / double_i(5, true) == double_i(6));
		REQUIRE(double_i(30, true) / double_i(5) == double_i(6, true));
 	}
}


TEST_CASE("ArithmeticsDoubleNumber", "[Arithmetics]") {
	int a_int = 134;
	float a_float = 179.456;
	double a_double = 38475.38475;
	uint64_t a_uint64_t = 2836412387;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> rand_lims(
		std::numeric_limits<double>::min() + 5,
		std::numeric_limits<double>::max() - 5
	);
	std::uniform_real_distribution<> rand_half(
		std::numeric_limits<double>::min() / 2,
		std::numeric_limits<double>::max() / 2
	);
	std::uniform_real_distribution<> rand_sqrt(
		-(sqrt(std::numeric_limits<double>::max()) - 5),
		sqrt(std::numeric_limits<double>::max()) - 5
	);
	SECTION("+- basic") {
		for (int i = 0; i < kTestsIterationsNumber; ++i) {
			double a = rand_half(gen), b = rand_half(gen);
			REQUIRE(double_i(a) + b == double_i(a + b));
			REQUIRE(double_i(a) - b == double_i(a - b));
			REQUIRE(double_i(a) + static_cast<int>(b) == double_i(a + static_cast<int>(b)));
			REQUIRE(double_i(a) - static_cast<int>(b) == double_i(a - static_cast<int>(b)));
			REQUIRE(double_i(a) + static_cast<float>(b) == double_i(a + static_cast<float>(b)));
			REQUIRE(double_i(a) - static_cast<float>(b) == double_i(a - static_cast<float>(b)));
			REQUIRE(double_i(a) + static_cast<uint64_t>(b) == double_i(a + static_cast<uint64_t>(b)));
			REQUIRE(double_i(a) - static_cast<uint64_t>(b) == double_i(a - static_cast<uint64_t>(b)));
		}
	}
	SECTION("*/ basic") {
		for (int i = 0; i < kTestsIterationsNumber; ++i) {
			double a = rand_sqrt(gen), b = rand_sqrt(gen);
			while (b == 0) {
				b = rand_sqrt(gen);
			}
			REQUIRE(double_i(a) * b == double_i(a * b));
			REQUIRE(double_i(a) / b == double_i(a / b));
			REQUIRE(double_i(a) * static_cast<int>(b) == double_i(a * static_cast<int>(b)));
			REQUIRE(double_i(a) / static_cast<int>(b) == double_i(a / static_cast<int>(b)));
			REQUIRE(double_i(a) * static_cast<float>(b) == double_i(a * static_cast<float>(b)));
			REQUIRE(double_i(a) / static_cast<float>(b) == double_i(a / static_cast<float>(b)));
			REQUIRE(double_i(a) * static_cast<uint64_t>(b) == double_i(a * static_cast<uint64_t>(b)));
			REQUIRE(double_i(a) / static_cast<uint64_t>(b) == double_i(a / static_cast<uint64_t>(b)));
		}
	}
	SECTION("*/ special; devision by 0") {
		REQUIRE(
			double_i(5) / 0 ==
			double_i(5, true)
		);
		REQUIRE(
			double_i(0) / 0 ==
			double_i(1)
		);
		REQUIRE(
			double_i(1, true) / 0 ==
			double_i(1, true)
		);
	}
	SECTION("+- inf") {
		REQUIRE(
			double_i(30, true) + a_int ==
			double_i(30, true)
		);
		REQUIRE(
			double_i(30, true) + a_float ==
			double_i(30, true)
		);
		REQUIRE(
			double_i(30, true) + a_double ==
			double_i(30, true)
		);
		REQUIRE(
			double_i(30, true) + a_uint64_t ==
			double_i(30, true)
		);

		REQUIRE(
			double_i(30, true) - a_int ==
			double_i(30, true)
		);
		REQUIRE(
			double_i(30, true) - a_float ==
			double_i(30, true)
		);
		REQUIRE(
			double_i(30, true) - a_double ==
			double_i(30, true)
		);
		REQUIRE(
			double_i(30, true) - a_uint64_t ==
			double_i(30, true)
		);
	}
	SECTION("*/ inf") {
		REQUIRE(
			double_i(30, true) * a_int ==
			double_i(30 * a_int, true)
		);
		REQUIRE(
			double_i(30, true) * a_float ==
			double_i(30 * static_cast<double>(a_float), true)
		);
		REQUIRE(
			double_i(30, true) * a_double ==
			double_i(30 * a_double, true)
		);
		REQUIRE(
			double_i(30, true) * a_uint64_t ==
			double_i(30 * a_uint64_t, true)
		);

		REQUIRE(
			double_i(30, true) / a_int ==
			double_i(static_cast<double>(30) / a_int, true)
		);
		REQUIRE(
			double_i(30, true) / a_float ==
			double_i(30 / static_cast<double>(a_float), true)
		);
		REQUIRE(
			double_i(30, true) / a_double ==
			double_i(30 / a_double, true)
		);
		REQUIRE(
			double_i(30, true) / a_uint64_t ==
			double_i(static_cast<double>(30) / a_uint64_t, true)
		);
	}
}


// Compose double with double
TEST_CASE("CompositionDoubleDouble", "[Compare]") {
	SECTION("Equality") {
		REQUIRE(double_i() == double_i());
		REQUIRE(double_i(-5) == double_i(-5, false));
		REQUIRE(double_i(57, true) == double_i(57, true));
		REQUIRE(double_i() != double_i(5));
		REQUIRE(double_i(5) != double_i(5, true));
	}
	SECTION("Less") {
		// regular
		REQUIRE(double_i(5) < double_i(10));
		REQUIRE(double_i(-5) < double_i(1));
		REQUIRE(double_i(5, true) < double_i(12, true));
		REQUIRE(double_i(-5, true) < double_i(2, true));
		REQUIRE(double_i(5, false) < double_i(26, true));
		REQUIRE(double_i(534876.345, false) < double_i(26, true));
		REQUIRE(double_i(-5, true) < double_i(-1241, false));
		REQUIRE(double_i(-5, true) < double_i(1243, false));

		// infinities
		REQUIRE(double_i(-5, true) < double_i(1243, true));
		REQUIRE(double_i(985, true) < double_i(1243, true));
		REQUIRE(double_i(-698567, true) < double_i(-1243, true));

		// with equality
		REQUIRE(double_i(123) <= double_i(1214238));
		REQUIRE(double_i(123) <= double_i(123));
	}
	SECTION("Greater") {
		// regular
		REQUIRE(double_i(10) > double_i(5));
		REQUIRE(double_i(1) > double_i(-5));
		REQUIRE(double_i(12, true) > double_i(5, true));
		REQUIRE(double_i(2, true) > double_i(-5, true));
		REQUIRE(double_i(26, true) > double_i(5, false));
		REQUIRE(double_i(26, true) > double_i(534876.345, false));
		REQUIRE(double_i(-1241, false) > double_i(-5, true));
		REQUIRE(double_i(1243, false) > double_i(-5, true));

		// infinities
		REQUIRE(double_i(1243, true) > double_i(-5, true));
		REQUIRE(double_i(1243, true) > double_i(985, true));
		REQUIRE(double_i(-1243, true) > double_i(-698567, true));

		// with equality
		REQUIRE(double_i(1214238) >= double_i(123));
		REQUIRE(double_i(123) >= double_i(123));
	}
}

// Compose double with numbers
TEST_CASE("CompositionDoubleNumber", "[Compare]") {
	SECTION("Equality") {
		// EXPECT_EQ(0, double_i());
		REQUIRE(double_i() == 0);
		REQUIRE(double_i(-5) == -5);
		// EXPECT_EQ(-5, double_i(-5));
		// EXPECT_EQ(-5, double_i(-5, false));
		REQUIRE(double_i(-5, false) == -5);
		REQUIRE(double_i() != 5);
		// EXPECT_NE(0, double_i(5));
		// EXPECT_NE(8, double_i(5, true));
	}
	SECTION("Less") {
		// regular
		REQUIRE(double_i(5) < 10);
		REQUIRE(double_i(-5) < 1);
		REQUIRE(double_i(5, true) < double_i(12, true));
		REQUIRE(double_i(-5, true) < double_i(2, true));
		REQUIRE(double_i(5, false) < double_i(26, true));
		REQUIRE(double_i(534876.345, false) < double_i(26, true));
		REQUIRE(double_i(-5, true) < double_i(-1241, false));
		REQUIRE(double_i(-5, true) < double_i(1243, false));

		// with equality
		REQUIRE(double_i(123) <= 1214238);
		REQUIRE(double_i(123) <= 123);
	}
	SECTION("Greater") {
		// regular
		REQUIRE(double_i(10) > 5);
		REQUIRE(double_i(26, true) > 5);
		REQUIRE(double_i(26, true) > 534876.345);

		// with equality
		REQUIRE(double_i(1214238) >= 123);
		REQUIRE(double_i(123) >= 123);
	}
}