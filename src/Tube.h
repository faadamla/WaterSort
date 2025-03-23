#include <vector>
#include <ostream>
#include <map>

// Tube's elements are counted from the top.
class Tube {
public:
	Tube(std::vector<unsigned char> elements_) : elements(elements_) { update(); }



	size_t size() const { return elements.size(); }
	bool is_valid()const;

	bool can_fill_to(const Tube& to) const {
		return to.top_zeros > 0 && to.top_color == top_color;
	}
	void fill_to(Tube& to);

	size_t get_type() const { return type; };
	std::vector<unsigned char> equivalent() const;

	static std::vector<std::vector<unsigned char>> generate_all_types(unsigned char depth);

	friend std::ostream& operator<<(std::ostream& os, const Tube& tube);

	bool operator== (const Tube& other) const {
		return elements == other.elements;
	}

	bool operator< (const Tube& other) const {
		return elements < other.elements;
	}
		
private:
	size_t calc_type() const;
	void update();

	std::vector<unsigned char> elements;
	static std::map<std::vector<unsigned char>, size_t> type_map;
	// followings are updated by update():
	unsigned char top_zeros;
	unsigned char top_color;
	size_t type;
};

std::ostream& operator<<(std::ostream& os, Tube const& tube);