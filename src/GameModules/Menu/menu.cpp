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
#define FIRST_LINE 12

namespace game {

    void Menu::stop(__attribute__((unused))arcade::ICore *core)
    {
        delete this;
    }


    std::deque<std::shared_ptr<object::Rectangle>> Menu::initString(std::string str, display::Vector2i pos)
    {
        std::string test;
        std::string tmp;
        for (int i = 0; str[i]; ++i) {
            tmp = str[i];
            test += tmp + " ";
        }
        test += " ";
        std::deque<std::shared_ptr<object::Rectangle>> string = std::deque<std::shared_ptr<object::Rectangle>>();
        for (int i = 0; test[i]; ++i) {
            std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
            elem->setPos(display::Vector2i{pos.x+((SIZE)*i), pos.y});
            elem->setSize(display::Vector2i{SIZE, SIZE});
            elem->setColor(display::BLACK);
            elem->setCharacter(test[i]);
            elem->setText(test[i]);
            elem->setCharacterColor(display::WHITE);
            string.push_back(elem);
        }
        return string;
    }

    void Menu::createCursor()
    {
        cursor = std::make_shared<object::Rectangle>();
        cursor->setPos(display::Vector2i{8, FIRST_LINE});
        cursor->setSize(display::Vector2i{SIZE, SIZE});
        cursor->setColor(display::WHITE);
        cursor->setCharacter(' ');
        cursor->setCharacterColor(display::WHITE);
    }

    std::shared_ptr<object::Rectangle> createElemBackground(display::Vector2i pos, display::Color color)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setPos(pos);
        elem->setSize(display::Vector2i{SIZE, SIZE});
        elem->setColor(color);
        elem->setCharacter(' ');
        elem->setText(' ');
        elem->setCharacterColor(color);
        return elem;
    }

    void Menu::createBackground(void)
    {
        for (int i = 4; i <= 32; ++i) {
            for (int j = FIRST_LINE-2; j < 30; ++j)
                if (i == 4 || j == FIRST_LINE-2 || i == 32 || j == 29)
                    background.push_back(createElemBackground(display::Vector2i{i, j}, display::WHITE));
        }
        for (int i = 33; i < 62; ++i) {
            for (int j = FIRST_LINE-2; j < 30; ++j)
                if (i == 33 || j == FIRST_LINE-2 || i == 61 || j == 29)
                    background.push_back(createElemBackground(display::Vector2i{i, j}, display::WHITE));
        }
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
        static display::Vector2i gamePos = {11, FIRST_LINE};
        static display::Vector2i graphicPos = {38, FIRST_LINE};
        game::IGameModule *testGame = nullptr;
        display::IDisplayModule *testDisplay = nullptr;
        void *handle = loader.loadLib(pathToLib);
        if (pathToLib.find("menu") != std::string::npos)
            return;
        if (!handle)
            return;
        if ((testGame = loader.getEntryPoint<game::IGameModule *>(handle, "entryPointGame")) != nullptr) {
            delete testGame;
            std::string path = pathToLib.substr(pathToLib.find("_")+1);
            gameLibs.push_back(initString(path.substr(0, path.size() - 3), gamePos));
            gamePos.y += 2;
            dlclose(handle);
            return;
        }
        if ((testDisplay = loader.getEntryPoint<display::IDisplayModule *>(handle, "entryPointDisplay")) != nullptr) {
            delete testDisplay;
            std::string path = pathToLib.substr(pathToLib.find("_")+1);
            graphicLibs.push_back(initString(path.substr(0, path.size() - 3), graphicPos));
            graphicPos.y += 2;
            dlclose(handle);
            return;
        }
    }

    void Menu::init()
    {
        createBackground();
        createCursor();
        setListLibs();
    }

    void displayElem(display::IDisplayModule *display,
        std::deque<std::shared_ptr<object::Rectangle>> elements)
    {
        for (auto elem : elements)
            display->drawObj(elem);
    }

    void Menu::update(display::IDisplayModule *display)
    {
        static long unsigned int cursorPos = 0;
        for (long unsigned int j = 0; j < gameLibs.size(); ++j) {
            if (j != cursorPos)
                for (long unsigned int i = 0; i < gameLibs.at(j).size(); ++i)
                    gameLibs.at(j).at(i)->setCharacterColor(display::WHITE);
        }
        if (display->isButtonPressed(display::UP)) {
            cursorPos -= cursorPos > 0 ? 1 : 0;
            cursor->setPos(display::Vector2i{cursor->getPos().x, gameLibs.at(cursorPos).at(0)->getPos().y});
        }
        if (display->isButtonPressed(display::DOWN)) {
            cursorPos += cursorPos < gameLibs.size()-1 ? 1 : 0;
            cursor->setPos(display::Vector2i{cursor->getPos().x, gameLibs.at(cursorPos).at(0)->getPos().y});
        }
        for (long unsigned int i = 0; i < gameLibs.at(cursorPos).size(); ++i)
            gameLibs.at(cursorPos).at(i)->setCharacterColor(display::CYAN);
        for (auto game : gameLibs)
            displayElem(display, game);
        for (auto graphic : graphicLibs)
            displayElem(display, graphic);
        displayElem(display, background);
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
