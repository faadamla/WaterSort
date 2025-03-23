#include <gtest/gtest.h>
#include "State.h"

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