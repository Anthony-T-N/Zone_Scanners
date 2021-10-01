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
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(1000/2, 1000/2);

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
        // Clears screen every loop (Shapes constantly redraw to window.
        window.clear();
        window.draw(spriteBackground);
        window.draw(wall);
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // https://www.sfml-dev.org/tutorials/2.5/graphics-view.php#coordinates-conversions
            sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            std::cout << "(" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
            new_zonner.set_pos(event.mouseButton.x, event.mouseButton.y);
            image.setPixel(event.mouseButton.x / ScaleX, event.mouseButton.y / ScaleY, sf::Color::Green);
            temp_flag = true;
            //system("pause");
        }
        if (temp_flag == true)
        {
            //std::cout << sf::Mouse::getPosition() << "\n";
            new_zonner.spawn_to_window(window);
            /*
            if (window.GetPixel(posX + a, posY + b) == wallColor)
            {

            }// define wallColor
            */
            // https://stackoverflow.com/questions/46754875/pixel-with-specyfic-color-is-not-in-the-position-it-was-put-in-sfml
            sf::Color imagecolor = image.getPixel((new_zonner.get_zonners().getPosition().x + 1) / ScaleX, (new_zonner.get_zonners().getPosition().y + 0) / ScaleY);
            //std::cout << "x:" << new_zonner.get_zonners().getPosition().x + 1 << " y: " << new_zonner.get_zonners().getPosition().y + 0 << "\n";
            std::cout << "[DEBUG]: " << (float)imagecolor.toInteger() << "\n";
            // https://en.sfml-dev.org/forums/index.php?topic=23869.0
            image.setPixel((new_zonner.get_zonners().getPosition().x + 1) / ScaleX, (new_zonner.get_zonners().getPosition().y + 0) / ScaleY, sf::Color::Red);
            textureBackground.loadFromImage(image);
            //std::cout << (window.capture().getPixel(new_zonner.get_zonners().getPosition().x + 1, new_zonner.get_zonners().getPosition().y + 0)).toInteger() << "\n";
            if (new_zonner.get_zonners().getPosition().x + 1, new_zonner.get_zonners().getPosition().y + 0)
            {
                new_zonner.get_zonners().setFillColor(sf::Color::Red);
            }
            new_zonner.set_pos({ new_zonner.get_zonners().getPosition().x + 1, new_zonner.get_zonners().getPosition().y + 0 });
        }
        //window.draw(shape);
        window.display();
        Sleep(2);
    }
    return 0;
}
