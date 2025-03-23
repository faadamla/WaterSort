#include "Tube.h"
#include <iostream>

std::map<std::vector<unsigned char>, size_t> Tube::type_map;

bool Tube::valid() const
{
	bool has_zero = false;
	for (size_t i = 0; i < elements.size(); ++i) {
		const auto x = elements[elements.size() - 1 - i];
		if (has_zero) {
			if (x == 0) { continue; }
			else { return false; }
		}
		else {
			if (x == 0) {
				has_zero = true;
			}
			else { continue; }
		}
	}
	return true;
}

bool Tube::empty() const
{
	for (const auto x : elements) {
		if (x != 0) {
			return false;
		}
	}
	return true;
}

bool Tube::finished() const
{
	const auto color = elements[0];
	for (const auto x : elements) {
		if (x != color) {
			return false;
		}
	}
	return true;
}

size_t Tube::num_color_change() const
{
	size_t count = 0;
	for (size_t i = 1; i < elements.size(); ++i) {
		if (elements[i] != elements[i - 1]) {
			++count;
		}
	}
	return count;
}

void Tube::fill_to(Tube& to) {
	if (!can_fill_to(to)) {
		return;
	}
	else {
		for (unsigned char i = 0; i < to.top_zeros; ++i) {
			auto& from_elem = elements[top_zeros + i]; // Skip the zeros and start fill the first color out
			if (from_elem == to.top_color && (to.top_zeros - 1) >= i)
			{
				to.elements[to.top_zeros - 1 - i] = from_elem;
				from_elem = 0;
			}
		}
		to.update();
		update();
		return;
	}
}

std::vector<unsigned char> Tube::equivalent(std::map<unsigned char, unsigned char>& color_map) const
{
	unsigned char next_color = std::max_element(color_map.begin(), color_map.end())->second + 1;
	std::vector<unsigned char> eqiv;
	eqiv.reserve(size());
	for (const auto x : elements) {
		if (!color_map.contains(x)) {
			color_map[x] = next_color++;
		}
		eqiv.push_back(color_map[x]);
	}
	return eqiv;

}

std::vector<unsigned char> Tube::equivalent() const
{
	std::map<unsigned char, unsigned char> color_map{ {0,0} };
	return equivalent(color_map);
}

std::vector<std::vector<unsigned char>> Tube::generate_all_types(unsigned char depth)
{
	auto last = std::vector<std::vector<unsigned char>>{ {0}, {1} };
	for (size_t i = 1; i < depth; ++i) {
		std::vector<std::vector<unsigned char>> current;
		for (const auto& v : last) {
			if (v.back() == 0) {
				// if the previous is zero, only then we can continue with zero
				std::vector<unsigned char> copy = v;
				copy.push_back(0);
				current.push_back(copy);
			}
			const auto iter = std::max_element(v.begin(), v.end());
			const unsigned char max = 1 + *iter;
			for (unsigned char x = 1; x < max + 1; ++x) {
				std::vector<unsigned char> copy = v;
				copy.push_back(x);
				current.push_back(copy);
			}

		}
		last = current;
	}
	return last;
}

size_t Tube::calc_type() const
{
	auto equiv = equivalent();
	if (type_map.count(equiv) == 0) {
		auto new_types = generate_all_types(equiv.size());
		auto it = std::max_element(type_map.begin(), type_map.end());
		auto next_index = it == type_map.end() ? 0 : it->second + 1;
		for (const auto& v : new_types) {
			type_map[v] = next_index++;
		}
	}
	//return 42;
	if (type_map.count(equiv) == 0) {
		std::cout << "Error: type not found in map: ";
		for (const auto x : equiv) {
			std::cout << +x << " ";
		}
		std::cout << std::endl;
		return -1;
	}
	else {
		return type_map.at(equiv);
	}
}

void Tube::update()
{
	top_zeros = top_color = 0;
	for (auto e : elements) {
		if (e == 0) {
			++top_zeros;
		}
		else {
			top_color = e;
			break;
		}
	}

	type = valid() ? calc_type() : -1;
}

std::ostream& operator<<(std::ostream& os, Tube const& tube)
{
	for (const auto& x : tube.elements) {
		os << +x << " ";
	}
	os << std::endl;

	return os;
}