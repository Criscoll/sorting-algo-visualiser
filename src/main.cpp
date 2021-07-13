#include <iostream>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "./headers/button.hpp"

int main(int, char **)
{

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Sorting Algo Visualiser", sf::Style::Default);
    sf::Font roboto;

    if (!roboto.loadFromFile("./src/fonts/Roboto-Medium.ttf"))
    {
        throw("COULD NOT LOAD FONT");
    }

    struct Bar
    {
        float height;
        float posX;
        sf::Color color;
    };

    std::vector<Bar> bars;

    for (auto i = 0; i < window.getSize().x - 200; i += 2)
    {
        auto newBar = new Bar;
        newBar->height = rand() % (window.getSize().y - 300);
        newBar->posX = i;
        newBar->color = sf::Color::White;
        bars.push_back(*newBar);
    }

    Button bubbleSortBtn("Bubble Sort", {200, 50}, 20, sf::Color(89, 89, 89), sf::Color::Black);
    Button startBtn("Start", {200, 50}, 20, sf::Color(89, 89, 89), sf::Color::Black);

    bubbleSortBtn.setFont(roboto);
    bubbleSortBtn.setPosition({0, 0});
    startBtn.setFont(roboto);
    startBtn.setPosition({0, 100});

    // main program loop
    while (window.isOpen())
    {
        // handle window events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                startBtn.mouseMoved(window);
                bubbleSortBtn.mouseMoved(window);
                break;
            case sf::Event::MouseButtonPressed:
                // add logic here to check whether a start or stop button was pressed
                startBtn.mouseClicked(window);
                bubbleSortBtn.mouseClicked(window);
                break;
            case sf::Event::Resized:
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
                break;
            }
        }

        // clear the window
        window.clear();

        // draw the sprites
        bubbleSortBtn.drawTo(window);
        startBtn.drawTo(window);

        sf::RectangleShape rectangle;
        for (auto i = 0; i < bars.size(); ++i)
        {
            rectangle.setSize(sf::Vector2f(2.0f, bars[i].height));
            rectangle.setOrigin(0.0f, bars[i].height);
            rectangle.setFillColor(bars[i].color);
            rectangle.setPosition(bars[i].posX, window.getSize().y);
            window.draw(rectangle);
        }

        // end the current frame
        window.display();
    }
}
