/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** nibbler.hpp
*/

#include "IGameModule.hpp"
#include "IObject.hpp"
#include <deque>
#include <array>

namespace game {

    enum DIRECTION {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    class Nibbler : public IGameModule {
        public:
            Nibbler() {
                direction = game::DIRECTION::RIGHT;
                score = 0;
                lvl = 4;
            };
            ~Nibbler() {};
            void init(void) override;
            void update(display::IDisplayModule *display) override;
            void stop(void) override;
            void addElem(void);
            void initApple(void);
            void createHead(void);
            void resetGame(void);
            void createMap(void);
            void checkWall(void);
            void checkBody(void);
            void checkFood(display::Vector2i pos);
            void move(display::IDisplayModule *display);
            void moveHead(game::DIRECTION way);
            game::DIRECTION  choseWay(void);
        private:
            std::deque<std::shared_ptr<object::Rectangle>> nibbler;
            std::array<std::array<std::shared_ptr<object::Rectangle>, 19>, 19> map;
            std::deque<std::shared_ptr<object::Rectangle>> walls;
            int lvl;
            int score;
            DIRECTION direction;
            display::Vector2i index;
    };
}
