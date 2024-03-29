// WaterSort.cpp : Defines the entry point for the application.
//

#include "WaterSort.h"
#include "Tube.cpp"

using namespace std;

int main()
{
	cout << "Hello CMake." << std::endl;

	Tube<4> t1({ 0, 1, 2, 3 });
	Tube<4> t2({ 3,3,0,0 });

	t1.Describe();
	t2.Describe();
	return 0;
}
