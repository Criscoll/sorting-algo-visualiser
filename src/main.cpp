#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
#include "./headers/sorter.hpp"
#include "./headers/button.hpp"
#include "./headers/menu.hpp"
#include "./headers/types.hpp"
#include "./headers/constants.hpp"

void randomiseBars(sf::RenderWindow &window, std::vector<Bar> &v)
{
    for (auto i = 0; i < window.getSize().x - 300; i += 3)
    {
        Bar newBar;
        newBar.height = rand() % (window.getSize().y - 300);
        newBar.posX = i;
        newBar.color = BAR_COLOUR_DEFAULT;
        v.push_back(newBar);
    }
}

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
    randomiseBars(window, drawBars);

    Sorter sorter;
    Menu algoMenu({window.getSize().x - 210.f, 10.f}, Algorithm::BubbleSort);
    Button bubbleSortBtn("Bubble Sort", {200.f, 50.f}, 20, BTN_COLOUR_DEFAULT, TEXT_COLOUR_DEFAULT, roboto);
    Button mergeSortBtn("Merge Sort", {200, 50}, 20, BTN_COLOUR_DEFAULT, TEXT_COLOUR_DEFAULT, roboto);
    Button quickSortBtn("Quick Sort", {200, 50}, 20, BTN_COLOUR_DEFAULT, TEXT_COLOUR_DEFAULT, roboto);
    Button insertionSortBtn("Insertion Sort", {200, 50}, 20, BTN_COLOUR_DEFAULT, TEXT_COLOUR_DEFAULT, roboto);
    Button selectionSortBtn("Selection Sort", {200, 50}, 20, BTN_COLOUR_DEFAULT, TEXT_COLOUR_DEFAULT, roboto);

    algoMenu.addButton(bubbleSortBtn);
    algoMenu.addButton(mergeSortBtn);
    algoMenu.addButton(quickSortBtn);
    algoMenu.addButton(insertionSortBtn);
    algoMenu.addButton(selectionSortBtn);

    Button startBtn("Start", {200, 50}, 20, BTN_COLOUR_DEFAULT, TEXT_COLOUR_DEFAULT, roboto);
    Button resetBtn("Reset", {200, 50}, 20, BTN_COLOUR_DEFAULT, TEXT_COLOUR_DEFAULT, roboto);
    startBtn.setPosition({window.getSize().x - 210.f, window.getSize().y - 200.f});
    resetBtn.setPosition({window.getSize().x - 210.f, window.getSize().y - 100.f});

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
                resetBtn.mouseMoved(window);
                break;
            case sf::Event::MouseButtonPressed:
                algoMenu.mouseClicked(window);
                if (startBtn.isMouseHovering(window) && !startBtn.isDisabled())
                {
                    startBtn.updateActiveState(true);
                    startBtn.disable(true);

                    switch (algoMenu.getSelectedIdx())
                    {
                    case Algorithm::BubbleSort:
                        sortingOrder = sorter.bubbleSort(drawBars);
                        break;
                    case Algorithm::MergeSort:
                        sortingOrder = sorter.mergeSort(drawBars);
                        break;
                    case Algorithm::QuickSort:
                        sortingOrder = sorter.quickSort(drawBars);
                        break;
                    case Algorithm::InsertionSort:
                        sortingOrder = sorter.insertionSort(drawBars);
                        break;
                    case Algorithm::SelectionSort:
                        sortingOrder = sorter.selectionSort(drawBars);
                        break;
                    }
                }
                else if (resetBtn.isMouseHovering(window) && !resetBtn.isDisabled())
                {
                    startBtn.updateActiveState(false);
                    startBtn.disable(false);
                    std::queue<std::vector<Bar>>().swap(sortingOrder);
                    drawBars.clear();
                    randomiseBars(window, drawBars);
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
        resetBtn.drawTo(window);
        algoMenu.drawTo(window);

        sf::RectangleShape rectangle;

        // draw > UI Borders
        rectangle.setSize(sf::Vector2f(2.0f, window.getSize().y));
        rectangle.setFillColor(BORDER_COLOUR_DEFAULT);
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
            rectangle.setSize(sf::Vector2f(3.0f, drawBars[i].height));
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
