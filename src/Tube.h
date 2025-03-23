#include <vector>
#include <ostream>
#include <map>

// Tube's elements are counted from the top.
class Tube {
public:
	Tube(std::vector<unsigned char> elements_) : elements(elements_) { update(); }
	friend std::ostream& operator<<(std::ostream& os, const Tube& tube);

	bool can_fill_to(const Tube& to) const {
		return to.top_zeros > 0 && to.top_color == top_color;
	}

	Tube equivalent() const;
	size_t get_type() const { return type; };
	size_t size() const { return elements.size(); }

	void fill_to(Tube& to);
	bool is_valid()const;

	static std::vector<std::vector<unsigned char>> generate_all_types(unsigned char depth);

	bool operator== (const Tube& other) const {
		return elements == other.elements;
	}

	bool operator< (const Tube& other) const {
		return elements < other.elements;
	}
		
private:
	std::vector<unsigned char> elements;
	unsigned char top_zeros;
	unsigned char top_color;
	size_t calc_type() const;
	void update();
	static std::map<Tube, size_t> type_map;
	size_t type;
};

std::ostream& operator<<(std::ostream& os, Tube const& tube);