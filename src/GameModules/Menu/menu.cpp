/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.cpp
*/

#include "menu.hpp"
#include <vector>

namespace game {

    void Menu::stop()
    {
        delete this;
    }

    void Menu::init()
    {
        rect = std::make_shared<object::Rectangle>();
        rect->setPos(display::Vector2i{400, 300});
        rect->setSize(display::Vector2i{100, 100});
        rect->setColor(display::YELLOW);
        rect->setCharacter('v');
        rect->setCharacterColor(display::BLACK);
    }

    void Menu::update(display::IDisplayModule *display)
    {
        if (display->isButtonPressed(display::UP)) {
            rect->setPos(display::Vector2i{rect->getPos().x, rect->getPos().y - 10});
            rect->setCharacter('^');
        }
        if (display->isButtonPressed(display::RIGHT)) {
            rect->setPos(display::Vector2i{rect->getPos().x + 10, rect->getPos().y});
            rect->setCharacter('>');
        }
        if (display->isButtonPressed(display::LEFT)) {
            rect->setPos(display::Vector2i{rect->getPos().x - 10, rect->getPos().y});
            rect->setCharacter('<');
        }
        if (display->isButtonPressed(display::DOWN)) {
            rect->setPos(display::Vector2i{rect->getPos().x, rect->getPos().y + 10});
            rect->setCharacter('v');
        }
        display->drawObj(rect);
    }

}


extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Menu;
    }
}