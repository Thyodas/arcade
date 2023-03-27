/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.hpp
*/

#include "IGameModule.hpp"
#include "../../Objects/Rectangle/Rectangle.hpp"

namespace game {
    class Menu : public IGameModule {
        public:
            Menu() {};
            ~Menu() {};
            void init() override;
            void update(display::IDisplayModule *display) override;
            void stop() override;
        private:
            std::shared_ptr<object::Rectangle> rect;
    };
}
