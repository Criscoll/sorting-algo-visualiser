
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <unistd.h>

int main(int, char **)
{

    sf::RenderWindow window(sf::VideoMode(500, 500), "Sorting Algo Visualiser", sf::Style::Default);

    struct Bar
    {
        float height;
        float posX;
        sf::Color color;
    };

    std::vector<Bar> bars;

    for (auto i = 0; i < window.getSize().x; i += 2)
    {
        auto newBar = new Bar;
        newBar->height = rand() % window.getSize().y;
        newBar->posX = i;
        newBar->color = sf::Color::White;
        bars.push_back(*newBar);
    }

    int iter = 1, upperLim = bars.size();

    // main program loop
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
            }
        }

        // sort logic for this iteration
        bars[iter - 1].color = sf::Color::White;
        bars[iter].color = sf::Color::Red;
        if (bars[iter].height < bars[iter - 1].height)
        {
            auto temp = bars[iter].height;
            bars[iter].height = bars[iter - 1].height;
            bars[iter - 1].height = temp;
        }

        // clear the window
        window.clear();

        // draw the bars
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

        ++iter;
        if (iter >= upperLim)
        {
            bars[iter].color = sf::Color::White;
            bars[upperLim].color = sf::Color::White;
            iter = 1;
            --upperLim;
        }
    }
}
