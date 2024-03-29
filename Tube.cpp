#include <array>
#include <iostream>

using uc = unsigned char;


template<int N>
class Tube{
private:
	std::array<uc, N> elements;
	void update() {
		top_color = elements[0];
		top_zeros = 0;
		correct = true;
		bool had_zero = false;
		for (auto& e : elements) {
			if (e > 0) {
				top_color = e;
				top_zeros = 0;
				if (had_zero) correct = false;
			}
			else {
				++top_zeros;
				had_zero = true;
			}
		}
	}

public:
	uc size;
	uc top_color;
	uc top_zeros;
	bool correct;
	Tube(std::array<uc, N> elements): elements(elements), size(elements.size()) {
		this->update();
	}
	void Describe() {
		std::cout << "Elements:\n";
		for (auto const& v : elements) {
			printf("%d, ", v);
		}
		std::cout << std::endl;
		printf("Size = %d\n", size);
		printf("top_color = %d\n", top_color);
		printf("top_zeros = %d\n", top_zeros);
	}
};
