#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace nsUtil {
class Timer {
protected:
	//The clock time when the timer started
	int _startTicks;

	//The ticks stored when the timer was paused
	int _pausedTicks;

	//The timer status
	bool _paused;
	bool _started;

public:
	Timer(void);
	~Timer(void);

	//The various clock actions
	void start(void);
	void stop(void);
	void pause(void);
	void unpause(void);

	//Gets the timer's time
	int getTicks(void);

	//Checks the status of the timer
	bool isStarted(void);
	bool isPaused(void);
};
}

#endif /*_TIMER_H_*/
