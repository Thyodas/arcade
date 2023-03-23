/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** snake.hpp
*/

#include "IGameModule.hpp"
#include "../../Objects/Rectangle/Rectangle.hpp"

namespace game {
    class Snake : public IGameModule {
        public:
            Snake() {};
            ~Snake() {};
            void init() override;
            void update(display::IDisplayModule *display) override;
            void stop() override;
    };
}
