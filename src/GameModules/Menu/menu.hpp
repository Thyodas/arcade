/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.hpp
*/

#include "IGameModule.hpp"
#include "IObject.hpp"
#include <deque>

namespace game {
    class Menu : public IGameModule {
        public:
            Menu() {};
            ~Menu() {};
            void init() override;
            void update(display::IDisplayModule *display) override;
            void stop() override;
            void initString(std::string str);
        private:
            std::shared_ptr<object::Rectangle> cursor;
            std::deque<std::shared_ptr<object::Rectangle>> menu;
    };
}
