#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

class Zonner
{
public:
    Zonner(sf::Vector2f size)
    {
        zonner.setSize(size);
        zonner.setFillColor(sf::Color::Magenta);
    }
    void spawn_to_window(sf::RenderWindow& window)
    {
        //std::cout << "[DEBUG] Spawn zonner to window;" << "\n";
        window.draw(zonner);
    }
    // Relative to the shape's global position
    void set_pos(sf::Vector2f new_pos)
    {
        zonner.setPosition({ new_pos });
    }
    void set_pos(float x, float y)
    {
        zonner.setPosition(x , y);
    }
    void set_colour(int num)
    {
        if (num == 1)
        {
            zonner.setFillColor(sf::Color::Black);
        }
        else if (num == 2)
        {
            zonner.setFillColor(sf::Color::Blue);
        }
        else if (num == 3)
        {
            zonner.setFillColor(sf::Color::Cyan);
        }
    }
    sf::RectangleShape get_zonners()
    {
        return zonner;
    }
private:
    sf::RectangleShape zonner;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "<<< Title goes here >>>");

    sf::RectangleShape wall({ 100, 50 });
    wall.setFillColor(sf::Color::White);
    wall.setPosition(700, 700);

    Zonner new_zonner({ 15, 15 });

    bool temp_flag = false;

    // https://stackoverflow.com/questions/36448101/2-3-1-set-scale-of-background-texture-to-renderwindow-size

    sf::Texture textureBackground;
    // Create a sprite
    sf::Sprite spriteBackground;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.

    sf::Image image;

    // Attach the texture to the sprite
    // spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    // spriteBackground.setPosition(0, 0);

    float ScaleX;
    float ScaleY;

    if (!textureBackground.loadFromFile("1524275167.png"))
    {
        return -1;
    }
    else
    {
        TextureSize = textureBackground.getSize(); //Get size of texture.
        WindowSize = window.getSize();             //Get size of window.

        ScaleX = (float)WindowSize.x / TextureSize.x;
        ScaleY = (float)WindowSize.y / TextureSize.y;     //Calculate scale.

        std::cout << ScaleX << "\n";
        std::cout << ScaleY << "\n";

        spriteBackground.setTexture(textureBackground);
        spriteBackground.setScale(ScaleX, ScaleY);      //Set scale.

        image = textureBackground.copyToImage();
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clears screen every loop (Shapes constantly redraw to window).
        window.clear();
        window.draw(spriteBackground);
        window.draw(wall);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // https://www.sfml-dev.org/tutorials/2.5/graphics-view.php#coordinates-conversions
            sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            new_zonner.set_pos(event.mouseButton.x, event.mouseButton.y);
            temp_flag = true;
        }
        if (temp_flag == true)
        {
            //std::cout << sf::Mouse::getPosition() << "\n";
            new_zonner.spawn_to_window(window);
            // https://stackoverflow.com/questions/46754875/pixel-with-specyfic-color-is-not-in-the-position-it-was-put-in-sfml
            sf::Color imagecolor = image.getPixel((new_zonner.get_zonners().getPosition().x + 1) / ScaleX, (new_zonner.get_zonners().getPosition().y + 0) / ScaleY);
            //std::cout << "x:" << new_zonner.get_zonners().getPosition().x + 1 << " y: " << new_zonner.get_zonners().getPosition().y + 0 << "\n";
            std::cout << "[DEBUG]: " << (float)imagecolor.toInteger() << "\n";
            // https://en.sfml-dev.org/forums/index.php?topic=23869.0
            //image.setPixel((new_zonner.get_zonners().getPosition().x + 1) / ScaleX, (new_zonner.get_zonners().getPosition().y + 0) / ScaleY, sf::Color::Red);
            textureBackground.loadFromImage(image);
            //std::cout << (window.capture().getPixel(new_zonner.get_zonners().getPosition().x + 1, new_zonner.get_zonners().getPosition().y + 0)).toInteger() << "\n";
            bool temp_switch = true;
            bool turn_around = true;
            int temp_num = 1;
            if ((float)imagecolor.toInteger() == 255) // 255 == Black
            {
                turn_around = true;
                // new_zonner.get_zonners().setFillColor(sf::Color::Blue); Doesn't work, why ?
                new_zonner.set_colour(2);
            }
            else // Hits any other colour. Example: White
            {
                new_zonner.set_colour(3);
                if (temp_num == 1)
                {
                    temp_num = -1;
                }
                else
                {
                    temp_num = 1;
                }
                /*
                if (turn_around == true)
                {
                    if (temp_switch == true)
                    {
                        temp_num = -1;
                        temp_switch = false;
                    }
                    else if (temp_switch == false)
                    {
                        temp_num = 1;
                        temp_switch = true;
                    }
                    turn_around = false;
                }
                */
            }
            new_zonner.set_pos({ new_zonner.get_zonners().getPosition().x + temp_num, new_zonner.get_zonners().getPosition().y + 0 });
        }
        window.display();
        Sleep(2);
    }
    return 0;
}
