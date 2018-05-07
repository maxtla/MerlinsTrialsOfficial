#ifndef SFMLSOUND_H
#define SFMLSOUND_H
#include <SFML\Audio.hpp>
#include <string>

class SfmlSound
{
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;

public:
	SfmlSound();
	~SfmlSound();

	void playSound(std::string fileName);
	void stopSound();
	void pauseSound();
	void resumeSound();

};



#endif
