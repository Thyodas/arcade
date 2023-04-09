/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** sdl2.cpp
*/

#include "sdl2.hpp"
#include <stdexcept>
#include <memory>
#include <algorithm>

namespace display {

    void SDL2Renderer::init(Vector2i windowSize)
    {
        if (SDL_Init(SDL_INIT_VIDEO) == -1 || TTF_Init() == -1)
            throw std::runtime_error("SDL2Renderer: " + std::string(SDL_GetError()));

        if ((_window = SDL_CreateWindow("Window SDL2", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, SDL_WINDOW_ALLOW_HIGHDPI)) == nullptr)
            throw std::runtime_error("SDL2Renderer: " + std::string(SDL_GetError()));

        if ((_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
            throw std::runtime_error("SDL2Renderer: " + std::string(SDL_GetError()));

        _arial = TTF_OpenFont("fonts/arial_narrow_7.ttf", 26);

        _buttonsMap[LEFT] = SDL_KeyCode::SDLK_q;
        _buttonsMap[UP] = SDL_KeyCode::SDLK_z;
        _buttonsMap[RIGHT] = SDL_KeyCode::SDLK_d;
        _buttonsMap[DOWN] = SDL_KeyCode::SDLK_s;
        _buttonsMap[KEY_F] = SDL_KeyCode::SDLK_f;
        _buttonsMap[KEY_E] = SDL_KeyCode::SDLK_e;
        _buttonsMap[ESC] = SDL_KeyCode::SDLK_ESCAPE;
        _buttonsMap[F1] = SDL_KeyCode::SDLK_F1;
        _buttonsMap[F2] = SDL_KeyCode::SDLK_F2;
        _buttonsMap[F3] = SDL_KeyCode::SDLK_F3;
        _buttonsMap[F4] = SDL_KeyCode::SDLK_F4;
        _buttonsMap[F5] = SDL_KeyCode::SDLK_F5;
        _buttonsMap[F6] = SDL_KeyCode::SDLK_F6;
        _buttonsMap[F7] = SDL_KeyCode::SDLK_F7;

        for (const auto &item: _buttonsMap)
            _buttonsPressedMap[item.first] = false;

        _colorsMap[BLACK] = SDL_Color{0, 0, 0, 100};
        _colorsMap[RED] = SDL_Color{255, 0, 0, 100};
        _colorsMap[GREEN] = SDL_Color{0, 255, 0, 100};
        _colorsMap[YELLOW] = SDL_Color{255, 255, 0, 100};
        _colorsMap[BLUE] = SDL_Color{0, 0, 255, 100};
        _colorsMap[MAGENTA] = SDL_Color{255, 0, 255, 100};
        _colorsMap[CYAN] = SDL_Color{0, 255, 255, 255};
        _colorsMap[WHITE] = SDL_Color{255, 255, 255, 100};

        _eventMode = BASIC;
        _mapDecorator[object::RECTANGLE] = [this](std::shared_ptr<object::IObject> obj) { drawRect(obj); };
    }

    bool SDL2Renderer::isButtonPressed(Button button)
    {
        auto it = std::find(_buttonsPressed.begin(), _buttonsPressed.end(), button);
        if (it != _buttonsPressed.end()) {
            _buttonsPressed.erase(it);
            return true;
        }
        return false;
    }

    Vector2i SDL2Renderer::convertCellPosToPixelPos(Vector2i cellPos) const
    {
        return {cellPos.x * 12, cellPos.y * 26};
    }

    void SDL2Renderer::drawRect(std::shared_ptr<object::IObject> obj)
    {
        auto *rect = static_cast<object::Rectangle *>(obj.get());
        Vector2i pixelPos = convertCellPosToPixelPos(rect->getPos());
        Vector2i pixelSize = convertCellPosToPixelPos(rect->getSize());
        pixelSize.x *= 2;
        SDL_Rect rectToDraw = {
            .x = pixelPos.x,
            .y = pixelPos.y,
            .w = pixelSize.x,
            .h = pixelSize.y,
        };
        SDL_Color color = _colorsMap[rect->getColor()];
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(_renderer, &rectToDraw);

        if (rect->getText() == 0)
            return;
        std::string string;
        string.push_back(rect->getText());
        SDL_Surface *text_surface = TTF_RenderText_Solid(_arial, string.c_str(),
            _colorsMap[rect->getCharacterColor()]);
        SDL_Texture *text_texture = SDL_CreateTextureFromSurface(_renderer,
            text_surface);
        SDL_SetTextureAlphaMod(text_texture, 255);
        rectToDraw.w /= 2;
        rectToDraw.x += rectToDraw.w / 2 + text_surface->w / 2;
        SDL_RenderCopy(_renderer, text_texture, nullptr, &rectToDraw);
        SDL_FreeSurface(text_surface);
        SDL_DestroyTexture(text_texture);
    }

    void SDL2Renderer::close()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        TTF_Quit();
        delete this;
    }

    void SDL2Renderer::clearWindow(Color color)
    {
        SDL_Color sdl_color = _colorsMap[color];
        SDL_SetRenderDrawColor(_renderer, sdl_color.r, sdl_color.g,
            sdl_color.b, sdl_color.a);
        SDL_RenderClear(_renderer);
    }

    void SDL2Renderer::handleEvents()
    {
        _buttonsPressed.clear();
        _buttonsPressedMap.clear();
        if (_eventMode == TXT)
            return;
        while (SDL_PollEvent(&_event)) {
            if (_event.type == SDL_EventType::SDL_QUIT) {
                _buttonsPressed.push_back(Button::F7);
                continue;
            }
            if (_event.type == SDL_EventType::SDL_KEYDOWN) {
                for (auto & it : _buttonsMap) {
                    if (it.second == _event.key.keysym.sym) {
                        _buttonsPressedMap[it.first] = true;
                        break;
                    }
                }
            }
            if (_event.type == SDL_EventType::SDL_KEYUP) {
                for (auto & it : _buttonsMap) {
                    if (it.second == _event.key.keysym.sym) {
                        _buttonsPressedMap[it.first] = false;
                        break;
                    }
                }
            }
        }
        for (const auto &item: _buttonsPressedMap)
            if (item.second)
                _buttonsPressed.push_back(item.first);
    }

    void SDL2Renderer::startTextInput()
    {
        _eventMode = TXT;
    }

    std::string SDL2Renderer::getTextInput()
    {
        static std::string userName;
        int key;
        while (SDL_PollEvent(&_event)) {
            if (_event.type == SDL_EventType::SDL_QUIT) {
                _buttonsPressed.push_back(Button::F7);
                continue;
            }
            if (_event.type == SDL_EventType::SDL_KEYDOWN) {
                key = _event.key.keysym.sym;
                if (key == SDLK_RETURN || key == SDLK_RETURN2) {
                    endTextInput();
                    return "\n";
                }
                if (key == 8 && userName.size() > 0)
                    userName.pop_back();
                if (userName.size() == 11)
                    break;
                if (key == ' ')
                    userName += '_';
                if (key >= 'a' && key <= 'z')
                    userName += key;
                if (key >= '0' && key <= '9')
                    userName += key;
            }
        }
        return userName;
    }

    void SDL2Renderer::endTextInput()
    {
        _eventMode = BASIC;
    }


    void SDL2Renderer::drawObj(std::shared_ptr<object::IObject> obj)
    {
        auto ptr = _mapDecorator[obj->getType()];
        ptr(obj);
    }

    void SDL2Renderer::render()
    {
        SDL_RenderPresent(_renderer);
    }

}


extern "C"
{
    display::IDisplayModule *entryPointDisplay()
    {
        return new display::SDL2Renderer;
    }
}