#include <gtest/gtest.h>
#include "Tube.h"

TEST(Happy, pass){
	EXPECT_EQ(1, 1);
}

TEST(Tube, constructor) {
	std::vector<unsigned char> a{ 1, 2, 3, 4, 5 };
	Tube ta{ a };
	EXPECT_EQ(5, 5);
}

TEST(Tube, valid) {
	std::vector<unsigned char> a{ 1, 2, 3, 4, 5 };
	std::vector<unsigned char> b{ 0, 2, 3, 4, 5 };
	std::vector<unsigned char> c{ 1, 0, 3, 4, 5 };
	Tube ta{ a };
	Tube tb{ b };
	Tube tc{ c };
	EXPECT_TRUE(ta.is_valid());
	EXPECT_TRUE(tb.is_valid());
	EXPECT_FALSE(tc.is_valid());
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
	EXPECT_EQ(ta, Tube({ 0,0,3,4,5 }));
	EXPECT_EQ(tb, Tube({ 1,1,1,4,5 }));
}

TEST(Tube, equivalent) {
	std::vector<unsigned char> a{ 2, 2, 3, 4, 5 };
	std::vector<unsigned char> b{ 0, 0, 3, 3, 3 };
	std::vector<unsigned char> c{ 1, 2, 3, 4, 6 };
	std::vector<unsigned char> d{ 2, 1, 5, 14, 6 };
	Tube ta{ a };
	Tube tb{ b };
	Tube tc{ c };
	Tube td{ d };
	EXPECT_EQ(ta.equivalent(), Tube({ 1,1,2,3,4 }));
	EXPECT_EQ(tb.equivalent(), Tube({ 0,0,1,1,1 }));
	EXPECT_EQ(tc.equivalent(), Tube({ 1,2,3,4,5 }));
	EXPECT_EQ(td.equivalent(), Tube({ 1,2,3,4,5 }));
	EXPECT_EQ(tc.equivalent(), td.equivalent());
}

TEST(Tube, all_types) {
	auto n1 = Tube::generate_all_types(1).size();
	auto n2 = Tube::generate_all_types(2).size();
	auto n3 = Tube::generate_all_types(3).size();
	auto n4 = Tube::generate_all_types(4).size();
	auto n5 = Tube::generate_all_types(5).size();
	EXPECT_EQ(n1, 2);
	EXPECT_EQ(n2, 4);
	EXPECT_EQ(n3, 9);
	EXPECT_EQ(n4, 24);
	EXPECT_EQ(n5, 76);
}