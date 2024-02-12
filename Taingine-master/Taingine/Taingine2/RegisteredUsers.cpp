#include "RegisteredUsers.h"

void RegisteredUsers::registerInputUser(State state, InputUser* user, std::unordered_map<State, std::unordered_set<InputUser*>> registeredUsers) {

	if (registeredUsers.find(state) == registeredUsers.end()) {
		std::unordered_set<InputUser*> users;
		registeredUsers.insert({ state, users });
	}
	registeredUsers[state].insert(user);
}
void RegisteredUsers::enableMouseUsers(State state, bool enable) {
	std::cout << "registeredUsers - enableMouseUsers called!" << std::endl;
	std::unordered_map<State, std::unordered_set<InputUser*>>::iterator users = registeredMouseUsers.find(state);
	if (users == registeredMouseUsers.end()) {
		return;
	}

	for (std::unordered_set<InputUser*>::iterator it = users->second.begin(); it != users->second.end(); ++it) {
		(*it)->enableMouseUse(enable);
	}
}
void RegisteredUsers::enableKeyboardUsers(State state, bool enable) {
	std::cout << "registeredUsers - enableKeyboardUsers called!" << std::endl;
	std::unordered_map<State, std::unordered_set<InputUser*>>::iterator users = registeredKeyboardUsers.find(state);
	if (users == registeredKeyboardUsers.end()) {
		return;
	}

	for (std::unordered_set<InputUser*>::iterator it = users->second.begin(); it != users->second.end(); ++it) {
		(*it)->enableKeyboardUse(enable);
	}
}

void RegisteredUsers::registerMouseUser(State state, InputUser* user) {
	registerInputUser(state, user, registeredMouseUsers);
}
void RegisteredUsers::registerKeyboardUser(State state, InputUser* user) {
	registerInputUser(state, user, registeredKeyboardUsers);
}
void RegisteredUsers::registerUser(State state, InputUser* user) {
	registerInputUser(state, user, registeredMouseUsers);
	registerInputUser(state, user, registeredKeyboardUsers);
}
void RegisteredUsers::initState(State state) {
	enableMouseUsers(state, true);
	enableKeyboardUsers(state, true);
}
void RegisteredUsers::endState(State state) {
	enableMouseUsers(state, false);
	enableKeyboardUsers(state, false);
}