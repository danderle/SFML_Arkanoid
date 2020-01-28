#pragma once
#include <SFML/Audio.hpp>
#include <map>

class Sound
{
public:
	Sound();

	void Play(const std::string& filePath);

private:
	void LoadBuffer(const std::string& filePath);

public:
	const std::string& brickfilePath = "Resources\\arkbrick.wav";
	const std::string& padfilePath = "Resources\\arkpad.wav";
	const std::string& readyfilePath = "Resources\\ready.wav";
	const std::string& fartfilePath = "Resources\\Fart.wav";

private:
	sf::Sound sound;
	std::map<std::string, sf::SoundBuffer> buffers;
};

