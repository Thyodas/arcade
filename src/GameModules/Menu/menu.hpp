/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.hpp
*/

#include <deque>
#include "IGameModule.hpp"
#include "IObject.hpp"
#include "Loader.hpp"

namespace game {
    class Menu : public IGameModule {
        public:
            Menu() {};
            ~Menu() {};
            void init() override;
            void update(display::IDisplayModule *display) override;
            void stop() override;
            std::deque<std::shared_ptr<object::Rectangle>> initString(std::string str, display::Vector2i pos);
            void createCursor();
            void testLib(const std::string pathToLib);
            void setListLibs();
            void createBackground(void);
        private:
            arcade::Loader loader;
            std::shared_ptr<object::Rectangle> cursor;
            std::vector<std::deque<std::shared_ptr<object::Rectangle>>> gameLibs;
            std::vector<std::deque<std::shared_ptr<object::Rectangle>>> graphicLibs;
            std::deque<std::shared_ptr<object::Rectangle>> background;
    };
}
