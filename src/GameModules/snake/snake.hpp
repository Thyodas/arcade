/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** snake.hpp
*/

#include "IGameModule.hpp"
#include "IObject.hpp"
#include <deque>

namespace game {

    enum DIRECTION {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    class Snake : public IGameModule {
        public:
            Snake() {
                direction = game::DIRECTION::RIGHT;
                score = 0;
            };
            ~Snake() {};
            void init(void) override;
            void update(display::IDisplayModule *display) override;
            void stop(arcade::ICore *core) override;
            void addElem(void);
            void initApple(void);
            void createHead(void);
            void checkApple(void);
            void resetGame(void);
            void checkWall(void);
            void checkBody(void);
            void move(display::IDisplayModule *display);
            void createWall(display::Vector2i size);
        private:
            std::deque<std::shared_ptr<object::Rectangle>> initString(std::string str, display::Vector2i pos, display::Color color);
        private:
            std::deque<std::shared_ptr<object::Rectangle>> snake;
            std::deque<std::shared_ptr<object::Rectangle>> _title;
            std::shared_ptr<object::Rectangle> apple;
            std::deque<std::shared_ptr<object::Rectangle>> walls;
            int score;
            DIRECTION direction;
    };
}
