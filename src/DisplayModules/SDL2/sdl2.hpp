/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** sdl2.hpp
*/

#pragma once

#include "IDisplayModule.hpp"
#include "IObject.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <functional>
#include <vector>
#include <unordered_map>

namespace display {
    class SDL2Renderer : public IDisplayModule {
        public:
            SDL2Renderer() {};
            ~SDL2Renderer() {};
            void init(Vector2i windowSize) override;
            bool isButtonPressed(Button button) override;

            void startTextInput() override {};
            std::string getTextInput() override {};
            void endTextInput() override {};

            void close() override;

            void drawObj(std::shared_ptr<object::IObject> obj) override;
            void render() override;
            void clearWindow(Color color) override;
            void handleEvents() override;
        private:
            Vector2i convertCellPosToPixelPos(Vector2i pixelPos) const;
        private:
            std::unordered_map<Button, SDL_KeyCode> _buttonsMap;
            std::unordered_map<Button, bool> _buttonsPressedMap;
            std::unordered_map<Color, SDL_Color> _colorsMap;
            std::unordered_map<object::Type, std::function<void(std::shared_ptr<object::IObject> obj)>> _mapDecorator;
            void drawRect(std::shared_ptr<object::IObject> obj);

            SDL_Window *_window;
            SDL_Renderer *_renderer;
            TTF_Font *_arial;
            SDL_Event _event;
            std::vector<Button> _buttonsPressed;
    };

}
