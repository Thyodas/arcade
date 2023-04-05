/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.cpp
*/

#include <vector>
#include <list>
#include <filesystem>
#include <vector>
#include "menu.hpp"
#define SIZE 1

namespace game {

    void Menu::stop()
    {
        delete this;
    }


    std::deque<std::shared_ptr<object::Rectangle>> Menu::initString(std::string str)
    {
        static display::Vector2i pos = {10, 5};

        str += " ";
        std::cout << ">" << str << "<" << std::endl;
        std::deque<std::shared_ptr<object::Rectangle>> string = std::deque<std::shared_ptr<object::Rectangle>>();
        for (int i = 0; str[i]; ++i) {
            std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
            elem->setPos(display::Vector2i{pos.x+((SIZE*2)*i), pos.y});
            elem->setSize(display::Vector2i{SIZE, SIZE});
            elem->setColor(display::BLACK);
            elem->setCharacter(str[i]);
            elem->setText(str[i]);
            elem->setCharacterColor(display::WHITE);
            string.push_back(elem);
        }
        pos.y += 2;
        return string;
    }

    void Menu::createCursor()
    {
        cursor = std::make_shared<object::Rectangle>();
        cursor->setPos(display::Vector2i{10, 10});
        cursor->setSize(display::Vector2i{SIZE, SIZE});
        cursor->setColor(display::WHITE);
        cursor->setCharacter(' ');
        cursor->setCharacterColor(display::WHITE);
    }

    void Menu::setListLibs()
    {
        for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
            std::string path_str = std::string(entry.path().c_str());
            if (path_str.compare(0, 7, "arcade_"))
                testLib(path_str);
        }
    }

    void Menu::testLib(const std::string pathToLib)
    {
        game::IGameModule *testGame = nullptr;
        display::IDisplayModule *testDisplay = nullptr;
        void *handle = loader.loadLib(pathToLib);
        if (!handle)
            return;
        if ((testGame = loader.getEntryPoint<game::IGameModule *>(handle, "entryPointGame")) != nullptr) {
            delete testGame;
            std::string path = pathToLib.substr(pathToLib.find("_")+1);
            gameLibs.push_back(initString(path.substr(0, path.size() - 3)));
            dlclose(handle);
            return;
        }
        if ((testDisplay = loader.getEntryPoint<display::IDisplayModule *>(handle, "entryPointDisplay")) != nullptr) {
            delete testDisplay;
            std::string path = pathToLib.substr(pathToLib.find("_")+1);
            graphicLibs.push_back(initString(path.substr(0, path.size() - 3)));
            dlclose(handle);
            return;
        }
    }

    void Menu::init()
    {
        createCursor();
        setListLibs();
    }

    void Menu::update(display::IDisplayModule *display)
    {
        if (display->isButtonPressed(display::UP))
            cursor->setPos(display::Vector2i{cursor->getPos().x, cursor->getPos().y - SIZE});
        if (display->isButtonPressed(display::DOWN))
            cursor->setPos(display::Vector2i{cursor->getPos().x, cursor->getPos().y + SIZE});
        for (auto games : gameLibs)
            for (int i = 0; i < games.size(); ++i)
                display->drawObj(games.at(i));
        for (auto graphics : graphicLibs)
            for (int i = 0; i < graphics.size(); ++i)
                display->drawObj(graphics.at(i));
        display->drawObj(cursor);
    }

}


extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Menu;
    }
}
