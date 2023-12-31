/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** ncurses.hpp
*/

#include "IDisplayModule.hpp"
#include "IObject.hpp"

#include <ncurses.h>

#include <map>
#include <functional>
#include <vector>
#include <unordered_map>

namespace display {

    enum EVENT_MODE {
        BASIC,
        TXT
    };

    class NcursesRenderer : public IDisplayModule {
        public:
            NcursesRenderer() : _pairsMap({{}}) {};
            ~NcursesRenderer() {};
            void init(Vector2i windowSize) override;
            bool isButtonPressed(Button button) override;

            void startTextInput() override;
            std::string getTextInput() override;
            void endTextInput() override;

            void close() override;

            void drawObj(std::shared_ptr<object::IObject> obj) override;
            void render() override;
            void clearWindow(Color color) override;
            void handleEvents() override;
        private:
            void drawRect(std::shared_ptr<object::IObject> obj);

            enum class PairNcurses {
                BLACK_PAIR,
                RED_PAIR,
                GREEN_PAIR,
                YELLOW_PAIR,
                BLUE_PAIR,
                MAGENTA_PAIR,
                CYAN_PAIR,
                WHITE_PAIR
            };
        private:
            Vector2i _sizeTerminal;
            Vector2i _sizeTerminalPixel;
            WINDOW *_window;

            std::unordered_map<Button, int> _buttonsMap;
            std::unordered_map<Color, short> _colorsMap;
            std::map<std::pair<Color, Color>, int> _pairsMap;
            std::map<object::Type, std::function<void(std::shared_ptr<object::IObject> obj)>> _mapDecorator;

            std::vector<Button> _buttonsPressed;
            EVENT_MODE _eventMode;
    };

}
