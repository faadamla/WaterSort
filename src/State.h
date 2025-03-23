#pragma once

#include "Tube.h"

class State {
public:
	State(const std::vector<Tube>& tubes_) : tubes(tubes_) {};

	State(size_t depth, size_t n_tubes, std::vector<unsigned char>& in_vec);

	inline size_t size() const { return tubes.size(); }
	
	bool is_valid() const;
	
	inline bool can_fill_to(size_t from, size_t to) const {
		return tubes[from].can_fill_to(tubes[to]);
	}
	
	State fill_to(size_t from, size_t to) const;
	
	State equiv() const;

	bool finished() const;

	std::vector<unsigned char> to_vec() const;


	bool operator== (const State& other) const;
	
	bool operator< (const State& other) const;
	
	friend std::ostream& operator<<(std::ostream& os, State const& state);

private:
	std::vector<Tube> tubes;
};