/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** ncurses.cpp
*/

#include "ncurses.hpp"
#include <memory>
#include <algorithm>
#include <sys/ioctl.h>
#include <unistd.h>

namespace display {

    void NcursesRenderer::init(__attribute__((unused))Vector2i windowSize)
    {
        _window = initscr();

        getmaxyx(_window, _sizeTerminal.y, _sizeTerminal.x);
        struct winsize ws;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
        _sizeTerminalPixel.x = ws.ws_col * 12.1;
        _sizeTerminalPixel.y = ws.ws_row * 25.7;

        nodelay(_window, TRUE);
        noecho();
        cbreak();
        mousemask(ALL_MOUSE_EVENTS, NULL);
        start_color();
        curs_set(0);

        _buttonsMap[LEFT] = 'q';
        _buttonsMap[UP] = 'z';
        _buttonsMap[RIGHT] = 'd';
        _buttonsMap[DOWN] = 's';
        _buttonsMap[KEY_F] = 'f';
        _buttonsMap[KEY_E] = 'e';
        _buttonsMap[ESC] = 27;
        _buttonsMap[F1] = 80;
        _buttonsMap[F2] = 81;
        _buttonsMap[F3] = KEY_F(3);
        _buttonsMap[F4] = KEY_F(4);
        _buttonsMap[F5] = KEY_F(5);
        _buttonsMap[F6] = KEY_F(6);
        _buttonsMap[F7] = KEY_F(7);

        _colorsMap[BLACK] = COLOR_BLACK;
        _colorsMap[RED] = COLOR_RED;
        _colorsMap[GREEN] = COLOR_GREEN;
        _colorsMap[YELLOW] = COLOR_YELLOW;
        _colorsMap[BLUE] = COLOR_BLUE;
        _colorsMap[MAGENTA] = COLOR_MAGENTA;
        _colorsMap[CYAN] = COLOR_CYAN;
        _colorsMap[WHITE] = COLOR_WHITE;

        for (int color1 = BLACK, pair = 1; color1 <= WHITE; color1++) {
            for (int color2 = BLACK; color2 <= WHITE; color2++, pair++) {
                init_pair(pair, _colorsMap[static_cast<Color>(color1)], _colorsMap[static_cast<Color>(color2)]);
                _pairsMap[std::make_pair(static_cast<Color>(color1), static_cast<Color>(color2))] = pair;
            }
        }

        _mapDecorator[object::RECTANGLE] = [this](std::shared_ptr<object::IObject> obj) { drawRect(obj); };
    }

    bool NcursesRenderer::isButtonPressed(Button button)
    {
        auto it = std::find(_buttonsPressed.begin(), _buttonsPressed.end(), button);
        if (it != _buttonsPressed.end()) {
            _buttonsPressed.erase(it);
            return true;
        }
        return false;
    }

    void NcursesRenderer::drawRect(std::shared_ptr<object::IObject> obj)
    {
        object::Rectangle *rect = static_cast<object::Rectangle *>(obj.get());
        int x = rect->getPos().x % _sizeTerminal.x;
        int y = rect->getPos().y % _sizeTerminal.y;
        char c = rect->getCharacter();
        int pair = _pairsMap[std::make_pair(rect->getCharacterColor(), rect->getColor())];
        attron(COLOR_PAIR(pair));
        for (int i = x; i < x + (rect->getSize().x*2) && i < _sizeTerminal.x; ++i)
            for (int j = y; j < y + rect->getSize().y && j < _sizeTerminal.y; ++j)
                mvaddch(j, i, c);
        attroff(COLOR_PAIR(pair));
    }

    void NcursesRenderer::close()
    {
        clear();
        endwin();
        delete this;
    }

    void NcursesRenderer::clearWindow(__attribute__((unused))Color color)
    {
        clear();
    }

    void NcursesRenderer::handleEvents()
    {
        getmaxyx(_window, _sizeTerminal.y, _sizeTerminal.x);
        int c;
        while ((c = getch()) != ERR) {
            for (auto it = _buttonsMap.begin() ; it != _buttonsMap.end() ; ++it) {
                if ((*it).second == c) {
                    clear();
                    _buttonsPressed.push_back((*it).first);
                    break;
                }
            }
        }
    }

    void NcursesRenderer::drawObj(std::shared_ptr<object::IObject> obj)
    {
        auto ptr = _mapDecorator[obj->getType()];
        ptr(obj);
    }

    void NcursesRenderer::render()
    {
        refresh();
    }

}


extern "C"
{
    display::IDisplayModule *entryPointDisplay()
    {
        return new display::NcursesRenderer;
    }
}

