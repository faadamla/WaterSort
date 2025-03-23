#include <gtest/gtest.h>
#include "Tube.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
	// Expect two strings not to be equal.
	EXPECT_STRNE("hello", "world");
	// Expect equality.
	EXPECT_EQ(7 * 6, 42);
}

TEST(Tube, compare) {
	std::vector<unsigned char> a{ 1, 2, 3, 4, 5 };
	std::vector<unsigned char> b{ 1, 2, 3, 4, 5 };
	std::vector<unsigned char> c{ 1, 2, 3, 4, 6 };
	Tube ta{ a };
	Tube tb{ b };
	Tube tc{ c };
	EXPECT_EQ(ta, tb);
	EXPECT_NE(ta, tc);
	EXPECT_NE(tb, tc);
}

TEST(Tube, fill_to) {
	std::vector<unsigned char> a{ 1, 1, 3, 4, 5 };
	std::vector<unsigned char> b{ 0, 0, 1, 4, 5 };
	std::vector<unsigned char> c{ 0, 0, 3, 4, 5 };
	Tube ta{ a };
	Tube tb{ b };
	Tube tc{ c };
	EXPECT_FALSE(ta.can_fill_to(tc));
	EXPECT_FALSE(tb.can_fill_to(ta));
	EXPECT_FALSE(tb.can_fill_to(tc));
	EXPECT_FALSE(tc.can_fill_to(ta));
	EXPECT_FALSE(tc.can_fill_to(tb));
	EXPECT_TRUE(ta.can_fill_to(tb));
	ta.fill_to(tb);
	EXPECT_EQ(ta, Tube({0,0,3,4,5}));
	EXPECT_EQ(tb, Tube({ 1,1,1,4,5 }));
}
