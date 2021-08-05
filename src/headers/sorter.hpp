#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "types.hpp"
#include "constants.hpp"

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
        return states;
    }

    std::queue<std::vector<Bar>> mergeSort(std::vector<Bar> bars)
    {
        std::queue<std::vector<Bar>> states;
        states.push(bars);
        mergeSorter(bars, states, 0, bars.size() - 1);
        return states;
    }

    void mergeSorter(std::vector<Bar> &bars, std::queue<std::vector<Bar>> &states, int l, int r)
    {
        if (l < r)
        {
            int m = l + (r - l) / 2;
            mergeSorter(bars, states, l, m);
            mergeSorter(bars, states, m + 1, r);
            merge(bars, states, l, m, r);
        }
    }

    void merge(std::vector<Bar> &bars, std::queue<std::vector<Bar>> &states, int l, int m, int r)
    {
        int i, j, k, nl, nr;

        //size of left and right sub-arrays
        nl = m - l + 1;
        nr = r - m;
        Bar larr[nl], rarr[nr];

        //fill left and right sub-arrays
        for (i = 0; i < nl; i++)
            larr[i] = bars[l + i];
        for (j = 0; j < nr; j++)
            rarr[j] = bars[m + 1 + j];
        i = 0;
        j = 0;
        k = l;

        // visualisation for comparing both sides of a merge (functionally does nothing)
        while (i < nl && j < nr)
        {
            bars[l + i].color = BAR_COLOUR_SELECTED;
            bars[m + 1 + j].color = BAR_COLOUR_SELECTED;
            states.push(bars);
            bars[l + i].color = BAR_COLOUR_DEFAULT;
            bars[m + 1 + j].color = BAR_COLOUR_DEFAULT;
            i++;
            j++;
        }

        i = 0;
        j = 0;

        //merge temp arrays to real array
        while (i < nl && j < nr)
        {
            if (larr[i].height <= rarr[j].height)
            {
                bars[k].height = larr[i].height;
                i++;
            }
            else
            {
                bars[k].height = rarr[j].height;
                j++;
            }

            if (k > l)
                bars[k - 1].color = BAR_COLOUR_DEFAULT;
            bars[k].color = BAR_COLOUR_SELECTED;
            k++;

            states.push(bars);
        }

        //extra element in left array
        while (i < nl)
        {
            bars[k].height = larr[i].height;
            bars[k - 1].color = BAR_COLOUR_DEFAULT;
            bars[k].color = BAR_COLOUR_SELECTED;
            i++;
            k++;
            states.push(bars);
        }

        //extra element in right array
        while (j < nr)
        {
            bars[k].height = rarr[j].height;
            bars[k - 1].color = BAR_COLOUR_DEFAULT;
            bars[k].color = BAR_COLOUR_SELECTED;
            j++;
            k++;
            states.push(bars);
        }

        // change the last bar selected to the default colour
        bars[k - 1].color = BAR_COLOUR_DEFAULT;
        states.push(bars);
    }

private:
};
