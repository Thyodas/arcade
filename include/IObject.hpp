/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** IObject.hpp
*/

#pragma once

#include "IDisplayModule.hpp"

enum Type {
    RECTANGLE,
    PLAYER,
    TEXT,
    CIRCLE,
};

class IObject {
    public:
        virtual Type getType() const = 0;

        virtual void setPos(IDisplayModule::Vector2i pos) = 0;
        virtual IDisplayModule::Vector2i getPos() const = 0;
        virtual void setSize(IDisplayModule::Vector2i size) = 0;
        virtual IDisplayModule::Vector2i getSize() const = 0;
        virtual void setTexture(std::string path) = 0;
        virtual std::string getTexture() const = 0;
        virtual void setCharacter(char c) = 0;
        virtual char getCharacter() const = 0;
        virtual void setColor(IDisplayModule::Color color) = 0;
        virtual IDisplayModule::Color getColor() const = 0;
};

class ARectangle : public IObject {
    protected:
        Type _id;

        IDisplayModule::Vector2i _pos;
        IDisplayModule::Vector2i _size;
        std::string _pathToTexture;
        int _borderThickness;
        IDisplayModule::Color _color;
        char _character;
};

