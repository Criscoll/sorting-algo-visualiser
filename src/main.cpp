#include <iostream>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include "./headers/button.hpp"
#include "./headers/menu.hpp"

int main(int, char **)
{

    sf::RenderWindow window(sf::VideoMode(1700, 1200), "Sorting Algo Visualiser", sf::Style::Default);
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
    for (auto i = 0; i < window.getSize().x - 300; i += 2)
    {
        auto newBar = new Bar;
        newBar->height = rand() % (window.getSize().y - 300);
        newBar->posX = i;
        newBar->color = sf::Color::White;
        bars.push_back(*newBar);
    }

    Menu algoMenu({window.getSize().x - 200.f, 10.f}, 0);
    Button bubbleSortBtn("Bubble Sort", {200.f, 50.f}, 20, sf::Color(89, 89, 89), sf::Color::Black, roboto);
    Button startBtn("Start", {200, 50}, 20, sf::Color(89, 89, 89), sf::Color::Black, roboto);

    algoMenu.addButton(bubbleSortBtn);
    algoMenu.addButton(startBtn);

    // bubbleSortBtn.setFont(roboto);
    // bubbleSortBtn.setPosition({window.getSize().x - 300, 0});
    // startBtn.setFont(roboto);
    // startBtn.setPosition({window.getSize().x - 300, 100});

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
                algoMenu.mouseMoved(window);
                break;
            case sf::Event::MouseButtonPressed:
                // add logic here to check whether a start or stop button was pressed
                algoMenu.mouseClicked(window);
                break;
            case sf::Event::Resized:
                sf::FloatRect view(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(view));
                break;
            }
        }

        // clear the window
        window.clear();

        // draw
        // draw > buttons
        // bubbleSortBtn.drawTo(window);
        // startBtn.drawTo(window);
        algoMenu.drawTo(window);

        sf::RectangleShape rectangle;
        // draw > UI Borders
        rectangle.setSize(sf::Vector2f(3.0f, window.getSize().y));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setPosition(window.getSize().x - 250, 0);
        window.draw(rectangle);

        // draw > sorting bars
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
