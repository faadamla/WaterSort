#include <iostream>
#include "Game.cpp"

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

	// cout << endl << "===================types_of_tubes:=================" << endl;

	// for (auto ar : t2.types_of_tubes()) {
	// 	for (auto v : ar) {
	// 		printf("%d, ", v);
	// 	}
	// 	cout << endl;
	// }

	cout << endl << "===================types_map:=================" << endl;

	for (auto& [key, value] : type_map<5>) {
		for (auto v : key) {
			printf("%d, ", v);
		}
		cout << ": " << value << "\n";
	}

	cout << endl << "===================my_type:=================" << endl;
	Tube<4> my_type_test({ 3, 0,0,0 });
	my_type_test.print();
	cout << "my_type: " << my_type_test.type;

	cout << endl << "===================Tube Comparison test:=================" << endl;
	cout << "Compare: " << (Tube<4>({ 1, 1, 1, 1 }) < Tube<4>({ 1,2,3,4 }));

	cout << endl << "\n\n===================State::possibleMoves test:=================" << endl;
	State<4, 4> TestGame1({ 1,1,2,0,1,1,2,0,2,2,0,0,3,3,3,3 });
	TestGame1.print();
	auto&& moves = TestGame1.possibleMoves();
	for (auto&& m : moves) {
		printf("%d -> %d\n", m.first, m.second);
	}

	cout << endl << "\n\n===================State::recolorInPlace test:=================" << endl;
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

	cout << endl << "\n\n===================State::discoverAllNonEquivalenStatesFromInitialState test:=================" << endl;
	const State<4, 4> TestGame2({ 1,2,1,2,1,3,3,2,1,2,3,3,0,0,0,0 });
	cout << "Initial state:\n";
	TestGame2.print();
	cout << endl;
	auto allDiscovered = discoverAllNonEquivalenStatesFromInitialState(TestGame2);
	for (auto&& s : allDiscovered) {
		s.print();
		cout<<endl;
	}
	cout <<"Total #: "<<allDiscovered.size()<<endl;

	cout << endl << "\n\n===================Game::factorial test:=================" << endl;
	cout << "10!=" << factorial(10) <<endl;
	cout << "20!=" << factorial(20) <<endl;
	cout << "21!=" << factorial(21) <<endl;

	cout << endl << "\n\n===================Game::numberOfInitialStates test:=================" << endl;
	cout << "Estimated number of unique Initial state for\n";
	for (int numTubes=3; numTubes<11; numTubes++){
		cout << "<"<<numTubes<<",4>: " << numberOfInitialStates(numTubes,4) <<endl;
	}


	cout << endl << "\n\n===================Game::allUniqueInitialState test:=================" << endl;
	auto InitialStatesSet = allUniqueInitialState<6,4>();
	cout << "Number of unique Initial state for <6,4>: " << InitialStatesSet.size() <<endl;



	return 0;
}
