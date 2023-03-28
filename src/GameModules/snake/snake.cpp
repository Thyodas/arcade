/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Snake.cpp
*/

#include "snake.hpp"
#include <vector>
#define SIZE 2

namespace game {

    void Snake::stop()
    {
        delete this;
    }

    void Snake::init()
    {
        direction = game::DIRECTION::RIGHT;
        createHead();
        for (int i = 0; i < 4; ++i)
            addElem();
    }

    void Snake::createHead(void)
    {
        std::shared_ptr<object::Rectangle> elem = std::make_shared<object::Rectangle>();
        elem->setPos(display::Vector2i{60, 30});
        elem->setSize(display::Vector2i{SIZE, SIZE});
        elem->setColor(display::GREEN);
        elem->setCharacter('*');
        snake.push_back(elem);
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
                                            snake.at(snake.size() - 1)->getPos().y});
        if (direction == game::DIRECTION::LEFT)
            elem->setPos(display::Vector2i{snake.at(snake.size() - 1)->getPos().x +
                                            snake.at(snake.size() - 1)->getSize().x,
                                            snake.at(snake.size() - 1)->getPos().y -
                                            snake.at(snake.size() - 1)->getSize().y});
        elem->setColor(display::GREEN);
        elem->setCharacter('*');
        snake.push_back(elem);
    }

    //1920 --> 158 = 12.15
    //1080 --> 42 = 25.7

    void Snake::update(display::IDisplayModule *display)
    {
        if (display->isButtonPressed(display::UP)) {
            direction = game::DIRECTION::UP;
            for (long unsigned int i = snake.size() - 1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                                        snake.at(i - 1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x,
                                snake.at(0)->getPos().y -
                                snake.at(snake.size() - 1)->getSize().y});
        } else if (display->isButtonPressed(display::RIGHT)) {
            direction = game::DIRECTION::RIGHT;
            for (long unsigned int i = snake.size() - 1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                                    snake.at(i - 1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x +
                                snake.at(snake.size() - 1)->getSize().x,
                                snake.at(0)->getPos().y});
        } else if (display->isButtonPressed(display::LEFT)) {
            direction = game::DIRECTION::LEFT;
            for (long unsigned int i = snake.size()-1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                    snake.at(i-1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x -
                                snake.at(snake.size() - 1)->getSize().x,
                                snake.at(0)->getPos().y});
        } else if (display->isButtonPressed(display::DOWN)) {
            direction = game::DIRECTION::DOWN;
            for (long unsigned int i = snake.size() - 1; i > 0; --i)
                snake.at(i)->setPos(display::Vector2i{snake.at(i - 1)->getPos().x,
                                    snake.at(i - 1)->getPos().y});
            snake.at(0)->setPos(display::Vector2i{snake.at(0)->getPos().x,
                                                snake.at(0)->getPos().y +
                                                snake.at(snake.size() - 1)->getSize().y});
        }
        for (long unsigned int i = 0; i < snake.size(); ++i)
            display->drawObj(snake.at(i));
    }

}


extern "C"
{
    game::IGameModule *entryPointGame()
    {
        return new game::Snake;
    }
}
