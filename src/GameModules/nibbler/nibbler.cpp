/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Nibbler.cpp
*/

#include <vector>
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include "nibbler.hpp"
#define SIZE 1
#define WALL '#'
#define FOOD 'o'
#define EMPTY ' '

namespace game {

    void Nibbler::stop(__attribute__((unused))arcade::ICore *core)
    {
        std::ofstream scoreFile;
        scoreFile.open("score.arcade", std::fstream::app);
        scoreFile << "nibbler " << core->getPlayerName() << " " << std::to_string(lvl) << std::endl;
        scoreFile.close();
        delete this;
    }

    std::shared_ptr<object::Rectangle> isWall(display::Vector2i pos, display::Color color)
    {
        std::shared_ptr<object::Rectangle> wall = std::make_shared<object::Rectangle>();
        wall->setPos(pos);
        wall->setSize(display::Vector2i{SIZE, SIZE});
        wall->setColor(color);
        wall->setCharacter(WALL);
        wall->setCharacterColor(color);
        return wall;
    }

    std::shared_ptr<object::Rectangle> isFood(display::Vector2i pos)
    {
        std::shared_ptr<object::Rectangle> food = std::make_shared<object::Rectangle>();
        food->setPos(pos);
        food->setSize(display::Vector2i{2, SIZE});
        food->setColor(display::BLACK);
        food->setCharacter(FOOD);
        food->setText(FOOD);
        food->setCharacterColor(display::YELLOW);
        return food;
    }

    std::shared_ptr<object::Rectangle> isEmpty(display::Vector2i pos)
    {
        std::shared_ptr<object::Rectangle> empty = std::make_shared<object::Rectangle>();
        empty->setPos(pos);
        empty->setSize(display::Vector2i{2, SIZE});
        empty->setColor(display::BLACK);
        empty->setCharacter(' ');
        empty->setText(' ');
        empty->setCharacterColor(display::BLACK);
        return empty;
    }

    void Nibbler::createMap(void)
    {
        std::string path = "src/GameModules/nibbler/lvl/" + std::to_string(lvl) + ".lvl";
        std::string line;
        std::ifstream myfile(path, std::ios::in);
        int i = 0, j = 0;

        if (!myfile.is_open())
            throw std::runtime_error("Nibbler: Cannot open file (.lvl file)");

        std::getline(myfile, line);
        int color = stoi(line);

        while (std::getline(myfile, line)) {
            for (auto character : line) {
                if (character == WALL)
                    map[i][j++] = isWall(display::Vector2i{(j * 2)+15, i+8}, (display::Color)color);
                else if (character == FOOD) {
                    map[i][j++] = isFood(display::Vector2i{(j * 2)+15, i+8});
                    nbFood++;
                } else
                    map[i][j++] = isEmpty(display::Vector2i{(j * 2)+15, i+8});
            }
            i++;
            j = 0;
        }
    }

    std::deque<std::shared_ptr<object::Rectangle>> Nibbler::initString(std::string str, display::Vector2i pos, display::Color color)
    {
        std::string test;
        std::string tmp;
        for (int i = 0; str[i]; ++i) {
            tmp = str[i];
            test += tmp;
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
            elem->setCharacterColor(color);
            string.push_back(elem);
        }
        return string;
    }


    void Nibbler::init()
    {
        index.y = 17-6;
        index.x = 11+6;
        createHead();
        createMap();
        _title = initString("Nibbler", display::Vector2i{27, 2}, display::WHITE);
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    void Nibbler::createHead(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setPos(display::Vector2i{37, 25});
        elem->setSize(display::Vector2i{SIZE, SIZE});
        elem->setColor(display::WHITE);
        elem->setCharacter('<');
        elem->setCharacterColor(display::BLACK);
        nibbler.push_back(elem);
    }

    void Nibbler::addElem(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setSize(display::Vector2i{SIZE, SIZE});
        if (direction == game::DIRECTION::UP)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y -
                        nibbler.at(nibbler.size() - 1)->getSize().y});
        if (direction == game::DIRECTION::RIGHT)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x -
                        nibbler.at(nibbler.size() - 1)->getSize().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y});
        if (direction == game::DIRECTION::DOWN)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y +
                        nibbler.at(nibbler.size() - 1)->getSize().y});
        if (direction == game::DIRECTION::LEFT)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x +
                        nibbler.at(nibbler.size() - 1)->getSize().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y});
        elem->setColor(display::RED);
        elem->setCharacter('*');
        elem->setCharacterColor(display::RED);
        nibbler.push_back(elem);
    }

    void Nibbler::checkWall(void)
    {
    };

    void Nibbler::checkFood(display::Vector2i pos)
    {
        if (map[index.x][index.y]->getCharacter() == FOOD) {
            addElem();
            score++;
            map[index.x][index.y] = isEmpty(display::Vector2i{pos.x, pos.y});
            nbFood--;
        }
    };

    void Nibbler::checkBody(void)
    {
        for (long unsigned int i = 1; i < nibbler.size(); ++i) {
            if (nibbler.at(0)->getPos().x == nibbler.at(i)->getPos().x &&
            nibbler.at(0)->getPos().y == nibbler.at(i)->getPos().y) {
                resetGame();
            }
        }
    };

    void Nibbler::resetGame(void)
    {
        while (!nibbler.empty()) {
            nibbler.at(nibbler.size() - 1).reset();
            nibbler.pop_back();
        }
        direction = game::DIRECTION::RIGHT;
        createHead();
        score = 0;
        index.y = 17-6;
        index.x = 11+6;
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    game::DIRECTION inverse(game::DIRECTION dir)
    {
        if (dir == game::DIRECTION::UP)
            return game::DIRECTION::DOWN;
        if (dir == game::DIRECTION::RIGHT)
            return game::DIRECTION::LEFT;
        if (dir == game::DIRECTION::LEFT)
            return game::DIRECTION::RIGHT;
        if (dir == game::DIRECTION::DOWN)
            return game::DIRECTION::UP;
        return dir;
    }

    game::DIRECTION randomPos(game::DIRECTION direction, std::array<int, 4> possibleWay)
    {
        srand(time(NULL));
        int random = rand() % 4;
        bool exists = std::find(std::begin(possibleWay), std::end(possibleWay), 1) != std::end(possibleWay);

        if (!exists)
            return direction;
        if (possibleWay[0]+possibleWay[1]+possibleWay[2]+possibleWay[3] == 1) {
            while (possibleWay[random] != 1)
                random = rand() % 4;
            return (game::DIRECTION)random;
        }
        return direction;
    }

    game::DIRECTION Nibbler::choseWay(void)
    {
        std::array<int, 4> possibleWay = {1, 1, 1, 1}; // [UP, RIGHT, DOWN, LEFT] -> 1 = possible / 0 = impossible
        possibleWay[inverse(direction)] = 0;

        if (map[index.x-SIZE][index.y]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::UP] = 0;
        if (map[index.x][index.y+SIZE]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::RIGHT] = 0;
        if (map[index.x+SIZE][index.y]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::DOWN] = 0;
        if (map[index.x][index.y-SIZE]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::LEFT] = 0;

        game::DIRECTION way = randomPos(direction, possibleWay);
        if (way == direction)
            return direction;
        return way;
    }

    void Nibbler::moveHead(game::DIRECTION way)
    {
        display::Vector2i pos = nibbler.at(0)->getPos();
        for (long unsigned int i = nibbler.size()-1; i > 0; --i)
            nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                nibbler.at(i-1)->getPos().y});
        if (way == game::DIRECTION::UP) {
            index.x -= SIZE;
            nibbler.at(0)->setPos(display::Vector2i{pos.x, pos.y-SIZE});
            direction = game::DIRECTION::UP;
            nibbler.at(0)->setCharacter('v');
        }
        if (way == game::DIRECTION::RIGHT) {
            index.y += SIZE;
            nibbler.at(0)->setPos(display::Vector2i{pos.x+2, pos.y});
            direction = game::DIRECTION::RIGHT;
            nibbler.at(0)->setCharacter('<');
        }
        if (way == game::DIRECTION::DOWN) {
            index.x += SIZE;
            nibbler.at(0)->setPos(display::Vector2i{pos.x, pos.y+SIZE});
            direction = game::DIRECTION::DOWN;
            nibbler.at(0)->setCharacter('^');
        }
        if (way == game::DIRECTION::LEFT) {
            index.y -= SIZE;
            nibbler.at(0)->setPos(display::Vector2i{pos.x-2, pos.y});
            direction = game::DIRECTION::LEFT;
            nibbler.at(0)->setCharacter('>');
        }
    }

    void Nibbler::checkEvent(display::IDisplayModule *display)
    {
        if (display->isButtonPressed(display::F5))
            return resetGame();
        if (display->isButtonPressed(display::UP) && direction != game::DIRECTION::DOWN) {
            if (map[index.x-SIZE][index.y]->getCharacter() != WALL) {
                direction = game::DIRECTION::UP;
                nibbler.at(0)->setCharacter('v');
            }
        } else if (display->isButtonPressed(display::RIGHT) && direction != game::DIRECTION::LEFT) {
            if (map[index.x][index.y+SIZE]->getCharacter() != WALL) {
                direction = game::DIRECTION::RIGHT;
                nibbler.at(0)->setCharacter('<');
            }
        } else if (display->isButtonPressed(display::LEFT) && direction != game::DIRECTION::RIGHT) {
            if (map[index.x][index.y-SIZE]->getCharacter() != WALL) {
                direction = game::DIRECTION::LEFT;
                nibbler.at(0)->setCharacter('>');
            }
        } else if (display->isButtonPressed(display::DOWN) && direction != game::DIRECTION::UP) {
            if (map[index.x+SIZE][index.y]->getCharacter() != WALL) {
                direction = game::DIRECTION::DOWN;
                nibbler.at(0)->setCharacter('^');
            }
        }
    }

    void Nibbler::move()
    {
        display::Vector2i pos = nibbler.at(0)->getPos();
        if (direction == game::DIRECTION::UP) {
            if (map[index.x-SIZE][index.y]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.y -= SIZE;
                index.x -= SIZE;
                nibbler.at(0)->setPos(pos);
            } else {
                game::DIRECTION way = choseWay();
                if (way != direction)
                    moveHead(way);
            }
        } else if (direction == game::DIRECTION::RIGHT) {
            if (map[index.x][index.y+SIZE]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.x += 2;
                index.y += SIZE;
                nibbler.at(0)->setPos(pos);
            } else {
                game::DIRECTION way = choseWay();
                if (way != direction)
                    moveHead(way);
            }
        } else if (direction == game::DIRECTION::LEFT) {
            if (map[index.x][index.y-SIZE]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.x -= 2;
                index.y -= SIZE;
                nibbler.at(0)->setPos(pos);
            } else {
                game::DIRECTION way = choseWay();
                if (way != direction)
                    moveHead(way);
            }
        } else if (direction == game::DIRECTION::DOWN) {
            if (map[index.x+SIZE][index.y]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.y += SIZE;
                index.x += SIZE;
                nibbler.at(0)->setPos(pos);
            } else {
                game::DIRECTION way = choseWay();
                if (way != direction)
                    moveHead(way);
            }
        }
    }


    void Nibbler::update(display::IDisplayModule *display)
    {
        checkEvent(display);
        move();
        checkBody();
        checkFood(nibbler.at(0)->getPos());
        std::string lvlInStr = std::to_string(lvl);
        std::deque<std::shared_ptr<object::Rectangle>> displayLvl = initString("Lvl : " + lvlInStr, display::Vector2i{18, 4}, display::WHITE);
        std::string scoreInStr = std::to_string(score * 100);
        std::deque<std::shared_ptr<object::Rectangle>> displayScore = initString("Score : " + scoreInStr, display::Vector2i{34, 4}, display::WHITE);

        for (int i = 0; i < 19; ++i)
            for (int j = 0; j < 19; ++j)
                display->drawObj(map[i][j]);
        for (long unsigned int i = 0; i < nibbler.size(); ++i)
            display->drawObj(nibbler.at(i));
        for (auto character: _title)
            display->drawObj(character);
        for (auto elem : displayScore)
            display->drawObj(elem);
        for (auto elem : displayLvl)
            display->drawObj(elem);

        if (nbFood == 0) {
            lvl++;
            if (lvl > 32)
                lvl = 1;
            resetGame();
            createMap();
        }
    }
}


extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Nibbler;
    }
}
