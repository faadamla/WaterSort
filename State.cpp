#include "Tube.cpp"
#include <set>
#include <list>

using uc = unsigned char;

template<uc numberOfTubes, uc depthOfTube>
class State {
private:
public:
	bool won;
	std::array<Tube<depthOfTube>, numberOfTubes> tubes;
	State(std::array<uc, depthOfTube*numberOfTubes> longArray) {
		std::array<uc, depthOfTube> _array;
		for (uc iTube = 0; iTube < numberOfTubes; iTube++) {
			for (uc i = 0; i < depthOfTube; i++) {
				_array[i] = longArray[iTube * depthOfTube + i];
			}
			tubes[iTube] = Tube<depthOfTube>(_array);
		}
		won = false;
	}
	void print() const {
		for (uc i = 0; i < numberOfTubes; i++) {
			printf("%d: ", i);
			tubes[i].print();
		}
		std::cout << "won: " << std::boolalpha << won << std::endl;
	}
	void print() {
		return const_cast<const State<numberOfTubes, depthOfTube>*>(this)->print();
	}
	State() {
		for (uc i = 0; i < numberOfTubes; i++) {
			tubes[i] = Tube<depthOfTube>();
		}
		won = false;
	}
	bool operator<(const State<numberOfTubes, depthOfTube> &rhs) const
	{
		for (uc i = 0; i < numberOfTubes; i++) {
			for (uc j = 0; j < depthOfTube; j++) {
				if (tubes[i].elements[j] == rhs.tubes[i].elements[j]) continue;
				else if (tubes[i].elements[j] < rhs.tubes[i].elements[j]) return true;
				else if (tubes[i].elements[j] > rhs.tubes[i].elements[j]) return false;
			}
		}

		return false;
	}
	bool operator==(const State<numberOfTubes, depthOfTube>& rhs) const {
		for (uc i = 0; i < numberOfTubes; i++) {
			for (uc j = 0; j < depthOfTube; j++) {
				if (tubes[i].elements[j] == rhs.tubes[i].elements[j]) continue;
				else if (tubes[i].elements[j] < rhs.tubes[i].elements[j]) return false;
				else if (tubes[i].elements[j] > rhs.tubes[i].elements[j]) return false;
			}
		}

		return true;
	}
	std::vector<std::pair<uc, uc>> possibleMoves()const {
		std::vector<std::pair<uc, uc>> moves;
		Tube<depthOfTube> fromTube, toTube;
		for (uc ifrom = 0; ifrom < numberOfTubes; ifrom++) {
			for (uc ito = 0; ito < numberOfTubes; ito++) {
				if (tubes[ifrom].can_pour_to(tubes[ito])) {
					moves.emplace_back(std::pair<uc, uc>({ ifrom, ito }));
				}
			}

		}

		return moves;
	}
	std::vector < State<numberOfTubes, depthOfTube>> possibleNextStates(){
		State<numberOfTubes, depthOfTube> copy_current = *this;
		std::vector < State<numberOfTubes, depthOfTube>> nextStates{};
		for (auto&& [from, to] : this->possibleMoves()) {
			auto&& [afterfrom, afterto] = tubes[from].after_pour(tubes[to]);
			copy_current.tubes[from] = afterfrom;
			copy_current.tubes[to] = afterto;
			nextStates.emplace_back(copy_current);
			copy_current = *this;
		}
		return nextStates;
	}
	std::set<State<numberOfTubes, depthOfTube>> discoverAllStatesFromInitialState() {
		std::set<State<numberOfTubes, depthOfTube>> discoveredStates{};
		std::list<State<numberOfTubes, depthOfTube>> todiscover{};
		todiscover.push_back(*this);
		State<numberOfTubes, depthOfTube> currentState;
		for (; !todiscover.empty(); todiscover.pop_front()) {
			currentState = todiscover.front();
			if (discoveredStates.contains(currentState)) {
				continue;
			}
			else {
				for (auto&& newState : currentState.possibleNextStates()) {
					if (!discoveredStates.contains(newState)) {
						todiscover.push_back(newState);
					}
				}
				discoveredStates.insert(currentState);
			}
		}
		return discoveredStates;
	}
};