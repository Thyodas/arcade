/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** sfml.cpp
*/

#include "sfml.hpp"
#include <memory>

namespace display {

    void SFMLRenderer::init(Vector2i windowSize)
    {
        _window.create(sf::VideoMode(windowSize.x, windowSize.y), "Window SFML");

        _arial.loadFromFile("fonts/arial_narrow_7.ttf");

        _buttonsMap[LEFT] = sf::Keyboard::Q;
        _buttonsMap[UP] = sf::Keyboard::Z;
        _buttonsMap[RIGHT] = sf::Keyboard::D;
        _buttonsMap[DOWN] = sf::Keyboard::S;
        _buttonsMap[KEY_F] = sf::Keyboard::F;
        _buttonsMap[KEY_E] = sf::Keyboard::E;
        _buttonsMap[ESC] = sf::Keyboard::Escape;
        _buttonsMap[F1] = sf::Keyboard::F1;
        _buttonsMap[F2] = sf::Keyboard::F2;
        _buttonsMap[F3] = sf::Keyboard::F3;
        _buttonsMap[F4] = sf::Keyboard::F4;
        _buttonsMap[F5] = sf::Keyboard::F5;
        _buttonsMap[F6] = sf::Keyboard::F6;
        _buttonsMap[F7] = sf::Keyboard::F7;

        _colorsMap[BLACK] = sf::Color::Black;
        _colorsMap[RED] = sf::Color::Red;
        _colorsMap[GREEN] = sf::Color::Green;
        _colorsMap[YELLOW] = sf::Color::Yellow;
        _colorsMap[BLUE] = sf::Color::Blue;
        _colorsMap[MAGENTA] = sf::Color::Magenta;
        _colorsMap[CYAN] = sf::Color::Cyan;
        _colorsMap[WHITE] = sf::Color::White;

        _mapDecorator[object::RECTANGLE] = [this](std::shared_ptr<object::IObject> obj) { drawRect(obj); };
        _eventMode = BASIC;
    }

    bool SFMLRenderer::isButtonPressed(Button button)
    {
        auto it = std::find(_buttonsPressed.begin(), _buttonsPressed.end(), button);
        if (it != _buttonsPressed.end()) {
            _buttonsPressed.erase(it);
            return true;
        }
        return false;
    }

    sf::Vector2f SFMLRenderer::convertCellPosToPixelPos(Vector2i pixelPos) const
    {
        return {(float)(pixelPos.x * 12), (float)(pixelPos.y * 26)};
    }

    void SFMLRenderer::drawRect(std::shared_ptr<object::IObject> obj)
    {
        object::Rectangle *rect = static_cast<object::Rectangle *>(obj.get());
        sf::Vector2f pixelSize = convertCellPosToPixelPos(rect->getSize());
        pixelSize.x *= 2;
        sf::RectangleShape rectToDraw(pixelSize);
        sf::Vector2f pixelPos = convertCellPosToPixelPos(rect->getPos());
        rectToDraw.setPosition(pixelPos);
        rectToDraw.setFillColor(_colorsMap[rect->getColor()]);
        _window.draw(rectToDraw);
        if (rect->getText() != 0) {
            sf::Text text;
            std::string string;
            string.push_back(rect->getText());
            text.setFont(_arial);
            text.setString(string);
            text.setCharacterSize(pixelSize.x);
            text.setFillColor(_colorsMap[rect->getCharacterColor()]);
            text.setPosition(sf::Vector2f{pixelPos.x + pixelSize.x / 2, pixelPos.y});
            _window.draw(text);
        }
    }

    void SFMLRenderer::close()
    {
        _window.close();
        delete this;
    }

    void SFMLRenderer::clearWindow(Color color)
    {
        _window.clear(_colorsMap[color]);
    }

    void SFMLRenderer::handleEvents()
    {
        _buttonsPressed.clear();
        if (_eventMode == TXT) {
            return;
        }
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _buttonsPressed.push_back(Button::F7);
                continue;
            }
        }
        for (auto it = _buttonsMap.begin(); it != _buttonsMap.end(); ++it) {
            if (sf::Keyboard::isKeyPressed((*it).second))
                _buttonsPressed.push_back((*it).first);
        }
    }

    void SFMLRenderer::startTextInput()
    {
        _eventMode = TXT;
    }

    std::string SFMLRenderer::getTextInput()
    {
        static std::string userName;
        while (_window.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed) {
                _buttonsPressed.push_back(Button::F7);
                continue;
            }
            if (_event.type == sf::Event::KeyPressed) {
                if (_event.key.code == 58) {
                    endTextInput();
                    return "\n";
                }
                if (_event.key.code == 59)
                    userName.pop_back();
                if (userName.size() == 11)
                    break;
                if (_event.key.code == 57)
                    userName += '_';
                if (_event.key.code >= 0 && _event.key.code <= 25)
                    userName += _event.key.code + 97;
                if (_event.key.code >= 75 && _event.key.code <= 84)
                    userName += _event.key.code - 27;
            }
        }
        return userName;
    }

    void SFMLRenderer::endTextInput()
    {
        _eventMode = BASIC;
    }




    void SFMLRenderer::drawObj(std::shared_ptr<object::IObject> obj)
    {
        auto ptr = _mapDecorator[obj->getType()];
        ptr(obj);
    }

    void SFMLRenderer::render()
    {
        _window.display();
    }

}


extern "C"
{
    display::IDisplayModule *entryPointDisplay()
    {
        return new display::SFMLRenderer;
    }
}