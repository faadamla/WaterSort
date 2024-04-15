#include <iostream>
#include "State.cpp"

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
	cout << "Compare: " << (Tube<4>({ 1, 1, 1, 1 }) < Tube<4>({ 1,2,3,4 }));

	cout << endl << "\n\n===================Game::possibleMoves test:=================" << endl;
	State<4, 4> TestGame1({ 1,1,2,0,1,1,2,0,2,2,0,0,3,3,3,3 });
	TestGame1.print();
	auto&& moves = TestGame1.possibleMoves();
	for (auto&& m : moves) {
		printf("%d -> %d\n", m.first, m.second);
	}

	cout << endl << "\n\n===================Game::discoverAllStatesFromInitialState test:=================" << endl;
	const State<4, 4> TestGame2({ 1,2,1,2,1,3,3,2,1,2,3,3,0,0,0,0 });
	TestGame2.print();
	auto && allDiscovered = discoverAllStatesFromInitialState(TestGame2);
	for (auto&& s : allDiscovered) {
		// s.print();
		// cout<<endl;
	}
	cout <<"Total: "<<allDiscovered.size()<<endl;

	cout << endl << "\n\n===================Game::recolorInPlace test:=================" << endl;
	State<3, 4> TestGame3({ 3,1,3,1,2,2,2,2,0,0,0,0 });
	cout <<"Before:\n";
	TestGame3.print();
	cout<<"After sort:\n";
	auto TestGame4 = TestGame3;
	TestGame4.sortTubesInPlace();
	TestGame4.print();
	cout<<"After recolor:\n";
	TestGame4 = TestGame3;
	TestGame4.reColorInPlace();
	TestGame4.print();

	cout << endl << "\n\n===================Game::discoverAllNonEquivalenStatesFromInitialState test:=================" << endl;
	TestGame2.print();
	allDiscovered = discoverAllNonEquivalenStatesFromInitialState(TestGame2);
	for (auto&& s : allDiscovered) {
		s.print();
		cout<<endl;
	}
	cout <<"Total: "<<allDiscovered.size()<<endl;

	std::map<int, double> my_map{ {1,11.0}, {2,22.0} };


	//std:array<int, 3> a{ 0,1, 2 };
	//std:array<int, 3> b{ a, 42 };
	return 0;
}
