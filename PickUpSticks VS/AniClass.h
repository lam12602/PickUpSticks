#pragma once
#include "AniClass.cpp"

Animation::Animation(sf::Sprite* newAinimatedSprite, std::string newbaseFilePath, std::string newfileType)
{
}

void Animation::addClip(std::string clipName, int numFrames, bool newshouldLoop)
{
	Clip newClip;
    for (int i = 0; i < numFrames; ++i)
    {
        newClip.textures.push_back(sf::Texture());
        newClip.textures[i].loadFromFile(baseFilePath + "_" + clipName + "_" + std::to_string(i + 1) + fileType);
        newClip.shouldLoop = newshouldLoop;

        animation[clipName] = newClip;
    }
}

inline void Animation::update()
{
    sf::Time timepassedThisFrame = animationClock.getElapsedTime();

    if (timepassedThisFrame >= timePerFrame)
    {
        animationClock.restart();


        ++currentFrame;
        if (currentFrame >= currentClip->size())
        {
            if (currentClip->shouldLoop)
            {
                currentFrame = 0;
            }
            
        }

        playerSprite.setTexture((*currentClip)[currentFrame]);

    }
}

inline void Animation::play()
{
    isPlaying = true;
}

inline void Animation::play(std::string clipToPlay)
{
    if (animation.find(clipToPlay) != animation.end())
    {
        currentClip = &(animation[clipToPlay]);
        isPlaying true;
    }
}

inline void Animation::stop()
{
    isPlaying false;
    currentFame = 0;
}

inline void Animation::pause()
{
    isPlaying false;
}

