#include <iostream>
//#include <Windows.h>

#include <SFML/Graphics.hpp>

class Zonner
{
public:
    Zonner(sf::Vector2f size)
    {
        zonner.setSize(size);
        zonner.setFillColor(sf::Color::White);
    }
    void spawn_to_window(sf::RenderWindow& window)
    {
        std::cout << "[DEBUG] Spawn zonner to window;" << "\n";
        window.draw(zonner);
    }
    void set_pos(sf::Vector2f new_pos)
    {
        zonner.setPosition({ new_pos });
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

    Zonner new_zonner({ 50, 50 });

    bool temp_flag = false;
    sf::Vector2i mouse_position;

    sf::Texture textureBackground;
    textureBackground.loadFromFile("152427516.png");

    // Create a sprite
    sf::Sprite spriteBackground;

    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);

    // Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

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
        if (event.type == sf::Event::MouseButtonPressed)
        {
            mouse_position = sf::Mouse::getPosition(window);
            temp_flag = true;
            new_zonner.set_pos(sf::Vector2f(mouse_position));
            //system("pause");
        }
        if (temp_flag == true)
        {
            //std::cout << sf::Mouse::getPosition() << "\n";
            new_zonner.spawn_to_window(window);
            new_zonner.set_pos({ new_zonner.get_zonners().getPosition().x + 1, new_zonner.get_zonners().getPosition().y + 1 });
        }
        window.draw(shape);
        window.display();
        //Sleep(0.9);
    }

    return 0;
}
