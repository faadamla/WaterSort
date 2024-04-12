#include <iostream>
#include "Tube.cpp"

using namespace std;

int main()
{
	//cout << "Hello CMake." << std::endl;

	Tube<4> t1({ 0, 1, 2, 3 });
	Tube<4> t2({ 1,3,3,0 });
	Tube<4> t3({ 1,2,3,0 });

	//t1.Describe();	
	cout << "Before pour:" << endl;
	t2.print();
	t3.print();

	auto [t4, t5] = t3.after_pour(t2);
	cout << "After pour2:" << endl;
	t4.print();
	t5.print();

	//t2.try_pour(t3);
	cout << "After pour:" << endl;
	t2.print();
	t3.print();

	cout << endl << "===================types_of_tubes:=================" << endl;

	for (auto ar : t2.types_of_tubes()) {
		for (auto v : ar) {
			printf("%d, ", v);
		}
		cout << endl;
	}

	cout << endl << "===================types_map:=================" << endl;

	Tube<5> t_test;
	for (auto& [key, value] : t_test.type_map()) {
		for (auto v : key) {
			printf("%d, ", v);
		}
		cout << ": " << value << "\n";
	}

	cout << endl << "===================my_type:=================" << endl;
	Tube<4> my_type_test({ 3, 0,0,0 });
	my_type_test.print();
	cout << "my_type: " << my_type_test.my_type();

	cout << endl << "===================Comparison test:=================" << endl;
	cout << "Compare: " << (Tube<4>({ 1,2,3,4 }) < Tube<4>({ 1, 1, 1, 1 }));


	//std:array<int, 3> a{ 0,1, 2 };
	//std:array<int, 3> b{ a, 42 };
	return 0;
}
