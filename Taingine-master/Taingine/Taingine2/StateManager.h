#pragma once
#include "State.h"
#include "RegisteredUsers.h"

class StateManager{

private:
	class QueuedState {
	public:
		State state;
		bool waitForEndRequest;

		QueuedState(State state, bool waitForEndRequest) {
			this->state = state;
			this->waitForEndRequest = waitForEndRequest;
		}
	};

	State defaultState;

	RegisteredUsers* registeredUsers;

	State currentState;
	std::vector<QueuedState*> stateQueue;

	void switchState(State newState);
	State getNextState();
	void cleanQueue();
	void sortStateIntoQueue(QueuedState* newState);

public:
	StateManager(State defaultState, State initialState);
	void suggestState(State state, bool waitForEndRequest);
	void endState(State state);
	State getState();
	void updateState();
	void registerUser(InputUser* user, std::vector<State> states);
	void registerKeyboardUser(InputUser* user, std::vector<State> states);
	void registerMouseUser(InputUser* user, std::vector<State> states);

};

