#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>


int main()

{
#pragma region SetUp
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    srand(time(NULL));

    

    sf::Texture playerTexture;
    sf::Texture grassTexture;
    sf::Texture stickTexture;
    if (!playerTexture.loadFromFile("Assets/Player_Stand.png"))
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

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);



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
    playerSprite.setOrigin(playerTexture.getSize().x / 2, playerTexture.getSize().y / 2);
    
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

    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");

    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();

    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/Music.ogg");
    gameMusic.setLoop(true);
    gameMusic.play();



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
        window.display();
    }

    return 0;
#pragma endregion


        
}