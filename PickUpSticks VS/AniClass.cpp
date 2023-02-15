#pragma once

#include <SFML/Graphics.hpp>

class Animation
{

	struct Clip {
		std::vector<sf::Texture> textures;
		bool shouldLoop;

	};

public:

	Animation(sf::Sprite* newAinimatedSprite, std::string newbaseFilePath, std::string newfileType = "png");

	void addClip(std::string clipName, int numFrames, bool newshouldLoop = false);

	void update();

	void play();
	void play(std::string clipToPlay);
	void stop();
	void pause();



private:

	sf::Sprite* animatedSprite;
	std::string baseFilePath;
	std::string fileType;
	Clip* currentClip;
	std::map<std::string, Clip > animation;
	int currentFame;
	sf::Time timePerFrame;
	sf::Clock animationClock;
	bool isPlaying;
};


