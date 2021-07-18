#include <iostream>
#include <SFML/Graphics.hpp>
#include "types.hpp"

class Sorter
{
public:
    // ============ Constructors ============
    Sorter() {}

    // ============ Member Functions ============
    std::vector<std::vector<Bar>> bubbleSort(sf::RenderWindow &window, std::vector<Bar> bars)
    {

        std::vector<std::vector<Bar>> states;
        int iter = 1, upperLim = bars.size();

        for (auto i = 0; i < bars.size(); ++i)
        {
            // sort logic for this iteration
            bars[iter - 1].color = sf::Color::White;
            bars[iter].color = sf::Color::Red;
            if (bars[iter].height < bars[iter - 1].height)
            {
                auto temp = bars[iter].height;
                bars[iter].height = bars[iter - 1].height;
                bars[iter - 1].height = temp;
            }

            states.push_back(bars);

            ++iter;
            if (iter >= upperLim)
            {
                bars[iter].color = sf::Color::White;
                bars[upperLim].color = sf::Color::White;
                iter = 1;
                --upperLim;
            }
        }

        return states;
    }

    void mergeSort()
    {
    }

private:
};
