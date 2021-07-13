#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
public:
    Button()
    {
    }

    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color textColour)
    {
        _text.setString(t);
        _text.setFillColor(textColour);
        _text.setCharacterSize(charSize);
        _button.setFillColor(bgColor);
        _button.setSize(size);
    }

    // =========== Getters ===========

    bool isSelected()
    {
        return _isSel;
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

    bool isMouseHovering(sf::RenderWindow &window)
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
                _button.setFillColor(sf::Color::Red);
            }
            else
            {
                _button.setFillColor(sf::Color(89, 89, 89));
            }
        }
    }

    void mouseClicked(sf::RenderWindow &window)
    {
        if (this->isMouseHovering(window))
        {
            if (_isSel)
            {
                _button.setFillColor(sf::Color::Red);
            }
            else
            {
                _button.setFillColor(sf::Color::Green);
            }
        }
        _isSel = !_isSel;
    }

private:
    sf::RectangleShape _button;
    sf::Text _text;
    bool _isSel = false;
};