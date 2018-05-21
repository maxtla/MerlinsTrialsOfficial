#include "stdafx.h"
#include "SoundEngine.h"

SoundEngine::SoundEngine()
{
}

SoundEngine::~SoundEngine()
{
}

void SoundEngine::loadMusic(std::string fileName)
{
	if (!this->music.openFromFile(fileName))
	{
		//handle exceptiom
	}
}

void SoundEngine::loadSound(std::string fileName)
{
	if (!this->buffer.loadFromFile(fileName))
	{
		// handle exception

	}

	this->sound.setBuffer(this->buffer);
}

void SoundEngine::playMusic()
{
	this->music.play();
}

void SoundEngine::playSound()
{
	this->sound.play();	
}

void SoundEngine::stopSound()
{
	if(this->sound.getStatus() == sf::SoundSource::Status::Playing)
		this->sound.stop();	
}

void SoundEngine::pauseSound()
{
	if (this->sound.getStatus() == sf::SoundSource::Status::Playing)
		this->sound.pause();
}

void SoundEngine::resumeSound()
{
	if (this->sound.getStatus() == sf::SoundSource::Status::Paused)
		this->sound.play();
}

void SoundEngine::loopSound(bool loop)
{
	this->sound.setLoop(loop);
}

void SoundEngine::setSoundVolume(float volume)
{
	this->sound.setVolume(volume);
}

void SoundEngine::stopMusic()
{
	if (this->music.getStatus() == sf::SoundSource::Status::Playing)
		this->music.stop();
}

void SoundEngine::pauseMusic()
{
	if (this->music.getStatus() == sf::SoundSource::Status::Playing)
		this->music.pause();
}

void SoundEngine::resumeMusic()
{
	if (this->music.getStatus() == sf::SoundSource::Status::Paused)
		this->music.play();
}

void SoundEngine::loopMusic(bool loop)
{
	this->music.setLoop(loop);
}

void SoundEngine::setMusicVolume(float volume)
{
	this->music.setVolume(volume);
}

bool SoundEngine::isPlaying()
{
	bool playing = false;

	if (this->sound.getStatus() == sf::SoundSource::Status::Playing)
		playing = true;
	else if (this->music.getStatus() == sf::SoundSource::Status::Playing)
		playing = true;

	return playing;
}
