/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** sdl2.cpp
*/

#include "sdl2.hpp"
#include <stdexcept>
#include <memory>

namespace display {
    SDL2Renderer::SDL2Renderer()
    {
        if (SDL_Init(SDL_INIT_VIDEO) == -1)
            throw std::runtime_error("SDL2Renderer: " + std::string(SDL_GetError()));

        if ((_window = SDL_CreateWindow("Window, mehdy tg", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_ALLOW_HIGHDPI)) == nullptr)
            throw std::runtime_error("SDL2Renderer: " + std::string(SDL_GetError()));

        if ((_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED)) == nullptr)
            throw std::runtime_error("SDL2Renderer: " + std::string(SDL_GetError()));

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

        _colorsMap[BLACK] = SDL_Color{0, 0, 0, 100};
        _colorsMap[RED] = SDL_Color{255, 0, 0, 100};
        _colorsMap[GREEN] = SDL_Color{0, 255, 0, 100};
        _colorsMap[YELLOW] = SDL_Color{255, 255, 0, 100};
        _colorsMap[BLUE] = SDL_Color{0, 0, 255, 100};
        _colorsMap[MAGENTA] = SDL_Color{255, 0, 255, 100};
        _colorsMap[CYAN] = SDL_Color{0, 255, 255, 100};
        _colorsMap[WHITE] = SDL_Color{255, 255, 255, 100};

        _mapDecorator[object::RECTANGLE] = [this](std::shared_ptr<object::IObject> obj) { drawRect(obj); };
    }

    SDL2Renderer::~SDL2Renderer()
    {

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

    void SDL2Renderer::drawRect(std::shared_ptr<object::IObject> obj)
    {
        auto *rect = static_cast<object::Rectangle *>(obj.get());
        SDL_Rect rectToDraw = {
            .x = rect->getPos().x,
            .y = rect->getPos().y,
            .w = rect->getSize().x,
            .h = rect->getSize().y,
        };
        SDL_Color color = _colorsMap[rect->getColor()];
        SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(_renderer, &rectToDraw);
    }

    void SDL2Renderer::close()
    {
        SDL_DestroyRenderer(_renderer);
        SDL_DestroyWindow(_window);
        SDL_Quit();
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
        while (SDL_PollEvent(&_event)) {
            if (_event.type == SDL_EventType::SDL_QUIT) {
                _buttonsPressed.push_back(Button::F7);
                continue;
            }
            if (_event.type == SDL_EventType::SDL_KEYDOWN) {
                for (auto & it : _buttonsMap) {
                    if (it.second == _event.key.keysym.sym) {
                        _buttonsPressed.push_back(it.first);
                        break;
                    }
                }
            }
        }
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
    display::IDisplayModule *entryPoint()
    {
        return new display::SDL2Renderer;
    }
}