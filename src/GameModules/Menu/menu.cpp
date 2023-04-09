/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.cpp
*/

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <filesystem>
#include <vector>
#include <fstream>
#include "menu.hpp"
#define SIZE 1
#define FIRST_LINE 14

namespace game {

    void Menu::stop(__attribute__((unused))arcade::ICore *core)
    {
        core->setPlayerName(userNameStr);
        delete this;
    }

    void manageUserInput(display::IDisplayModule *display)
    {
        display->startTextInput();
    }

    std::deque<std::shared_ptr<object::Rectangle>> Menu::initString(std::string str, display::Vector2i pos, display::Color color)
    {
        std::string test;
        std::string tmp;
        test += " ";
        for (int i = 0; str[i]; ++i) {
            tmp = str[i];
            test += tmp;
        }
        std::deque<std::shared_ptr<object::Rectangle>> string = std::deque<std::shared_ptr<object::Rectangle>>();
        for (int i = test.length() - 1; i != -1; --i) {
            std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
            elem->setPos(display::Vector2i{pos.x+((SIZE)*i), pos.y});
            elem->setSize(display::Vector2i{SIZE, SIZE});
            elem->setColor(display::BLACK);
            elem->setCharacter(test[i]);
            elem->setText(test[i]);
            elem->setCharacterColor(color);
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
        elem->setCharacterColor(color);
        return elem;
    }

    void Menu::createBackground(void)
    {
        titleUserName = initString("Pseudo: ", display::Vector2i{6, FIRST_LINE-6}, display::CYAN);
        for (int i = 4; i <= 32; ++i) {
            for (int j = FIRST_LINE-7; j < 30; ++j)
                if (i == 4 || j == FIRST_LINE-7 || i == 32 || j == 29)
                    background.push_back(createElemBackground(display::Vector2i{i, j}, display::CYAN));
        }
        titleScore = initString("Score: ", display::Vector2i{35, FIRST_LINE-6}, display::YELLOW);
        for (int i = 33; i <= 62; ++i) {
            for (int j = FIRST_LINE-7; j < 30; ++j)
                if (i == 33 || j == FIRST_LINE-7 || i == 62 || j == 29)
                    background.push_back(createElemBackground(display::Vector2i{i, j}, display::YELLOW));
        }
        for (int i = 4; i <= 32; ++i) {
            for (int j = FIRST_LINE-2; j < 30; ++j)
                if (i == 4 || j == FIRST_LINE-2 || i == 32 || j == 29)
                    background.push_back(createElemBackground(display::Vector2i{i, j}, display::WHITE));
        }
        for (int i = 33; i <= 62; ++i) {
            for (int j = FIRST_LINE-2; j < 30; ++j)
                if (i == 33 || j == FIRST_LINE-2 || i == 62 || j == 29)
                    background.push_back(createElemBackground(display::Vector2i{i, j}, display::WHITE));
        }
    }

    void Menu::initControl(bool show)
    {
        int y = 3;
        while (_control.size() > 0)
            _control.pop_back();
        if (!show) {
            _control = initString("To show controls press E", display::Vector2i{5, y+2}, display::WHITE);
            show = false;
            return;
        }
        for (int i = 0; i < 66; ++i)
            for (int j = 0; j < 66; ++j) {
                if ((i == 16 || j == 6 || i == 54 || j == 28) &&
                    (i >= 16 && j >= 6 && i <= 54 && j <= 28))
                    _control.push_back(createElemBackground(display::Vector2i{i,j}, display::CYAN));
                else
                    _control.push_back(createElemBackground(display::Vector2i{i,j}, display::BLACK));
            }
        std::deque<std::shared_ptr<object::Rectangle>> title = initString("Controls:", display::Vector2i{28, y}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> z = initString("Z       ->  up", display::Vector2i{20, (y+=5)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> q = initString("Q       ->  left", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> s = initString("S       ->  down", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> d = initString("D       ->  right", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> f1 = initString("f1      ->  prev graphic lib", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> f2 = initString("f2      ->  next graphic lib", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> f3 = initString("f3      ->  prev game", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> f4 = initString("f4      ->  next game", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> f5 = initString("f5      ->  restart game", display::Vector2i{20, (y+=2)}, display::WHITE);
        std::deque<std::shared_ptr<object::Rectangle>> f7 = initString("f7      ->  exit", display::Vector2i{20, (y+=2)}, display::WHITE);
        for (auto elem : title)
            _control.push_back(elem);
        for (auto elem : z)
            _control.push_back(elem);
        for (auto elem : q)
            _control.push_back(elem);
        for (auto elem : s)
            _control.push_back(elem);
        for (auto elem : d)
            _control.push_back(elem);
        for (auto elem : f1)
            _control.push_back(elem);
        for (auto elem : f2)
            _control.push_back(elem);
        for (auto elem : f3)
            _control.push_back(elem);
        for (auto elem : f4)
            _control.push_back(elem);
        for (auto elem : f5)
            _control.push_back(elem);
        for (auto elem : f7)
            _control.push_back(elem);
        show = true;
    }

    void Menu::setListLibs()
    {
        display::Vector2i gamePos = {11, FIRST_LINE};
        display::Vector2i graphicPos = {38, FIRST_LINE};
        for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
            std::string path_str = std::string(entry.path().c_str());
            if (path_str.compare(0, 7, "arcade_"))
                testLib(path_str, &gamePos, &graphicPos);
        }
    }

    void Menu::testLib(const std::string pathToLib, display::Vector2i *gamePos, display::Vector2i *graphicPos)
    {
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
            gameLibs.push_back(initString(path.substr(0, path.size() - 3), *gamePos, display::WHITE));
            gameLibsStr.push_back(path.substr(0, path.size() - 3));
            gamePos->y += 2;
            dlclose(handle);
            return;
        }
        if ((testDisplay = loader.getEntryPoint<display::IDisplayModule *>(handle, "entryPointDisplay")) != nullptr) {
            delete testDisplay;
            std::string path = pathToLib.substr(pathToLib.find("_")+1);
            graphicLibs.push_back(initString(path.substr(0, path.size() - 3), *graphicPos, display::WHITE));
            graphicLibsStr.push_back(path.substr(0, path.size() - 3));
            graphicPos->y += 2;
            dlclose(handle);
            return;
        }
    }

    void Menu::init()
    {
        createBackground();
        createCursor();
        setListLibs();
        initControl(false);
        _title = initString("M E N U", display::Vector2i{28, 2}, display::WHITE);
    }

    void displayElem(display::IDisplayModule *display,
        std::deque<std::shared_ptr<object::Rectangle>> elements)
    {
        for (auto elem : elements)
            display->drawObj(elem);
    }

    std::vector<std::string> splitScore(std::string line)
    {
        std::vector<std::string> array;
        size_t pos = line.find(' ');
        size_t initialPos = 0;

        while(pos != std::string::npos) {
            array.push_back(line.substr( initialPos, pos - initialPos));
            initialPos = pos + 1;
            pos = line.find(' ', initialPos);
        }
        array.push_back(line.substr(initialPos, std::min(pos, line.size()) - initialPos+1));
        return array;
    }


    std::string Menu::getPlayerScore(std::string game)
    {
        std::vector<int> allPlayerScores;
        std::ifstream scoreFile("score.arcade");
        std::string line;
        while (std::getline(scoreFile, line)) {
            std::vector<std::string> lineSplit = splitScore(line);
            if (game == lineSplit[0] && userNameStr == lineSplit[1])
                allPlayerScores.push_back(stoi(lineSplit[2]));
        }
        if (allPlayerScores.size() != 0) {
            auto max = std::max_element(allPlayerScores.begin(), allPlayerScores.end());
            return std::to_string(*max);
        }
        return game == "nibbler" ? ("?") : ("???");
    }

    void Menu::update(display::IDisplayModule *display)
    {
        static bool show = false;
        static std::string userNameTmp = "";
        static bool showCursor = false;
        static long unsigned int cursorPos = 0;
        showCursor = !showCursor;
        if (cursorPos == (long unsigned int)-1 && !show) {
            std::string tmp = display->getTextInput();
            if (tmp == "\n") {
                cursorPos = 0;
                cursor->setColor(display::WHITE);
                cursor->setPos(display::Vector2i{8, 14});
                _score = initString(getPlayerScore(gameLibsStr[cursorPos]), display::Vector2i{38, 10}, display::WHITE);
            } else {
                userNameTmp.clear();
                userNameTmp += tmp;
            }
        } else {
            for (long unsigned int j = 0; j < gameLibs.size(); ++j) {
                if (j != cursorPos)
                    for (long unsigned int i = 0; i < gameLibs.at(j).size(); ++i)
                        gameLibs.at(j).at(i)->setCharacterColor(display::WHITE);
            }
            if (display->isButtonPressed(display::KEY_E)) {
                show = !show;
                initControl(show);
            }
            if (display->isButtonPressed(display::UP) && !show) {
                if (cursorPos == 0) {
                    cursorPos = -1;
                    cursor->setPos(display::Vector2i{8, 10});
                    display->startTextInput();
                    return;
                }
                cursorPos -= cursorPos > 0 ? 1 : 0;
                cursor->setPos(display::Vector2i{cursor->getPos().x, gameLibs.at(cursorPos).at(0)->getPos().y});
                _score = initString(getPlayerScore(gameLibsStr[cursorPos]), display::Vector2i{38, 10}, display::WHITE);
            }
            if (display->isButtonPressed(display::DOWN) && !show) {
                cursorPos += cursorPos < gameLibs.size()-1 ? 1 : 0;
                cursor->setPos(display::Vector2i{cursor->getPos().x, gameLibs.at(cursorPos).at(0)->getPos().y});
                _score = initString(getPlayerScore(gameLibsStr[cursorPos]), display::Vector2i{38, 10}, display::WHITE);
            }
            for (long unsigned int i = 0; i < gameLibs.at(cursorPos).size(); ++i)
                gameLibs.at(cursorPos).at(i)->setCharacterColor(display::CYAN);
        }
        userNameStr = userNameTmp;
        _userName = initString(userNameTmp, display::Vector2i{9, FIRST_LINE-4}, display::CYAN);
        for (auto game : gameLibs)
            displayElem(display, game);
        for (auto graphic : graphicLibs)
            displayElem(display, graphic);
        displayElem(display, background);
        displayElem(display, titleUserName);
        displayElem(display, _userName);
        displayElem(display, titleScore);
        displayElem(display, _score);
        displayElem(display, _title);
        if (showCursor)
            display->drawObj(cursor);
        displayElem(display, _control);
    }

}

extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Menu;
    }
}
