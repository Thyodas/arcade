/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** nibbler.hpp
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

    class Nibbler : public IGameModule {
        public:
            Nibbler() {
                direction = game::DIRECTION::RIGHT;
                score = 0;
                lvl = 1;
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
            void move(display::IDisplayModule *display);
            display::Vector2i moveHead(display::Vector2i pos);
            void checkFood(void);
        private:
            std::deque<std::shared_ptr<object::Rectangle>> nibbler;
            std::array<std::array<std::shared_ptr<object::Rectangle>, 19>, 19> map;
            std::deque<std::shared_ptr<object::Rectangle>> walls;
            int lvl;
            int score;
            DIRECTION direction;
    };
}