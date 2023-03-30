/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Nibbler.cpp
*/

#include "nibbler.hpp"
#include <vector>
#include <fstream>
#include <time.h>
#define SIZE 1
#define WALL '#'
#define FOOD 'o'
#define EMPTY ' '

namespace game {

    void Nibbler::stop()
    {
        delete this;
    }

    std::shared_ptr<object::Rectangle> isWall(display::Vector2i pos)
    {
        std::shared_ptr<object::Rectangle> wall = std::make_shared<object::Rectangle>();
        wall->setPos(pos);
        wall->setSize(display::Vector2i{SIZE, SIZE});
        wall->setColor(display::WHITE);
        wall->setCharacter(WALL);
        wall->setText(WALL);
        wall->setCharacterColor(display::WHITE);
        return wall;
    }

    std::shared_ptr<object::Rectangle> isFood(display::Vector2i pos)
    {
        std::shared_ptr<object::Rectangle> food = std::make_shared<object::Rectangle>();
        food->setPos(pos);
        food->setSize(display::Vector2i{SIZE, SIZE});
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
        empty->setSize(display::Vector2i{SIZE, SIZE});
        empty->setColor(display::BLACK);
        empty->setCharacter(EMPTY);
        empty->setText(EMPTY);
        empty->setCharacterColor(display::BLACK);
        return empty;
    }

    void Nibbler::createMap(void)
    {
        std::string path = "src/GameModules/nibbler/lvl/" + std::to_string(lvl) + ".lvl";
        std::string line;
        std::ifstream myfile(path, std::ios::in);
        int i, j = 0;

        if (!myfile.is_open())
            std::cout << "Can not open file" << std::endl;

        while (std::getline(myfile, line)) {
            for (auto character : line) {
                if (character == WALL)
                    map[i][j++] = isWall(display::Vector2i{j+5, i+2});
                else if (character == FOOD)
                    map[i][j++] = isFood(display::Vector2i{j+5, i+2});
                else
                    map[i][j++] = isEmpty(display::Vector2i{j+5, i+2});
            }
            i++;
            j = 0;
        }
    }

    void Nibbler::init()
    {
        createHead();
        createMap();
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    void Nibbler::createHead(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setPos(display::Vector2i{16, 19});
        elem->setSize(display::Vector2i{SIZE, SIZE});
        elem->setColor(display::RED);
        elem->setCharacter('<');
        elem->setText('<');
        elem->setCharacterColor(display::BLACK);
        nibbler.push_back(elem);
    }

    void Nibbler::addElem(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setSize(display::Vector2i{SIZE, SIZE});
        if (direction == game::DIRECTION::UP)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y +
                        nibbler.at(nibbler.size() - 1)->getSize().y});
        if (direction == game::DIRECTION::RIGHT)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x -
                        nibbler.at(nibbler.size() - 1)->getSize().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y});
        if (direction == game::DIRECTION::DOWN)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y -
                        nibbler.at(nibbler.size() - 1)->getSize().y});
        if (direction == game::DIRECTION::LEFT)
            elem->setPos(display::Vector2i{nibbler.at(nibbler.size() - 1)->getPos().x +
                        nibbler.at(nibbler.size() - 1)->getSize().x,
                        nibbler.at(nibbler.size() - 1)->getPos().y});
        elem->setColor(display::RED);
        elem->setCharacter('*');
        elem->setText('*');
        elem->setCharacterColor(display::RED);
        nibbler.push_back(elem);
    }

    void Nibbler::checkWall(void)
    {
        for (int i = 0; i < 19; ++i) {
            for (int j = 0; j < 19; ++j) {
                if (nibbler.at(0)->getPos().x == walls.at(i)->getPos().x &&
                nibbler.at(0)->getPos().y == walls.at(i)->getPos().y) {
                    resetGame();
                }
            }
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

    void Nibbler::checkFood(void)
    {
        for (int i = 0; i < 19; ++i) {
            for (int j = 0; j < 19; ++j) {
                if (map[i][j]->getCharacter() == FOOD &&
                nibbler.at(0)->getPos().x == map[i][j]->getPos().x &&
                nibbler.at(0)->getPos().y == map[i][j]->getPos().y) {
                    map[i][j] = isEmpty(display::Vector2i{j+5, i+2});
                }
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
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    //1920 --> 158 = 12.15
    //1080 --> 42 = 25.7

    game::DIRECTION inverse(game::DIRECTION dir)
    {
        if (dir == game::DIRECTION::UP)
            return game::DIRECTION::DOWN;
        if (dir == game::DIRECTION::RIGHT)
            return game::DIRECTION::LEFT;
        if (dir == game::DIRECTION::LEFT)
            return game::DIRECTION::RIGHT;
        return game::DIRECTION::UP;
    }

    display::Vector2i randomPos(display::Vector2i pos, std::array<int, 4> possibleWay)
    {
        srand(time(NULL));
        int random = rand() % 4;
        if (possibleWay[0] == 0 && possibleWay[1] == 0 && possibleWay[2] == 0 && possibleWay[3] == 0)
            return pos;
        while (possibleWay[random] != 1)
            random = rand() % 4;
        if (random == 0)
            return display::Vector2i{pos.x, pos.y-SIZE};
        if (random == 1)
            return display::Vector2i{pos.x+SIZE, pos.y};
        if (random == 2)
            return display::Vector2i{pos.x-SIZE, pos.y};
        if (random == 3)
            return display::Vector2i{pos.x, pos.y+SIZE};
        return display::Vector2i{pos.x, pos.y};
    }

    display::Vector2i Nibbler::moveHead(display::Vector2i pos)
    {
        std::array<int, 4> possibleWay = {1, 1, 1, 1};

        possibleWay[inverse(direction)] = 0;
        if (map[pos.y-2][pos.x-5-SIZE]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::UP] = 0;
        if (map[pos.y-2+SIZE][pos.x-5]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::RIGHT] = 0;
        if (map[pos.y-2-SIZE][pos.x-5]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::LEFT] = 0;
        if (map[pos.y-2][pos.x-5+SIZE]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::DOWN] = 0;
        return randomPos(pos, possibleWay);
    }

    void Nibbler::move(display::IDisplayModule *display)
    {
        // display::Vector2i pos = nibbler.at(0)->getPos();
        // if (display->isButtonPressed(display::UP) && direction != game::DIRECTION::DOWN) {
        //     // for (long unsigned int i = nibbler.size()-1; i > 0; --i)
        //     //     nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
        //     //         nibbler.at(i-1)->getPos().y});
        //     // std::cout << "UP" << std::endl;
        //     pos.y -= SIZE;
        //     std::cout << std::to_string(pos.x) << std::to_string(pos.y) << std::endl;
        //     std::cout << "->" << map[pos.y-2][pos.x-5]->getCharacter() << "<-" << std::endl;
        // } else if (display->isButtonPressed(display::RIGHT) && direction != game::DIRECTION::LEFT) {
        //     // for (long unsigned int i = nibbler.size()-1; i > 0; --i)
        //     //     nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
        //     //         nibbler.at(i-1)->getPos().y});
        //     // std::cout << "RIGHT" << std::endl;
        //     pos.x += SIZE;
        //     std::cout << std::to_string(pos.x) << std::to_string(pos.y) << std::endl;
        //     std::cout << "->" << map[pos.y-2][pos.x-5]->getCharacter() << "<-" << std::endl;
        // } else if (display->isButtonPressed(display::LEFT) && direction != game::DIRECTION::RIGHT) {
        //     // for (long unsigned int i = nibbler.size()-1; i > 0; --i)
        //     //     nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
        //     //         nibbler.at(i-1)->getPos().y});
        //     // std::cout << "LEFT" << std::endl;
        //     pos.x -= SIZE;
        //     std::cout << std::to_string(pos.x) << std::to_string(pos.y) << std::endl;
        //     std::cout << "->" << map[pos.y-2][pos.x-5]->getCharacter() << "<-" << std::endl;
        // } else if (display->isButtonPressed(display::DOWN) && direction != game::DIRECTION::UP) {
        //     // for (long unsigned int i = nibbler.size()-1; i > 0; --i)
        //     //     nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
        //     //         nibbler.at(i-1)->getPos().y});
        //     // std::cout << "DOWN" << std::endl;
        //     pos.y += SIZE;
        //     std::cout << std::to_string(pos.x) << std::to_string(pos.y) << std::endl;
        //     std::cout << "->" << map[pos.y-2][pos.x-5]->getCharacter() << "<-" << std::endl;
        // }
        // // if (map[pos.x-5][pos.y-2]->getCharacter() == WALL) {
        // //     pos = moveHead(nibbler.at(0)->getPos());
        // // }
        // nibbler.at(0)->setPos(pos);
    }


    void Nibbler::update(display::IDisplayModule *display)
    {
        move(display);
        // checkBody();

        for (int i = 0; i < 19; ++i)
            for (int j = 0; j < 19; ++j)
                display->drawObj(map[i][j]);
        for (long unsigned int i = 0; i < nibbler.size(); ++i)
            display->drawObj(nibbler.at(i));
    }
}


extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Nibbler;
    }
}
