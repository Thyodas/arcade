/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** menu.hpp
*/

#include <deque>
#include <vector>
#include "IGameModule.hpp"
#include "IObject.hpp"
#include "Loader.hpp"

namespace game {
    class Menu : public IGameModule {
        public:
            Menu() {
                userNameStr = "";
            };
            ~Menu() {};
            void init() override;
            void update(display::IDisplayModule *display) override;
            void stop(arcade::ICore *core) override;
        private:
            std::deque<std::shared_ptr<object::Rectangle>> initString(std::string str, display::Vector2i pos, display::Color color);
            void createCursor(void);
            void testLib(const std::string pathToLib, display::Vector2i *gamePos, display::Vector2i *graphicPos);
            void setListLibs(void);
            void createBackground(void);
            std::string getPlayerScore(std::string game);
            void initControl(bool show);
        private:
            std::string _scoreStr;
            std::string userNameStr;
            std::vector<std::string> graphicLibsStr;
            std::vector<std::string> gameLibsStr;
            arcade::Loader loader;
            std::shared_ptr<object::Rectangle> cursor;
            std::vector<std::deque<std::shared_ptr<object::Rectangle>>> gameLibs;
            std::vector<std::deque<std::shared_ptr<object::Rectangle>>> graphicLibs;
            std::deque<std::shared_ptr<object::Rectangle>> background;
            std::deque<std::shared_ptr<object::Rectangle>> _userName;
            std::deque<std::shared_ptr<object::Rectangle>> _score;
            std::deque<std::shared_ptr<object::Rectangle>> titleUserName;
            std::deque<std::shared_ptr<object::Rectangle>> titleScore;
            std::deque<std::shared_ptr<object::Rectangle>> _title;
            std::deque<std::shared_ptr<object::Rectangle>> _control;
    };
}
