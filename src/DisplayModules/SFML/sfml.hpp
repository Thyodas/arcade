/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** sfml.hpp
*/

#pragma once

#include "IDisplayModule.hpp"

#include "../../Objects/Rectangle/Rectangle.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <functional>
#include <vector>
#include <unordered_map>

class SFMLRenderer : public IDisplayModule {
    public:
        SFMLRenderer();
        ~SFMLRenderer();
        void init(Vector2i windowSize) override {};
        bool isButtonPressed(Button button) override;
        Vector2i getMousePos() const override;
        MouseButtonEvent getMouseButtonEvent() override;

        void close() override;

        void drawObj(std::shared_ptr<IObject> obj) override;
        void render() override;
        void clearWindow(Color color) override;
        void handleEvents() override;
    private:
        std::unordered_map<Button, sf::Keyboard::Key> _buttonsMap;
        std::unordered_map<Color, sf::Color> _colorsMap;
        std::unordered_map<sf::Event::EventType, std::unordered_map<sf::Mouse::Button, std::function<MouseButtonEvent(int x, int y)>>> _mouseMap;
        std::unordered_map<Type, std::function<void(std::shared_ptr<IObject> obj)>> _mapDecorator;
        void drawRect(std::shared_ptr<IObject> obj);

        sf::RenderWindow _window;
        sf::Event _event;
        std::vector<Button> _buttonsPressed;
        std::vector<MouseButtonEvent> _mouseEvents;
};