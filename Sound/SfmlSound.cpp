#include "SfmlSound.h"

SfmlSound::SfmlSound()
{
}

SfmlSound::~SfmlSound()
{
}

void SfmlSound::playSound(std::string fileName)
{
	if (!this->buffer.loadFromFile(fileName))
	{
		// handle exception
	}

	this->sound.setBuffer(this->buffer);

	this->sound.play();
	
}

void SfmlSound::stopSound()
{
	if(this->sound.getStatus() == sf::SoundSource::Status::Playing)
		this->sound.stop();	
}

void SfmlSound::pauseSound()
{
	if (this->sound.getStatus() == sf::SoundSource::Status::Playing)
		this->sound.pause();
}

void SfmlSound::resumeSound()
{
	if (this->sound.getStatus() == sf::SoundSource::Status::Paused)
		this->sound.play();
}
