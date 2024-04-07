#include <array>
#include <iostream>
#include <vector>

using uc = unsigned char;


template<uc N>
class Tube{
private:
	void update() {
		top_color = elements[0];
		top_color_depth = 0;
		top_zeros = 0;
		correct = true;
		bool had_zero = false;
		for (auto& e : elements) {
			if (e > 0) {
				if (top_color == e) { top_color_depth++; }
				else {
					top_color_depth = 1;
					top_color = e;
				}
				top_zeros = 0;
				if (had_zero) correct = false;
			}
			else {
				++top_zeros;
				had_zero = true;
			}
		}
	}
	const static std::vector<std::array<uc, N>> types_of_tubes(uc i) {
		std::vector < std::array<uc, N>> return_vec;
		if (i > 0) {
			for (const auto& ar : types_of_tubes(i - 1)) {
				if (*(std::min_element(ar.begin(), ar.begin() + i)) == 0) { //If it has zero, can only be continued with zeros
					return_vec.emplace_back(ar);
					continue;
				}
				else {
					uc max_element = *(std::max_element(ar.begin(), ar.begin() + i)); //Max element before index i 
					for (uc new_element = 0; new_element <= max_element + 1; new_element++) {
						auto my_array = ar;
						my_array[i] = new_element;
						return_vec.emplace_back(my_array);
					}
				}
			}
			return return_vec;
		}
		else if (i == 0) {
			std::array<uc, N> ar1, ar2;
			for (int i = 0; i < N; i++) {
				ar1[i] = 0;
				ar2[i] = 0;
			}
			ar2[0] = 1;
			return { ar1, ar2 };
		}
	}
	
public:
	std::array<uc, N> elements; //Zero is the bottom of the tube
	uc size;
	uc top_color;
	uc top_zeros;
	uc top_color_depth;
	bool correct;
	Tube(std::array<uc, N> elements): elements(elements), size(N) {
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
		printf("top_color_depth = %d\n", top_color_depth);
		printf("correct: %s\n\n", correct ? "true" : "false");
	}
	void print() {
		for (int i = 0; i < elements.size(); i++) {
			printf("%d", elements[i]);
			if (i < elements.size() - 1) {
				printf(", ");
			}
		}
		std::cout << std::endl;
	}
	const static std::vector<std::array<uc, N>> types_of_tubes() {
		return types_of_tubes(N-1);
	}
	bool can_pour_to(const Tube<N> &to_tube) const {
		/*
		One can pour, if
		-top_color of to_tube is equal from_tube's top_color or to_tube is empty
		and
		-There are top zeros in to_tube
		and
		-from_tube is not empty
		*/
		if (this == &to_tube) {
			return false; }
		if (((to_tube.top_color == 0) || (to_tube.top_color == top_color)) && to_tube.top_zeros > 0 && top_color > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	void try_pour(Tube<N> &to_tube) {
		if (this->can_pour_to(to_tube)) {
			auto pour_color = top_color;
			uc pour_length = std::min(to_tube.top_zeros, top_color_depth);
			for (uc i = 0; i < pour_length; i++) {
				elements[N-top_zeros- pour_length +i] = 0;
				to_tube.elements[N-to_tube.top_zeros+i] = pour_color;
				//std::cout << "Modified inex: " << to_tube.size - to_tube.top_zeros + i << std::endl;	
			}
			this->update();
			to_tube.update();

		}
		else {
			std::cout << "Pour is not possible." << std::endl;
			return;
		}
	}
	std::pair<Tube<N>, Tube<N>> after_pour(const Tube<N>& to_tube) const {
		Tube<N> t1 = *this;
		Tube<N> t2 = to_tube;
		t1.try_pour(t2);
		return { t1, t2 };
	}
};
