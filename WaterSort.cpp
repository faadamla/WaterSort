// WaterSort.cpp : Defines the entry point for the application.
//

#include "WaterSort.h"
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

	cout << endl << "====================================" << endl;

	for (auto ar : t2.types_of_tubes()) {
		for (auto v : ar) {
			printf("%d, ", v);
		}
		cout << endl;
	}


	//std:array<int, 3> a{ 0,1, 2 };
	//std:array<int, 3> b{ a, 42 };
	return 0;
}
