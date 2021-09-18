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
    shape.setFillColor(sf::Color::Green);

    Zonner new_zonner({ 50, 50 });

    bool temp_flag = false;
    sf::Vector2i position;

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
        
        if (event.type == sf::Event::MouseButtonPressed)
        {
            position = sf::Mouse::getPosition();
            temp_flag = true;
            //system("pause");
        }
        if (temp_flag == true)
        {
            //std::cout << sf::Mouse::getPosition() << "\n";
            new_zonner.spawn_to_window(window);
            new_zonner.set_pos(sf::Vector2f(position));
            window.draw(shape);
        }

        window.display();
        //Sleep(0.9);
    }

    return 0;
}
