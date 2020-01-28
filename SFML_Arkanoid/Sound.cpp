#include "Sound.h"

Sound::Sound()
{
	LoadBuffer(brickfilePath);
	LoadBuffer(padfilePath);
	LoadBuffer(readyfilePath);
	LoadBuffer(fartfilePath);
}

void Sound::LoadBuffer(const std::string& filePath)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath))
		return;
	buffers.insert({ filePath, buffer });
}

void Sound::Play(const std::string& filePath)
{
	auto it = buffers.find(filePath);
	if (it != buffers.end())
	{
		sound.setBuffer(buffers[filePath]);
		sound.play();
	}
}
