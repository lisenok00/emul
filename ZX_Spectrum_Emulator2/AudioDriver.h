#ifndef AUDIODRIVER_H_
#define AUDIODRIVER_H_

#include <SDL2/SDL.h>
//#include <stack>
#include <queue>
class AudioDriver
{
protected:
	SDL_AudioDeviceID _dev;
	SDL_AudioSpec _spec;


	//using clock = std::chrono::high_resolution_clock;
	//clock::time_point _vr_audio;
	//std::stack<int> stack;
	short _level;
	std::queue<int> queue;
public:
	AudioDriver();
	~AudioDriver();

	void add_sam();

	void callback(short * buffer, size_t len);

	void set_level(short level) {
		_level = level;
	}
};




#endif /* AUDIODRIVER_H_ */
