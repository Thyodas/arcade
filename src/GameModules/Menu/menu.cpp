/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.cpp
*/

#include "menu.hpp"
#include <vector>

Menu::Menu() {}

Menu::~Menu() {}

void Menu::stop()
{
    delete this;
}

void Menu::init()
{
    rect = std::make_shared<Rectangle>();
    rect->setPos(IDisplayModule::Vector2i{400, 300});
    rect->setSize(IDisplayModule::Vector2i{100, 100});
    rect->setColor(IDisplayModule::YELLOW);
    rect->setCharacter('v');
    rect->setCharacterColor(IDisplayModule::BLACK);
}

void Menu::update(IDisplayModule *display)
{
    if (display->isButtonPressed(IDisplayModule::UP)) {
        rect->setPos(IDisplayModule::Vector2i{rect->getPos().x, rect->getPos().y - 10});
        rect->setCharacter('^');
    }
    if (display->isButtonPressed(IDisplayModule::RIGHT)) {
        rect->setPos(IDisplayModule::Vector2i{rect->getPos().x + 10, rect->getPos().y});
        rect->setCharacter('>');
    }
    if (display->isButtonPressed(IDisplayModule::LEFT)) {
        rect->setPos(IDisplayModule::Vector2i{rect->getPos().x - 10, rect->getPos().y});
        rect->setCharacter('<');
    }
    if (display->isButtonPressed(IDisplayModule::DOWN)) {
        rect->setPos(IDisplayModule::Vector2i{rect->getPos().x, rect->getPos().y + 10});
        rect->setCharacter('v');
    }
    display->drawObj(rect);
}

extern "C"
{
    IGameModule *entryPoint()
    {
        return new Menu;
    }
}