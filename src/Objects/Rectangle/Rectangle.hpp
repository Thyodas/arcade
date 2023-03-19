/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Rectangle.cpp
*/

#pragma once

#include "IObject.hpp"
#include <iostream>

class Rectangle : public ARectangle {
    public:
        Rectangle() { _id = RECTANGLE; };
        virtual ~Rectangle() {};

        //Interface implementation
        Type getType() const override { return _id;};

        void setPos(IDisplayModule::Vector2i pos) {_pos = pos;};
        IDisplayModule::Vector2i getPos() const override { return _pos;};
        void setSize(IDisplayModule::Vector2i size) {_size = size;};
        IDisplayModule::Vector2i getSize() const override { return _size;};
        void setColor(IDisplayModule::Color color) {_color = color;};
        IDisplayModule::Color getColor() const {return _color;};
        //Graphic lib (SFML, SDL2)
        void setTexture(std::string path) {_pathToTexture = path;};
        std::string getTexture() const override { return _pathToTexture;};
        //Terminal graphical lib
        void setCharacter(char c) {_character = c;};
        char getCharacter() const override { return _character;};

        //Other internal logic
        int getBorderThickness() const {return _borderThickness;};
        void setBorderThickness(int thickness) {_borderThickness = thickness;};
        bool contains(IDisplayModule::Vector2i pos) const {
            if (pos.x >= _pos.x && pos.x <= (_pos.x + _size.x) &&
                pos.y >= _pos.y && pos.y <= (_pos.y + _size.y))
                return true;
            return false;
        }
};
