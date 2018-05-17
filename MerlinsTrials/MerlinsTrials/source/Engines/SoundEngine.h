#pragma once
#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H
#include <SFML\Audio.hpp>
#include <string>

class SoundEngine
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sf::Music music;

public:
	SoundEngine();
	~SoundEngine();

	void playMusic(std::string fileName);
	void playSound(std::string fileName);
	void stopSound();
	void pauseSound();
	void resumeSound();
	void loopSound(bool loop);
	void setSoundVolume(float volume); // 0-100

	void stopMusic();
	void pauseMusic();
	void resumeMusic();
	void loopMusic(bool loop);
	void setMusicVolume(float volume); // 0-100
	
	bool isPlaying();

};



#endif
