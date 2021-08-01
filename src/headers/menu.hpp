#include <iostream>
#include <SFML/Graphics.hpp>
#include "button.hpp"

class Menu
{
public:
    // ============ Constructors ============

    Menu();
    Menu(sf::Vector2f position, int selectedIdx)
    {
        _position = position;
        _selectedIdx = selectedIdx;
    }

    // ============ Getters & Setters ============

    // ============ Member Functions ============
    void moveUp();
    void moveDown();

    void addButton(Button newBtn)
    {
        _buttons.push_back(newBtn);
        updateButtonStates();
    }

    void drawTo(sf::RenderWindow &window)
    {
        for (auto i = 0; i < _buttons.size(); ++i)
        {
            _buttons[i].setPosition({_position.x, _position.y + (i * 100)});
            _buttons[i].drawTo(window);
        }
    }

    void mouseMoved(sf::RenderWindow &window)
    {
        for (auto &btn : _buttons)
            btn.mouseMoved(window);
    }

    void mouseClicked(sf::RenderWindow &window)
    {
        for (auto i = 0; i < _buttons.size(); ++i)
        {
            if (_buttons[i].isMouseHovering(window))
            {
                _selectedIdx = i;
            }
        }

        updateButtonStates();
    }

    void updateButtonStates()
    {
        for (auto i = 0; i < _buttons.size(); ++i)
        {
            if (_selectedIdx == i)
                _buttons[i].updateActiveState(true);
            else
                _buttons[i].updateActiveState(false);
        }
    }

private:
    sf::Vector2f _position;
    std::vector<Button> _buttons;
    int _selectedIdx;
};