#include "Tube.h"

Tube Tube::equivalent() const
{
	std::map<unsigned char, unsigned char> color_map{ {0,0} };
	unsigned char next_color = 1;
	std::vector<unsigned char> eqiv;
	for (const auto x : elements) {
		if (color_map.count(x) == 0) {
			color_map[x]= next_color;
			++next_color;
		}
		eqiv.push_back(color_map[x]);
	}
	return { eqiv };
}


void Tube::fill_to(Tube& to) {
    if (!can_fill_to(to)) {
        return;
    } else {
        for (unsigned char i = 0; i < to.top_zeros; ++i) {
            auto& from_elem = elements[top_zeros+i]; // Skip the zeros and start fill the first color out
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

bool Tube::is_valid() const
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

std::vector<std::vector<unsigned char>> Tube::generate_all_types(unsigned char depth)
{
	auto last = std::vector<std::vector<unsigned char>>{ {0}, {1} };
	for (size_t i = 1; i < depth; ++i) {
		std::vector<std::vector<unsigned char>> current;
		for (const auto& v : last) {
			if (v.back() == 0) {
				std::vector<unsigned char> copy = v;
				copy.push_back(0);
				current.push_back(copy);
			}
			else {
				const auto iter = std::max_element(v.begin(), v.end());
				const unsigned char max = 1 + *iter;
				for (unsigned char x = 0; x < max + 1; ++x) {
					std::vector<unsigned char> copy = v;
					copy.push_back(x);
					current.push_back(copy);
				}
			}
		}
		last = current;
	}
	for (auto& v : last) {
		std::reverse(v.begin(), v.end());
	}
	return last;
}

size_t Tube::calc_type() const
{
	return 42;
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
}

std::ostream& operator<<(std::ostream& os, Tube const& tube)
{
	for (const auto& x : tube.elements) {
		os << +x << " ";
	}
	os << std::endl;

	return os;
}