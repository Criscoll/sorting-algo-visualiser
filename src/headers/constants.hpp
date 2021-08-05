#pragma once

#define BTN_COLOUR_DEFAULT sf::Color(82, 82, 82)
#define BTN_COLOUR_ACTIVE sf::Color(86, 173, 85)
#define BTN_COLOUR_HOVER sf::Color(207, 70, 70)
#define BTN_COLOUR_FADED sf::Color(41, 37, 37)

#define TEXT_COLOUR_DEFAULT sf::Color(214, 214, 214)
#define TEXT_COLOUR_FADED sf::Color(158, 158, 158)

#define BORDER_COLOUR_DEFAULT sf::Color(82, 82, 82)

#define BAR_COLOUR_DEFAULT sf::Color::White
#define BAR_COLOUR_SELECTED sf::Color::Red

enum Algorithm
{
    BubbleSort,
    MergeSort,
    QuickSort,
    InsertionSort,
    RadixSort,
};