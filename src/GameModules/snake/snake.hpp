/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** snake.hpp
*/

#include "IGameModule.hpp"
#include <deque>
#include "../../Objects/Rectangle/Rectangle.hpp"

namespace game {

    enum DIRECTION {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    class Snake : public IGameModule {
        public:
            Snake() {};
            ~Snake() {};
            void init(void) override;
            void update(display::IDisplayModule *display) override;
            void stop(void) override;
            void addElem(void);
            void initApple(void);
            void createHead(void);
            void checkApple(void);
            void resetGame(void);
            void checkWall(void);
            void move(display::IDisplayModule *display);
            void createWall(display::Vector2i size);
        private:
            std::deque<std::shared_ptr<object::Rectangle>> snake;
            std::shared_ptr<object::Rectangle> apple;
            std::deque<std::shared_ptr<object::Rectangle>> walls;
            DIRECTION direction;
    };
}
