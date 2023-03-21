/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** ncurses.hpp
*/

#include "IDisplayModule.hpp"

#include "../../Objects/Rectangle/Rectangle.hpp"

#include <ncurses.h>

#include <map>
#include <functional>
#include <vector>
#include <unordered_map>

class NcursesRenderer : public IDisplayModule {
    public:
        NcursesRenderer();
        ~NcursesRenderer();
        void init(Vector2i windowSize) override {};
        bool isButtonPressed(Button button) override;
        Vector2i getMousePos() const override;
        MouseButtonEvent getMouseButtonEvent() override;

        void close() override;

        void drawObj(std::shared_ptr<IObject> obj) override;
        void render() override;
        void clearWindow(Color color) override;
        void handleEvents() override;
    private:
        Vector2i convertPixelPosToCellPos(Vector2i pixelPos) const;
        void drawRect(std::shared_ptr<IObject> obj);

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
        std::unordered_map<char, IDisplayModule::MouseButtonEvent::MouseButton> _mouseButtonMap;
        std::unordered_map<long, std::function<MouseButtonEvent(int x, int y)>> _mouseMap;
        std::map<Type, std::function<void(std::shared_ptr<IObject> obj)>> _mapDecorator;

        std::vector<Button> _buttonsPressed;
        std::vector<MouseButtonEvent> _mouseEvents;
};