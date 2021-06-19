#include <iostream>
#include <SFML/Graphics.hpp>

int main(int, char **)
{

    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Testing", sf::Style::Default);
    sf::RectangleShape test(sf::Vector2f(50.0f, 100.0f));
    test.setFillColor(sf::Color::Red);
    test.setPosition(0.0f, 450.0f);

    while (window.isOpen())
    {

        // handle window events
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {

            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                // std::cout << "Window Width: " << evnt.size.width << " Widnow Height: " << evnt.size.height << '\n';
                break;
            }
        }

        // clear the window
        window.clear();

        // draw
        window.draw(test);

        // end the current frame
        window.display();
    }
}
