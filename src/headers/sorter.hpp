#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "types.hpp"

// void *operator new(size_t size)
// {
//     std::cout << "Allocating memory of size " << size << " bytes\n";
//     return malloc(size);
// }

class Sorter
{
public:
    // ============ Constructors ============
    Sorter() {}

    // ============ Member Functions ============
    std::queue<std::vector<Bar>> bubbleSort(std::vector<Bar> bars)
    {
        std::queue<std::vector<Bar>> states;
        states.push(bars);

        int iter = 1, upperLim = bars.size() - 1;

        while (upperLim >= 1)
        {
            // std::cout << "upperLim - " << upperLim << " iter - " << iter << std::endl;
            // sort logic >  setting colours for current pair comparison
            bars[iter - 1].color = sf::Color::White;
            bars[iter].color = sf::Color::Red;

            // sort logic > comparing adjacent pair
            if (bars[iter].height < bars[iter - 1].height)
            {
                auto temp = bars[iter].height;
                bars[iter].height = bars[iter - 1].height;
                bars[iter - 1].height = temp;
            }

            states.push(bars);

            // sort logic > resetting sorting loop
            ++iter;
            if (iter >= upperLim)
            {
                bars[iter].color = sf::Color::White;
                bars[upperLim].color = sf::Color::White;
                iter = 1;
                --upperLim;
            }
        }
        std::cout << "just before returning the order" << std::endl;
        return states;
    }

    void mergeSort()
    {
    }

private:
};
