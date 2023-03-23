/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** IObject.hpp
*/

#pragma once

#include "IDisplayModule.hpp"

namespace object {
    enum Type {
        RECTANGLE,
    };

    class IObject {
        public:
            virtual Type getType() const = 0;

            virtual void setPos(display::Vector2i pos) = 0;
            virtual display::Vector2i getPos() const = 0;
            virtual void setSize(display::Vector2i size) = 0;
            virtual display::Vector2i getSize() const = 0;
            virtual void setTexture(std::string path) = 0;
            virtual std::string getTexture() const = 0;
            virtual void setCharacter(char c) = 0;
            virtual char getCharacter() const = 0;
            virtual void setCharacterColor(display::Color color) = 0;
            virtual display::Color getCharacterColor() const = 0;
            virtual void setColor(display::Color color) = 0;
            virtual display::Color getColor() const = 0;
    };

    class ARectangle : public IObject {
        protected:
            Type _id;

            display::Vector2i _pos;
            display::Vector2i _size;
            std::string _pathToTexture;
            int _borderThickness;
            display::Color _color;
            display::Color _characterColor;
            char _character;
    };
}

