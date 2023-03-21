/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** ncurses.cpp
*/

#include "ncurses.hpp"
#include <memory>
#include <sys/ioctl.h>
#include <unistd.h>

NcursesRenderer::NcursesRenderer()
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

    _buttonsMap[LEFT] = 'q';
    _buttonsMap[UP] = 'z';
    _buttonsMap[RIGHT] = 'd';
    _buttonsMap[DOWN] = 's';
    _buttonsMap[KEY_Q] = 'f';
    _buttonsMap[KEY_E] = 'e';
    _buttonsMap[ESC] = 27;
    _buttonsMap[F1] = 80;
    _buttonsMap[F2] = KEY_F(2);
    _buttonsMap[F3] = KEY_F(3);
    _buttonsMap[F4] = KEY_F(4);
    _buttonsMap[F5] = KEY_F(5);
    _buttonsMap[F6] = KEY_F(6);
    _buttonsMap[F7] = KEY_F(7);

    _mouseMap[BUTTON1_PRESSED] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::PRESSED,
                                MouseButtonEvent::MouseButton::LEFT,
                                Vector2i{x, y}};
    };
    _mouseMap[BUTTON2_PRESSED] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::PRESSED,
                                MouseButtonEvent::MouseButton::RIGHT,
                                Vector2i{x, y}};
    };
    _mouseMap[BUTTON1_RELEASED] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::RELEASED,
                                MouseButtonEvent::MouseButton::LEFT,
                                Vector2i{x, y}};
    };
    _mouseMap[BUTTON2_RELEASED] = [](int x, int y) {
        return MouseButtonEvent{MouseButtonEvent::MouseEventType::RELEASED,
                                MouseButtonEvent::MouseButton::LEFT,
                                Vector2i{x, y}};
    };

    _mapDecorator[RECTANGLE] = [this](IObject *obj) { drawRect(obj); };
}

NcursesRenderer::~NcursesRenderer()
{

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

IDisplayModule::Vector2i NcursesRenderer::getMousePos() const
{
    MEVENT event;
    getmouse(&event);
    return Vector2i{event.x, event.y};
}

IDisplayModule::MouseButtonEvent NcursesRenderer::getMouseButtonEvent()
{
    if (_mouseEvents.empty())
        return MouseButtonEvent{MouseButtonEvent{MouseButtonEvent::MouseEventType::NONE,
                                MouseButtonEvent::MouseButton::NONE,
                                Vector2i{0, 0}}};
    return _mouseEvents.front();
}

IDisplayModule::Vector2i NcursesRenderer::convertPixelPosToCellPos(Vector2i pixelPos) const
{
    return {(int)(pixelPos.x / 12.1), (int)(pixelPos.y / 25.7)};
}

void NcursesRenderer::drawRect(IObject *obj)
{
    Rectangle *rect = static_cast<Rectangle *>(obj);
    Vector2i cellPos = convertPixelPosToCellPos(rect->getPos());
    Vector2i cellSize = convertPixelPosToCellPos(rect->getSize());
    int x = cellPos.x;
    int y = cellPos.y;
    char c = rect->getCharacter();
    for (int i = x; i < x + cellSize.x && i < _sizeTerminal.x; ++i)
        for (int j = y; j < y + cellSize.y && j < _sizeTerminal.y; ++j)
            mvprintw(j, i, "%c", c);
}

void NcursesRenderer::close()
{
    endwin();
}

void NcursesRenderer::clearWindow(Color color)
{
    refresh();
}

void NcursesRenderer::handleEvents()
{
    MEVENT event;
    int c = getch();
    for (auto it = _buttonsMap.begin(); it != _buttonsMap.end(); ++it) {
        if ((*it).second == c) {
            clear();
            _buttonsPressed.push_back((*it).first);
            break;
        }
    }
    if (c == KEY_MOUSE && getmouse(&event) == OK) {
        for (auto it = _mouseMap.begin(); it != _mouseMap.end(); ++it) {
            if ((*it).first & event.bstate) {
                clear();
                _mouseEvents.push_back(((*it).second)(event.x, event.y));
                break;
            }
        }
    }
}

void NcursesRenderer::drawObj(IObject *obj)
{
    auto ptr = _mapDecorator[obj->getType()];
    ptr(obj);
}

void NcursesRenderer::render()
{

}

extern "C"
{
    std::unique_ptr<IDisplayModule> entryPointDisplay()
    {
        return std::make_unique<NcursesRenderer>();
    }
}

