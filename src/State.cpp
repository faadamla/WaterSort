#pragma once

#include "State.h"

bool State::is_valid() const {
	for (const auto& t : tubes) {
		if (!t.is_valid()) {
			return false;
		}
	}
	return true;
}

State State::fill_to(size_t from, size_t to) const {
	State new_state = *this;
	new_state.tubes[from].fill_to(new_state.tubes[to]);
	return new_state;
}

bool State::operator== (const State& other) const {
	if (size() != other.size()) {
		return false;
	}
	else {
		for (size_t i = 0; i < size(); ++i)
		{
			if (tubes[i] != other.tubes[i]) {
				return false;
			}
		}
	}
	return true;
}

bool State::operator< (const State& other) const {
	if (size() < other.size()) {
		return true;
	}
	else if (size() > other.size()) {
		return false;
	}
	else {
		for (size_t i = 0; i < size(); ++i)
		{
			if (tubes[i] < other.tubes[i]) {
				return true;
			}
			else if (other.tubes[i] < tubes[i]) {
				return false;
			}
			else { continue; }
		}
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, State const& state) {
	for (const auto& t : state.tubes) {
		os << t;
	}
	os << std::endl;
	return os;
}