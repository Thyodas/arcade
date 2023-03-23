/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** IDisplayModule.hpp
*/

#pragma once

#include <iostream>
#include <memory>

namespace object {
    class IObject;
}

namespace display {
    struct Vector2i {
        int x;
        int y;
    };
    enum Color {
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
    };
    enum Button {
        LEFT,
        UP,
        RIGHT,
        DOWN,
        KEY_F,
        KEY_E,
        ESC,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7
    };
    class IDisplayModule {
        public:
            virtual ~IDisplayModule() = default;


            virtual void init(Vector2i windowSize) = 0;
            virtual void close() = 0;


            virtual bool isButtonPressed(Button button) = 0;


            virtual void drawObj(std::shared_ptr<object::IObject> obj) = 0;
            virtual void render() = 0;
            virtual void clearWindow(Color color) = 0;
            virtual void handleEvents() = 0;
    };
}


