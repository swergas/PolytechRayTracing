#include <string>
#include <iostream>

#include "Timer.h"

#define TIMER nsUtil::Timer

TIMER::Timer(void) {
	//Initialize the variables
	_startTicks = 0;
	_pausedTicks = 0;
	_paused = false;
	_started = false;
	//std::cout << "Timer ()" << std::endl;
}

TIMER::~Timer(void) {
}

void TIMER::start(void) {
	//Start the timer
	_started = true;

	//Unpause the timer
	_paused = false;

	//Get the current clock time
	_startTicks = SDL_GetTicks();

	//std::cout << "Timer _started" << std::endl;
}

void TIMER::stop(void) {
	//Stop the timer
	_started = false;

	//Unpause the timer
	_paused = false;
}

void TIMER::pause(void) {
	//If the timer is running and isn't already _paused
	if ((_started == true) && (_paused == false)) {
		//Pause the timer
		_paused = true;

		//Calculate the _paused ticks
		_pausedTicks = SDL_GetTicks() - _startTicks;
	}
}

void TIMER::unpause(void) {
	//If the timer is _paused
	if (_paused == true) {
		//Unpause the timer
		_paused = false;

		//Reset the starting ticks
		_startTicks = SDL_GetTicks() - _pausedTicks;

		//Reset the _paused ticks
		_pausedTicks = 0;
	}
}

int TIMER::getTicks(void) {
	//If the timer is running
	if (_started == true) {
		//If the timer is _paused
		if (_paused == true) {
			//Return the number of ticks when the timer was _paused
			return _pausedTicks;
		} else {
			//Return the current time minus the start time
			return SDL_GetTicks() - _startTicks;
		}
	}

	//If the timer isn't running
	return 0;
}

bool TIMER::isStarted(void) {
	return _started;
}

bool TIMER::isPaused(void) {
	return _paused;
}

#undef TIMER
