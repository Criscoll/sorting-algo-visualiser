#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
#include "./headers/sorter.hpp"
#include "./headers/button.hpp"
#include "./headers/menu.hpp"
#include "./headers/types.hpp"

int main(int, char **)
{

    sf::RenderWindow window(sf::VideoMode(1700, 1200), "Sorting Algo Visualiser", sf::Style::Default);
    sf::Font roboto;

    if (!roboto.loadFromFile("../src/fonts/Roboto-Medium.ttf"))
    {
        throw("COULD NOT LOAD FONT");
    }

    // create the randomised bars
    std::vector<Bar> drawBars;
    for (auto i = 0; i < window.getSize().x - 300; i += 4)
    {
        Bar newBar;
        newBar.height = rand() % (window.getSize().y - 300);
        newBar.posX = i;
        newBar.color = sf::Color::White;
        drawBars.push_back(newBar);
    }

    Sorter sorter;
    Menu algoMenu({window.getSize().x - 200.f, 10.f}, -1);
    Button bubbleSortBtn("Bubble Sort", {200.f, 50.f}, 20, sf::Color(89, 89, 89), sf::Color::Black, roboto);
    Button mergeSortBtn("Merge Sort", {200, 50}, 20, sf::Color(89, 89, 89), sf::Color::Black, roboto);

    algoMenu.addButton(bubbleSortBtn);
    algoMenu.addButton(mergeSortBtn);

    Button startBtn("Start", {200, 50}, 20, sf::Color(89, 89, 89), sf::Color::Black, roboto);
    startBtn.setPosition({window.getSize().x - 200.f, window.getSize().y - 100.f});

    std::queue<std::vector<Bar>> sortingOrder;

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
                startBtn.mouseMoved(window);
                break;
            case sf::Event::MouseButtonPressed:
                algoMenu.mouseClicked(window);
                if (startBtn.isMouseHovering(window))
                {
                    startBtn.updateActiveState(true);
                    sortingOrder = sorter.bubbleSort(drawBars);
                    std::cout << "Returned from sorter" << std::endl;
                }

                break;
                // case sf::Event::Resized:
                //     sf::FloatRect view(0, 0, event.size.width, event.size.height);
                //     window.setView(sf::View(view));
                //     break;
            }
        }

        // clear the window
        window.clear();

        // draw
        // draw > buttons
        startBtn.drawTo(window);
        algoMenu.drawTo(window);

        sf::RectangleShape rectangle;

        // draw > UI Borders
        rectangle.setSize(sf::Vector2f(3.0f, window.getSize().y));
        rectangle.setFillColor(sf::Color::White);
        rectangle.setPosition(window.getSize().x - 250, 0);
        window.draw(rectangle);

        // draw > sorting bars
        if (!sortingOrder.empty())
        {
            drawBars = sortingOrder.front();
            sortingOrder.pop();
        }

        for (auto i = 0; i < drawBars.size(); ++i)
        {
            rectangle.setSize(sf::Vector2f(4.0f, drawBars[i].height));
            rectangle.setOrigin(0.0f, drawBars[i].height);
            rectangle.setFillColor(drawBars[i].color);
            rectangle.setPosition(drawBars[i].posX, window.getSize().y);
            window.draw(rectangle);
        }

        // end the current frame
        window.display();
    }

    std::cout << "Program Terminated" << std::endl;
}
