#include "StateManager.h"

void StateManager::switchState(State newState) {
	registeredUsers->endState(currentState);
	this->currentState = newState;
	registeredUsers->initState(currentState);
}
State StateManager::getNextState() {
	if (stateQueue.empty()) {
		return defaultState;
	}
	return stateQueue[0]->state;
}
void StateManager::cleanQueue() {
	for (std::vector<QueuedState*>::iterator it = stateQueue.begin(); it != stateQueue.end(); it++) {
		if (!(*it)->waitForEndRequest) {
			stateQueue.erase(it);
		}
	}
}
void StateManager::sortStateIntoQueue(QueuedState* newState) {
	for (std::vector<QueuedState*>::iterator it = stateQueue.begin(); it != stateQueue.end(); it++) {
		if (!(*it)->state > newState->state) {
			stateQueue.insert(it, newState);
			return;
		}
	}
	stateQueue.push_back(newState);
}

StateManager::StateManager(State defaultState, State initialState) {
	this->defaultState = defaultState;
	this->currentState = initialState;
	suggestState(initialState, true);
}
void StateManager::suggestState(State state, bool waitForEndRequest) {
	QueuedState* queuedState = new QueuedState(state, waitForEndRequest);
	sortStateIntoQueue(queuedState);
}
void StateManager::endState(State state) {
	for (std::vector<QueuedState*>::iterator it = stateQueue.begin(); it != stateQueue.end();) {
		if ((*it)->state == state) {
			stateQueue.erase(it);
			return;
		}
		else {
			++it;
		}
	}
}
State StateManager::getState() {
	return currentState;
}
void StateManager::updateState() {
	State nextState = getNextState();
	cleanQueue();
	if (currentState == nextState) {
		return;
	}
	switchState(nextState);
}
void StateManager::registerUser(InputUser* user, std::vector<State> states) {
	for (std::vector<State>::iterator it = states.begin(); it != states.end(); it++) {
		registeredUsers->registerUser((*it), user);
	}
}
void StateManager::registerKeyboardUser(InputUser* user, std::vector<State> states) {
	for (std::vector<State>::iterator it = states.begin(); it != states.end(); it++) {
		registeredUsers->registerKeyboardUser((*it), user);
	}
}
void StateManager::registerMouseUser(InputUser* user, std::vector<State> states) {
	for (std::vector<State>::iterator it = states.begin(); it != states.end(); it++) {
		registeredUsers->registerMouseUser((*it), user);
	}
}