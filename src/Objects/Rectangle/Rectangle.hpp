/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Rectangle.cpp
*/

#pragma once

#include "IObject.hpp"
#include <iostream>

namespace object {
    class Rectangle : public ARectangle {
        public:
            Rectangle() {
                _id = RECTANGLE;
                _text = 0;
            };
            virtual ~Rectangle() {};

            //Interface implementation
            Type getType() const override { return _id;};

            void setPos(display::Vector2i pos) {_pos = pos;};
            display::Vector2i getPos() const override { return _pos;};
            void setSize(display::Vector2i size) {_size = size;};
            display::Vector2i getSize() const override { return _size;};
            void setColor(display::Color color) {_color = color;};
            display::Color getColor() const {return _color;};
            //Graphic lib (SFML, SDL2)
            void setTexture(std::string path) {_pathToTexture = path;};
            std::string getTexture() const override { return _pathToTexture;};
            //Terminal graphical lib
            void setCharacter(char c) {_character = c;};
            char getCharacter() const override { return _character;};
            void setCharacterColor(display::Color color) override {_characterColor = color;};
            display::Color getCharacterColor() const override { return _characterColor;};

            //Other internal logic
            int getBorderThickness() const {return _borderThickness;};
            void setBorderThickness(int thickness) {_borderThickness = thickness;};
            bool contains(display::Vector2i pos) const {
                if (pos.x >= _pos.x && pos.x <= (_pos.x + _size.x) &&
                    pos.y >= _pos.y && pos.y <= (_pos.y + _size.y))
                    return true;
                return false;
            }
            char getText(void) const {return _text;};
            void setText(char text) {_text = text;};
    };
}


