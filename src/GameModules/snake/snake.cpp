/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Snake.cpp
*/

#include "snake.hpp"
#include <vector>
#include <time.h>
#define SIZE 1

namespace game {

    void Snake::stop()
    {
        delete this;
    }

    void Snake::init()
    {
        createHead();
        initApple();
        createWall(display::Vector2i{56, 26});
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    void Snake::createWall(display::Vector2i size)
    {
        for (int i = 5; i <= size.x + 5; ++i)
            for (int j = 2; j <= size.y + 2; ++j) {
                if (i == 5 || j == 2 || i == size.x + 5 || j == size.y + 2) {
                    std::shared_ptr<object::Rectangle> wall = std::make_shared<object::Rectangle>();
                    wall->setPos(display::Vector2i{i, j});
                    wall->setSize(display::Vector2i{1, 1});
                    wall->setColor(display::WHITE);
                    wall->setCharacter('*');
                    wall->setCharacterColor(display::WHITE);
                    walls.push_back(wall);
                }
            }
    }

    void Snake::createHead(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setPos(display::Vector2i{33, 15});
        elem->setSize(display::Vector2i{SIZE, SIZE});
        elem->setColor(display::GREEN);
        elem->setCharacter('<');
        elem->setText('<');
        elem->setCharacterColor(display::BLACK);
        snake.push_back(elem);
    }

    display::Vector2i getRadomPos(void)
    {
        srand (time(NULL));
        int x = rand() % 54 + 6;
        while (x%2 == 0)
            x = rand() % 54 + 6;
        return (display::Vector2i{x, (rand() % 24) + 3});
    }

    void Snake::initApple(void)
    {
        apple = std::make_shared<object::Rectangle>();
        apple->setPos(getRadomPos());
        apple->setSize(display::Vector2i{1, 1});
        apple->setColor(display::RED);
        apple->setCharacter('`');
        apple->setText('`');
        apple->setCharacterColor(display::GREEN);
    }

    void Snake::addElem(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setSize(display::Vector2i{SIZE, SIZE});
        if (direction == game::DIRECTION::UP)
            elem->setPos(display::Vector2i{snake.at(snake.size() - 1)->getPos().x,
                        snake.at(snake.size() - 1)->getPos().y +
                        snake.at(snake.size() - 1)->getSize().y});
        if (direction == game::DIRECTION::RIGHT)
            elem->setPos(display::Vector2i{snake.at(snake.size() - 1)->getPos().x -
                        snake.at(snake.size() - 1)->getSize().x,
                        snake.at(snake.size() - 1)->getPos().y});
        if (direction == game::DIRECTION::DOWN)
            elem->setPos(display::Vector2i{snake.at(snake.size() - 1)->getPos().x,
                        snake.at(snake.size() - 1)->getPos().y -
                        snake.at(snake.size() - 1)->getSize().y});
        if (direction == game::DIRECTION::LEFT)
            elem->setPos(display::Vector2i{snake.at(snake.size() - 1)->getPos().x +
                        snake.at(snake.size() - 1)->getSize().x,
                        snake.at(snake.size() - 1)->getPos().y});
        elem->setColor(display::GREEN);
        elem->setCharacter('*');
        elem->setText('*');
        elem->setCharacterColor(display::GREEN);
        snake.push_back(elem);
    }

    void Snake::checkApple(void)
    {
        if (snake.at(0)->getPos().x == apple->getPos().x &&
        snake.at(0)->getPos().y == apple->getPos().y) {
            apple->setPos(getRadomPos());
            score++;
            addElem();
        }
    };

    void Snake::checkWall(void)
    {
        for (long unsigned int i = 0; i < walls.size(); ++i) {
            if (snake.at(0)->getPos().x == walls.at(i)->getPos().x &&
            snake.at(0)->getPos().y == walls.at(i)->getPos().y) {
                resetGame();
            }
        }
    };

    void Snake::checkBody(void)
    {
        for (long unsigned int i = 1; i < snake.size(); ++i) {
            if (snake.at(0)->getPos().x == snake.at(i)->getPos().x &&
            snake.at(0)->getPos().y == snake.at(i)->getPos().y) {
                resetGame();
            }
        }
    };

    void Snake::resetGame(void)
    {
        while (!snake.empty()) {
            snake.at(snake.size() - 1).reset();
            snake.pop_back();
        }
        direction = game::DIRECTION::RIGHT;
        createHead();
        score = 0;
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    //1920 --> 158 = 12.15
    //1080 --> 42 = 25.7

    void Snake::move(display::IDisplayModule *display)
    {
        if (display->isButtonPressed(display::UP) && direction != game::DIRECTION::DOWN) {
            direction = game::DIRECTION::UP;
            for (long unsigned int i = snake.size() - 1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                                        snake.at(i - 1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x,
                                snake.at(0)->getPos().y -
                                snake.at(snake.size() - 1)->getSize().y});
            snake.at(0)->setCharacter('v');
            snake.at(0)->setText('v');

        } else if (display->isButtonPressed(display::RIGHT) && direction != game::DIRECTION::LEFT) {
            direction = game::DIRECTION::RIGHT;
            for (long unsigned int i = snake.size() - 1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                                    snake.at(i - 1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x +
                                snake.at(snake.size() - 1)->getSize().x * 2,
                                snake.at(0)->getPos().y});
            snake.at(0)->setCharacter('<');
            snake.at(0)->setText('<');

        } else if (display->isButtonPressed(display::LEFT) && direction != game::DIRECTION::RIGHT) {
            direction = game::DIRECTION::LEFT;
            for (long unsigned int i = snake.size()-1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                    snake.at(i-1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x -
                                snake.at(snake.size() - 1)->getSize().x * 2,
                                snake.at(0)->getPos().y});
            snake.at(0)->setCharacter('>');
            snake.at(0)->setText('>');

        } else if (display->isButtonPressed(display::DOWN) && direction != game::DIRECTION::UP) {
            direction = game::DIRECTION::DOWN;
            for (long unsigned int i = snake.size() - 1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                    snake.at(i - 1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x,
                                snake.at(0)->getPos().y +
                                snake.at(snake.size() - 1)->getSize().y});
            snake.at(0)->setCharacter('^');
            snake.at(0)->setText('^');
        }
    }

    void Snake::update(display::IDisplayModule *display)
    {
        move(display);
        checkApple();
        checkWall();
        checkBody();

        display->drawObj(apple);
        for (long unsigned int i = 0; i < snake.size(); ++i)
            display->drawObj(snake.at(i));
        for (long unsigned int i = 0; i < walls.size(); ++i)
            display->drawObj(walls.at(i));
    }
}


extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Snake;
    }
}
