/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** sfml.cpp
*/

#include "sfml.hpp"
#include <memory>

SFMLRenderer::SFMLRenderer() : _window(sf::VideoMode(1920, 1080), "Window tg")
{
    _buttonsMap[LEFT] = sf::Keyboard::Q;
    _buttonsMap[UP] = sf::Keyboard::Z;
    _buttonsMap[RIGHT] = sf::Keyboard::D;
    _buttonsMap[DOWN] = sf::Keyboard::S;
    _buttonsMap[KEY_Q] = sf::Keyboard::F;
    _buttonsMap[KEY_E] = sf::Keyboard::E;
    _buttonsMap[ESC] = sf::Keyboard::Escape;
    _buttonsMap[F1] = sf::Keyboard::F1;
    _buttonsMap[F2] = sf::Keyboard::F2;
    _buttonsMap[F3] = sf::Keyboard::F3;
    _buttonsMap[F4] = sf::Keyboard::F4;
    _buttonsMap[F5] = sf::Keyboard::F5;
    _buttonsMap[F6] = sf::Keyboard::F6;
    _buttonsMap[F7] = sf::Keyboard::F7;

    _mouseMap[sf::Event::MouseButtonPressed][sf::Mouse::Left] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::PRESSED,
                                MouseButtonEvent::MouseButton::LEFT,
                                Vector2i{x, y}};
    };
    _mouseMap[sf::Event::MouseButtonPressed][sf::Mouse::Right] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::PRESSED,
                                MouseButtonEvent::MouseButton::RIGHT,
                                Vector2i{x, y}};
    };
    _mouseMap[sf::Event::MouseButtonReleased][sf::Mouse::Left] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::RELEASED,
                                MouseButtonEvent::MouseButton::LEFT,
                                Vector2i{x, y}};
    };
    _mouseMap[sf::Event::MouseButtonReleased][sf::Mouse::Left] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::RELEASED,
                                MouseButtonEvent::MouseButton::LEFT,
                                Vector2i{x, y}};
    };

    _mapDecorator[RECTANGLE] = [this](IObject *obj) { drawRect(obj); };
}

SFMLRenderer::~SFMLRenderer()
{

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

IDisplayModule::Vector2i SFMLRenderer::getMousePos() const
{
    sf::Vector2i pos = sf::Mouse::getPosition(_window);
    return Vector2i{pos.x, pos.y};
}

IDisplayModule::MouseButtonEvent SFMLRenderer::getMouseButtonEvent()
{
    if (_mouseEvents.empty())
        return MouseButtonEvent{MouseButtonEvent{MouseButtonEvent::MouseEventType::NONE,
                                MouseButtonEvent::MouseButton::NONE,
                                Vector2i{0, 0}}};
    return _mouseEvents.front();
}

void SFMLRenderer::drawRect(IObject *obj)
{
    Rectangle *rect = static_cast<Rectangle *>(obj);
    sf::RectangleShape rectToDraw(sf::Vector2f(rect->getSize().x, rect->getSize().y));
    rectToDraw.setPosition(sf::Vector2f(rect->getPos().x, rect->getPos().y));
    rectToDraw.setFillColor(sf::Color::Red);
    _window.draw(rectToDraw);
}

void SFMLRenderer::close()
{
    _window.close();
}

void SFMLRenderer::clearWindow(Color color)
{
    _window.clear(sf::Color::Black);
}

void SFMLRenderer::handleEvents()
{
    _buttonsPressed.clear();
    _mouseEvents.clear();
    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::KeyPressed) {
            for (auto it = _buttonsMap.begin(); it != _buttonsMap.end(); ++it) {
                if ((*it).second == _event.key.code) {
                    _buttonsPressed.push_back((*it).first);
                    break;
                }
            }
        }
        if (_mouseMap.find(_event.type) != _mouseMap.end())
            if (_mouseMap[_event.type].find(_event.mouseButton.button) != _mouseMap[_event.type].end())
                _mouseEvents.push_back(_mouseMap[_event.type][_event.mouseButton.button](_event.mouseButton.x, _event.mouseButton.y));
    }
}

void SFMLRenderer::drawObj(IObject *obj)
{
    auto ptr = _mapDecorator[obj->getType()];
    ptr(obj);
}

void SFMLRenderer::render()
{
    _window.display();
}

extern "C"
{
    std::unique_ptr<IDisplayModule> entryPointDisplay()
    {
        return std::make_unique<SFMLRenderer>();
    }
}