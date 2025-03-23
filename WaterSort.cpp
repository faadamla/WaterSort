#include <iostream>
#include "src/Tube.h"

int main() {
	auto all = Tube::generate_all_types(4);
	for (const auto& v : all) {
		for (const auto x : v) {
			std::cout << +x << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "========================================" << std::endl;
	
	auto t1 = Tube({ 1, 2, 3, 4 });
	std::cout << t1;

	std::cout << "========================================" << std::endl;

	auto t2 = Tube({ 0,1,1,1 });
	std::cout << t2 << (t2.is_valid() ? "VALID" : "INVALID") << std::endl;
	auto t3 = Tube({ 1,1,1,0 });
	std::cout << t3 << (t3.is_valid() ? "VALID" : "INVALID") << std::endl;

	std::cout << "========================================" << std::endl;

	std::vector<int> v1{ 41,42 };
	std::vector<int> v2{ 41,42 };
	v2.reserve(100);
	std::cout<< (v1 == v2 ? "EQUAL" : "NOT EQUAL");

	std::cout << "========================================" << std::endl;

	auto n1 = Tube::generate_all_types(1).size();
	auto n2 = Tube::generate_all_types(2).size();
	auto n3 = Tube::generate_all_types(3).size();
	auto n4 = Tube::generate_all_types(4).size();
	auto n5 = Tube::generate_all_types(5).size();
	std::cout << n1 << std::endl;
	std::cout << n2 << std::endl;
	std::cout << n3 << std::endl;
	std::cout << n4 << std::endl;
	std::cout << n5 << std::endl;

	return 0;
}