#pragma once
#include <unordered_map>
#include <unordered_set>
#include "State.h"
#include "InputUser.h"
#include <math.h>
#include <iostream>

/*struct hash_state {
	std::size_t operator()(State state) const {
		return state;
	}
};
struct equal_state {
	bool operator()(State lhs, State rhs) const {
		return;
	}
};*/


class RegisteredUsers{

private:
	std::unordered_map<State, std::unordered_set<InputUser*>> registeredMouseUsers;
	std::unordered_map<State, std::unordered_set<InputUser*>> registeredKeyboardUsers;

	void registerInputUser(State state, InputUser* user, std::unordered_map<State, std::unordered_set<InputUser*>> registeredUsers);
	void enableMouseUsers(State state, bool enable);
	void enableKeyboardUsers(State state, bool enable);

public:
	void registerMouseUser(State state, InputUser* user);
	void registerKeyboardUser(State state, InputUser* user);
	void registerUser(State state, InputUser* user);
	void initState(State state);
	void endState(State state);
};

