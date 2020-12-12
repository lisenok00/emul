#include "AudioDriver.h"
#include <iostream>

void real_audiodriver_cb(void * data, Uint8 * stream, int len)
{
	std::cout << "-real_audiodriver-" << std::endl;
	reinterpret_cast<AudioDriver*>(data)->callback(
			reinterpret_cast<short *>(stream),
			size_t(len));
}

AudioDriver::AudioDriver()
{
	_spec.callback = real_audiodriver_cb;
	_spec.userdata = this;
	_spec.channels = 1;
	_spec.format = AUDIO_S16;
	_spec.samples = 128;
	_spec.freq =  11025;
	std::cout << "-Настройка-" << std::endl;

	SDL_AudioSpec obt;

	_dev = SDL_OpenAudioDevice(nullptr, 0, &_spec, &obt, 0);
	SDL_PauseAudioDevice(_dev, 0);
	std::cout << "-Снимаем с паузы-" << std::endl;
	//_vr_audio = clock::now()+std::chrono::seconds(2);

	_level = 0;
}

AudioDriver::~AudioDriver()
{
	SDL_PauseAudioDevice(0, 1);
	std::cout << "-Закрываем-" << std::endl;
	SDL_CloseAudioDevice(_dev);
}

void AudioDriver::callback(short int * buffer, size_t len)
{
	std::cout << len << std::endl;
	for (size_t i = 0; i < len; i++){
		if(!queue.empty()){
			buffer[i] = queue.front(); //передает первый элемент очереди
			queue.pop(); //удаляет первый элемент очереди
			std::cout << queue.front() << std::endl;
		}else{
			buffer[i] = _level;
		}
	}

}
void AudioDriver::add_sam()
{
	std::cout << _level << std::endl;
	queue.push(_level);
}



