#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


int main()

{
#pragma region SetUp
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks", sf::Style::None);

    sf::Texture playerTexture;
    sf::Texture grassTexture;
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

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);



    sf::Sprite GrassSprite;
    GrassSprite.setTexture(grassTexture);



    std::vector<sf::Sprite> grassSprites;
    for (int i = 0; i < 3; ++i)
    {
        grassSprites.push_back(GrassSprite);
    }
    playerSprite.setPosition(sf::Vector2f(100.0f, 100.0f));


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
        window.draw(playerSprite);
        for (int i = 0;i < grassSprites.size(); ++i)
        {
            window.draw(grassSprites[i]);
        }

        window.display();
    }

    return 0;
#pragma endregion


        
}