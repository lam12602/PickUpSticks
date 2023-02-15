#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include<cmath>
#include "AniClass.h"

enum class GameState
{
    RUNNING,
    GAME_OVER,
    NUM_GAME_STATES
};


int main()

{
#pragma region SetUp
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    srand(time(NULL));

    

    sf::Texture playerTextureStand;
    sf::Texture grassTexture;
    sf::Texture stickTexture;
    sf::Texture playerTextureWalk1;
    sf::Texture playerTextureWalk2;
    if (!playerTextureStand.loadFromFile("Assets/Player_Stand.png"))
    {
        //error
        std::cout << "load texture failed" << std::endl;
    }
    else
    {
        std::cout << "texture loaded" << std::endl;
    }
    if (!playerTextureWalk1.loadFromFile("Assets/Player_Walk_1.png"))
    {
        //error
        std::cout << "load texture failed" << std::endl;
    }
    else
    {
        std::cout << "texture loaded" << std::endl;
    }
    if (!playerTextureWalk2.loadFromFile("Assets/Player_Walk_2.png"))
    {
        //error
        std::cout << "load texture failed" << std::endl;
    }
    else
    {
        std::cout << "texture loaded" << std::endl;
    }

    if (!grassTexture.loadFromFile("Assets/Grass.png"))
    {
        
        std::cout << "load texture failed" << std::endl;

    }
    if (!stickTexture.loadFromFile("Assets/Stick.png"))
    {
        std::cout << "load texture failed" << std::endl;
    }

    std::vector<sf::Texture> playerWalk;
    int numFrames = 2;
    std::string baseFilePath = "Assets/Player_Walk_";
    std::string fileType = ".png";
    for (int i  = 0; i < numFrames; ++i)
    {
        playerWalk.push_back(sf::Texture());
        playerWalk[i].loadFromFile(baseFilePath + std::to_string(i + 1) + fileType);
    }
    

    std::vector<sf::Texture> playerStand;
    playerStand.push_back(sf::Texture());
    playerStand[0].loadFromFile("Assets/Player_Stand.png");

    std::vector<sf::Texture>* currentClip = &playerStand;


    float framesPerSecond = 12.0f;
    sf::Time timePerFrame = sf::seconds(1.0f / framesPerSecond);
    sf::Clock animationClock;
    int currentFrame = 0;

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTextureStand);



    sf::Sprite GrassSprite;
    GrassSprite.setTexture(grassTexture);

    sf::Sprite StickSprite;
    StickSprite.setTexture(stickTexture);


    std::vector<sf::Sprite> grassSprites;
    for (int i = 0; i < 5; ++i)
    {
        int colourtint = 100 + rand() % 155;
        float grassSize = 0 + rand() % 3;
        GrassSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x) - grassTexture.getSize().x, rand() % (window.getSize().y - grassTexture.getSize().y)));
        GrassSprite.setColor(sf::Color(colourtint, colourtint, colourtint));
        GrassSprite.setScale(grassSize, grassSize);
        grassSprites.push_back(GrassSprite);
    }
    std::vector<sf::Sprite> StickSprites;
    StickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x) - stickTexture.getSize().x, rand() % (window.getSize().y - stickTexture.getSize().y)));
    int stickrotation = 0 + rand() % 360;
    StickSprite.setRotation(stickrotation);
    StickSprites.push_back(StickSprite);
    
    
    playerSprite.setPosition(sf::Vector2f(100.0f, 100.0f));
    playerSprite.setColor(sf::Color::Cyan);
    //playerSprite.setRotation(90);
    //playerSprite.setScale(3.0f, 3.0f);
    playerSprite.setOrigin(playerTextureStand.getSize().x / 2, playerTextureStand.getSize().y / 2);
    
    //load fonts
    sf::Font gameFont;
    gameFont.loadFromFile("Assets/GameFont.ttf");


    //creat text objects
    sf::Text gameTitle;
    gameTitle.setFont(gameFont);
    gameTitle.setString("Pick up Sticks");
    gameTitle.setFillColor(sf::Color::Magenta);
    gameTitle.setOutlineThickness(2.0f);
    gameTitle.setOutlineColor(sf::Color::Black);
    float textwidth = gameTitle.getLocalBounds().width;
    gameTitle.setPosition(window.getSize().x / 2.0f - textwidth / 2.0f, 10);

    sf::Text scoreLabel;
    scoreLabel.setFont(gameFont);
    scoreLabel.setString("0000");
    float scorewidth = scoreLabel.getLocalBounds().width;
    //scoreLabel.setPosition(sf::Vector2f());

    sf::Text timerText;
    timerText.setFont(gameFont);
    timerText.setString("Time left: ");
    timerText.setFillColor(sf::Color::Magenta);
    timerText.setOutlineThickness(2.0f);
    timerText.setOutlineColor(sf::Color::Black);
    timerText.setPosition(window.getSize().x / 400.0f,  10.0f);

    sf::Text ScoreText;
    ScoreText.setFont(gameFont);
    ScoreText.setString("Score:0 ");
    ScoreText.setFillColor(sf::Color::Magenta);
    ScoreText.setOutlineThickness(2.0f);
    ScoreText.setOutlineColor(sf::Color::Black);
    ScoreText.setPosition(100.0f, 10.0f);

    sf::Text GameOver;
    GameOver.setFont(gameFont);
    GameOver.setString("Game Over");
    GameOver.setFillColor(sf::Color::Magenta);
    GameOver.setOutlineThickness(2.0f);
    GameOver.setOutlineColor(sf::Color::Black);
    textwidth = GameOver.getLocalBounds().width;
    GameOver.setPosition(window.getSize().x /2.0f - textwidth / 2.0f, window.getSize().y / 2.0f - 300);
    GameOver.setCharacterSize(60);

    sf::Text restart;
    restart.setFont(gameFont);
    restart.setString("Press enter to restart");
    restart.setFillColor(sf::Color::Magenta);
    restart.setOutlineThickness(2.0f);
    restart.setOutlineColor(sf::Color::Black);
    textwidth = restart.getLocalBounds().width;
    restart.setPosition(window.getSize().x / 2.0f - textwidth / 2.0f, window.getSize().y / 2.0f + 100);
    restart.setCharacterSize(60);

    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");

    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();

    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/Music.ogg");
    gameMusic.setLoop(true);
    gameMusic.play();
    float xDr = 10 - rand() % 21/10.0f;
    float yDr = 10 - rand() % 20/10.0f;

    sf::Vector2f direction(xDr, yDr);
    bool previousDash = false;

    sf::Clock deltaTimeClock;
    sf::Clock overallTimeClock;
    sf::Clock gameTimer;
    sf::Clock stickSpawn;
    int score = 0;
    float stickCooldown = 1;
    float gameDuration = 30;
    GameState currentState = GameState::RUNNING;

#pragma endregion





#pragma region Event
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }
#pragma endregion

#pragma region update
        

        sf::Time deltaTime = deltaTimeClock.restart();
        sf::Time totalTime = overallTimeClock.getElapsedTime();
        float gameTimeFloat = gameTimer.getElapsedTime().asSeconds();
        float remianingTimeFloat = gameDuration - gameTimeFloat;
        std::string timeString = "Time: ";
        timeString += std::to_string((int)ceil(remianingTimeFloat));
        timerText.setString(timeString);

        if (remianingTimeFloat <= 0)
        {
            remianingTimeFloat = 0;
            //GameRunning = false;
            currentState = GameState::GAME_OVER;
        }

        direction.x = 0;
        direction.y = 0;
        if (currentState == GameState::RUNNING)
        {
            if (sf::Joystick::isConnected(1))
            {
                float axisX = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
                float axisY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);

                float deadzone = 25;
                if (abs(axisX) > deadzone)
                    direction.x = axisX / 100.0f;
                if (abs(axisY) > deadzone)
                    direction.y = axisY / 100.0f;

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                direction.x = -1;
                
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                direction.x = 1;
                
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                direction.y = -1;
               
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                direction.y = 1;
                
            }

            if (direction.x != 0 || direction.y != 0)
            {
                currentClip = &playerWalk;
            }
            else
            {
                currentClip = &playerStand;
            }



            float speed = 500;
            sf::Vector2f velocity = direction * speed;
            sf::Vector2f distance = velocity * deltaTime.asSeconds();
            sf::Vector2f newPosition = playerSprite.getPosition() + distance;
            playerSprite.setPosition(newPosition);

            bool dashPress = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(1, 0);

            if (dashPress && !previousDash)
            {
                sf::Vector2f dashPosition = playerSprite.getPosition() + direction * 150.0f;
                playerSprite.setPosition(dashPosition);
            }

            previousDash = dashPress;

            //soawn stick(debug)
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousepositionFloat = (sf::Vector2f)localPosition;
                StickSprite.setPosition(mousepositionFloat);
                int stickrotation = 0 + rand() % 360;
                StickSprite.setRotation(stickrotation);
                StickSprites.push_back(StickSprite);

            }

            if (stickSpawn.getElapsedTime().asSeconds() >= stickCooldown)
            {
                StickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x) - stickTexture.getSize().x, rand() % (window.getSize().y - stickTexture.getSize().y)));
                int stickrotation = 0 + rand() % 360;
                StickSprite.setRotation(stickrotation);
                StickSprites.push_back(StickSprite);
            }

            sf::FloatRect playerbounds = playerSprite.getLocalBounds();

            for (int i = StickSprites.size() - 1; i >= 0; --i)
            {
                sf::FloatRect stickbounds = StickSprites[i].getLocalBounds();
                if (playerbounds.intersects(stickbounds))
                {
                    std::string ScoreString = "Score: ";
                    ScoreString += std::to_string(score);
                    ScoreText.setString(ScoreString);
                    StickSprites.erase(StickSprites.begin() + i);
                }
            }
            sf::Time timepassedThisFrame = animationClock.getElapsedTime();

            if (timepassedThisFrame >= timePerFrame)
            {
                animationClock.restart();
                

                ++currentFrame;
                if (currentFrame >= currentClip->size())
                {
                    currentFrame = 0;
                }

                playerSprite.setTexture((*currentClip)[currentFrame]);

            }

            

        }

        if (currentState == GameState::GAME_OVER)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                StickSprites.clear();
                gameTimer.restart();
                playerSprite.setPosition(sf::Vector2f(100.0f, 100.0f));
                currentState = GameState::RUNNING;
            }
        }
    
#pragma endregion

#pragma region Draw
        window.clear(sf::Color(61, 204, 90));
        
        for (int i = 0;i < grassSprites.size(); ++i)
        {
            window.draw(grassSprites[i]);
            
        }
        for (int i = 0; i < StickSprites.size(); ++i)
        {
            window.draw(StickSprites[i]);
        }
        window.draw(playerSprite);
        window.draw(gameTitle);
        window.draw(timerText);
        if (currentState == GameState::GAME_OVER)
        {
            window.draw(GameOver);
            window.draw(restart);
        }
        window.display();
    }

    return 0;
#pragma endregion


        
}