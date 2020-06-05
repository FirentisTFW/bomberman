#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{

    sf::VideoMode vm(800, 800);									//Tworzenie objektu videomode - tworzenie ekranu
	sf::RenderWindow window(vm, "Bomberman");

    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);

    sf::Clock clock;

    int i = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time time = clock.getElapsedTime();
		clock.restart().asSeconds();

        i++;

        std::cout << i << std::endl; 

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
