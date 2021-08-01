#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "./constants.hpp"
class Button
{
public:
    Button();

    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColour, sf::Font &font)
    {
        _text.setString(t);
        _text.setFillColor(textColour);
        _text.setCharacterSize(charSize);
        _text.setFont(font);
        _button.setFillColor(bgColor);
        _button.setSize(size);
    }

    // =========== Getters ===========

    bool isDisabled() const
    {
        return _isDisabled;
    }

    // =========== Setters ===========

    void setFont(sf::Font &font)
    {
        _text.setFont(font);
    }

    void setBackgroundColour(sf::Color bgColor)
    {
        _button.setFillColor(bgColor);
    }

    void setTextColour(sf::Color textColor)
    {
        _text.setFillColor(textColor);
    }

    void setPosition(sf::Vector2f pos)
    {
        _button.setPosition(pos);

        auto xPos = (_button.getPosition().x) + (_button.getGlobalBounds().width / 2) - (_text.getGlobalBounds().width / 2);
        auto yPos = (_button.getPosition().y) + (_button.getGlobalBounds().height / 2) - (_text.getGlobalBounds().height / 2);

        _text.setPosition({xPos, yPos});
    }

    // =========== Member Functions ===========

    void drawTo(sf::RenderWindow &window)
    {
        window.draw(_button);
        window.draw(_text);
    }

    bool isMouseHovering(sf::RenderWindow &window) const
    {
        auto mouseX = sf::Mouse::getPosition(window).x;
        auto mouseY = sf::Mouse::getPosition(window).y;

        if (mouseX < _button.getPosition().x || mouseX > _button.getGlobalBounds().width + _button.getPosition().x)
        {
            return false;
        }

        if (mouseY < _button.getPosition().y || mouseY > _button.getGlobalBounds().height + _button.getPosition().y)
        {
            return false;
        }

        return true;
    }

    void mouseMoved(sf::RenderWindow &window)
    {
        if (!_isSel)
        {
            if (this->isMouseHovering(window))
            {
                _button.setFillColor(BTN_COLOUR_HOVER);
            }
            else
            {
                _button.setFillColor(BTN_COLOUR_DEFAULT);
            }
        }
    }

    void updateActiveState(bool isActive)
    {
        if (isActive)
        {
            _button.setFillColor(BTN_COLOUR_ACTIVE);
            _isSel = true;
        }
        else
        {
            _button.setFillColor(BTN_COLOUR_DEFAULT);
            _isSel = false;
        }
    }

    void disable(bool isDisabled)
    {
        if (isDisabled)
        {
            _button.setFillColor(BTN_COLOUR_FADED);
            _text.setFillColor(TEXT_COLOUR_FADED);
            _isDisabled = true;
        }
        else
        {
            _button.setFillColor(BTN_COLOUR_DEFAULT);
            _text.setFillColor(TEXT_COLOUR_DEFAULT);
            _isDisabled = false;
        }
    }

private:
    sf::RectangleShape _button;
    sf::Text _text;
    bool _isSel = false;
    bool _isDisabled = false;
};
