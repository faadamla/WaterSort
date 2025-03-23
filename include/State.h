#include<vector>

class Tube;

class State {
public:
	State(std::vector<Tube> tubes_) : tubes(tubes_) {};
private:
	std::vector<Tube> tubes;
};