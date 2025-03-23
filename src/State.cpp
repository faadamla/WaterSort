#include <algorithm>
#include "State.h"

State::State(size_t depth, size_t n_tubes, std::vector<unsigned char>& in_vec) {
	if (depth * n_tubes != in_vec.size()) {
		throw std::invalid_argument("Invalid input vector size");
	}
	tubes.reserve(n_tubes);
	for (size_t i = 0; i < n_tubes; ++i) {
		std::vector<unsigned char> tube_vec;
		tube_vec.reserve(depth);
		tube_vec.insert(tube_vec.end(), in_vec.begin() + i * depth, in_vec.begin() + (i + 1) * depth);
		tubes.push_back(Tube(tube_vec));
	}
}

bool State::is_valid() const {
	for (const auto& t : tubes) {
		if (!t.valid()) {
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

State State::equiv() const
{
	State copy = *this;
	std::sort(copy.tubes.begin(), copy.tubes.end());
	std::map<unsigned char, unsigned char> color_map{ {0,0} };
	unsigned char next_color = 1;
	std::vector<Tube> equiv_tube;
	for (const auto& t : copy.tubes) {
		auto eqiv_v = t.equivalent(color_map);
		equiv_tube.push_back({ eqiv_v });
	}
	return State(equiv_tube);
}

bool State::finished() const
{
	for (const auto& t : tubes) {
		if (!t.finished()) {
			return false;
		}
	}
	return true;
}

std::vector<unsigned char> State::to_vec() const
{
	std::vector<unsigned char> result;
	size_t size_ = 0;
	for (const auto& t : tubes) {
		size_ += t.size();
	}
	result.reserve(size_);
	for (const auto& t : tubes) {
		result.append_range(t.to_vec());
	}
	return result;
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