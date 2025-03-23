#include <gtest/gtest.h>
#include "State.h"

std::vector<unsigned char> vec() {
	return std::vector<unsigned char>({ 1, 1, 3, 4, 0, 0, 1, 4, 0, 1, 3, 4 });
}

Tube ta() {
	return Tube({ 1, 1, 3, 4 });
}

Tube tb() {
	return Tube({ 0, 0, 1, 4 });
}

Tube tc() {
	return Tube({ 0, 1, 3, 4 });
}

Tube t_invalid() {
	return Tube({ 1, 2, 0, 3 });
}

State createState() {
	return State({ ta(), tb(), tc(), tc()});
}

TEST(State, constructor) {
	State state = createState();
	EXPECT_EQ(state.size(), 4);
	auto vec_ = vec();
	state = State(4, 3, vec_);
	EXPECT_EQ(state.size(), 3);
}

TEST(State, to_vec) {
	auto vec_ = vec();
	State state = State(4, 3, vec_);
	EXPECT_EQ(state.to_vec(), vec_);
}

TEST(State, valid) {
	State state = createState();
	EXPECT_TRUE(state.is_valid());
	state = State({ ta(), tb(), tc(), t_invalid() });
	EXPECT_FALSE(state.is_valid());
}

TEST(State, can_fill_to) {
	State state = createState();
	EXPECT_TRUE(state.can_fill_to(0, 1));
	EXPECT_TRUE(state.can_fill_to(0, 2));
	EXPECT_TRUE(state.can_fill_to(1, 2));
	EXPECT_TRUE(state.can_fill_to(2, 1));
	EXPECT_FALSE(state.can_fill_to(1, 0));
	EXPECT_FALSE(state.can_fill_to(2, 0));
}

TEST(State, fill_to) {
	State state = createState();
	auto state2 = state.fill_to(0, 1);
	EXPECT_EQ(state2, State({ Tube({ 0, 0, 3, 4 }), Tube({ 1, 1, 1, 4 }), tc(), tc() }));
	auto state3 = state.fill_to(0, 2);
	EXPECT_EQ(state3, State({ Tube({ 0, 1, 3, 4 }), tb(), Tube({1, 1, 3, 4}), tc()}));
	auto state4 = state.fill_to(1, 2);
	EXPECT_EQ(state4, State({ ta(), Tube({0, 0, 0, 4}), Tube({1, 1, 3, 4}), tc()}));
	auto state5 = state.fill_to(2, 1);
	EXPECT_EQ(state5, State({ ta(), Tube({0, 1, 1, 4}), Tube({0, 0, 3, 4}), tc()}));
}

TEST(State, equiv) {
	State state = createState();
	auto state2 = state.equiv();
	EXPECT_EQ(state2, State({ Tube({ 0,0,1,2 }), Tube({ 0,1,3,2 }), Tube({ 0, 1,3,2 }), Tube({ 1,1,3,2 }) }));
}

TEST(State, finished) {
	State state = createState();
	EXPECT_FALSE(state.finished());
	auto state2 = State({ Tube({ 0,0,0,0 }), Tube({ 1,1,1,1 }), Tube({ 1, 1,1,1 }), Tube({ 3,3,3,3 }) });
	EXPECT_TRUE(state2.finished());
}