/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.cpp
*/

#include "menu.hpp"
#include <vector>
#define SIZE 1

namespace game {

    void Menu::stop()
    {
        delete this;
    }

    void Menu::initString(std::string str)
    {
        display::Vector2i pos = {10, 10};
        for (int i = 0; str[i]; i++) {
            std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
            elem->setPos(display::Vector2i{pos.x+((SIZE*2)*i), pos.y});
            elem->setSize(display::Vector2i{SIZE, SIZE});
            elem->setColor(display::BLACK);
            elem->setCharacter(str[i]);
            elem->setText(str[i]);
            elem->setCharacterColor(display::WHITE);
            menu.push_back(elem);
        }
    }

    void Menu::init()
    {
        cursor = std::make_shared<object::Rectangle>();
        cursor->setPos(display::Vector2i{10, 10});
        cursor->setSize(display::Vector2i{SIZE, SIZE});
        cursor->setColor(display::WHITE);
        cursor->setCharacter(' ');
        cursor->setCharacterColor(display::WHITE);
        initString("menu test ok oui non wouhou ");
    }

    void Menu::update(display::IDisplayModule *display)
    {
        if (display->isButtonPressed(display::UP))
            cursor->setPos(display::Vector2i{cursor->getPos().x, cursor->getPos().y - SIZE});
        if (display->isButtonPressed(display::DOWN))
            cursor->setPos(display::Vector2i{cursor->getPos().x, cursor->getPos().y + SIZE});
        display->drawObj(cursor);
        for (long unsigned int i = 0; i < menu.size(); ++i)
            display->drawObj(menu.at(i));
    }

}


extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Menu;
    }
}