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
        empty->setCharacter('.');
        empty->setText('.');
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
                    map[i][j++] = isWall(display::Vector2i{(j*2)+15, i+8});
                else if (character == FOOD)
                    map[i][j++] = isFood(display::Vector2i{(j*2)+15, i+8});
                else
                    map[i][j++] = isEmpty(display::Vector2i{(j*2)+15, i+8});
            }
            i++;
            j = 0;
        }
    }

    void Nibbler::init()
    {
        index.y = 17-6;
        index.x = 11+6;
        createHead();
        createMap();
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    void Nibbler::createHead(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setPos(display::Vector2i{37, 25});
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
        elem->setText('*');
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
            map[index.x][index.y] = isEmpty(display::Vector2i{pos.x, pos.y});
        }
    };

    void Nibbler::checkBody(void)
    {
        for (long unsigned int i = 1; i < nibbler.size(); ++i) {
            if (nibbler.at(0)->getPos().x == nibbler.at(i)->getPos().x &&
            nibbler.at(0)->getPos().y == nibbler.at(i)->getPos().y) {
                std::cout << "ok" << std::endl;
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
        if (map[index.x][index.y-SIZE]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::UP] = 0;
        if (map[index.x+SIZE][index.y]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::RIGHT] = 0;
        if (map[index.x-SIZE][index.y]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::LEFT] = 0;
        if (map[index.x][index.y+SIZE]->getCharacter() == WALL)
            possibleWay[game::DIRECTION::DOWN] = 0;
        return randomPos(pos, possibleWay);
    }

    void Nibbler::move(display::IDisplayModule *display)
    {
        display::Vector2i pos = nibbler.at(0)->getPos();
        if (display->isButtonPressed(display::UP) && direction != game::DIRECTION::DOWN) {
            if (map[index.x-SIZE][index.y]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.y -= SIZE;
                index.x -= SIZE;
                nibbler.at(0)->setPos(pos);
                direction = game::DIRECTION::UP;
            } else {
                std::cout << "It's a WALLLLLLL!!!!!!" << std::endl;
            }

        } else if (display->isButtonPressed(display::RIGHT) && direction != game::DIRECTION::LEFT) {
            if (map[index.x][index.y+SIZE]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.x += 2;
                index.y += SIZE;
                nibbler.at(0)->setPos(pos);
                direction = game::DIRECTION::RIGHT;
            } else {
                std::cout << "It's a WALLLLLLL!!!!!!" << std::endl;
            }

        } else if (display->isButtonPressed(display::LEFT) && direction != game::DIRECTION::RIGHT) {
            if (map[index.x][index.y-SIZE]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.x -= 2;
                index.y -= SIZE;
                nibbler.at(0)->setPos(pos);
                direction = game::DIRECTION::LEFT;
            } else {
                std::cout << "It's a WALLLLLLL!!!!!!" << std::endl;
            }

        } else if (display->isButtonPressed(display::DOWN) && direction != game::DIRECTION::UP) {
            if (map[index.x+SIZE][index.y]->getCharacter() != WALL) {
                for (long unsigned int i = nibbler.size()-1; i > 0; --i)
                    nibbler.at(i)->setPos(display::Vector2i{nibbler.at(i-1)->getPos().x,
                        nibbler.at(i-1)->getPos().y});
                pos.y += SIZE;
                index.x += SIZE;
                nibbler.at(0)->setPos(pos);
                direction = game::DIRECTION::DOWN;
            } else {
                std::cout << "It's a WALLLLLLL!!!!!!" << std::endl;
            }
        }
        // if (map[tmp.x][tmp.y]->getCharacter() == WALL) {
        //     // nibbler.at(0)->setPos(nibbler.at(0)->getPos());
        //     // pos = moveHead(nibbler.at(0)->getPos());
        // } else {
        //     index = tmp;
        //     nibbler.at(0)->setPos(pos);
        // }
    }


    void Nibbler::update(display::IDisplayModule *display)
    {
        move(display);
        // checkBody();
        // checkFood(nibbler.at(0)->getPos());

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
