/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** sfml.hpp
*/

#pragma once

#include "IDisplayModule.hpp"
#include "IObject.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <functional>
#include <vector>
#include <unordered_map>

namespace display {

    enum EVENT_MODE {
        BASIC,
        TXT
    };

    class SFMLRenderer : public IDisplayModule {
        public:
            SFMLRenderer() {};
            ~SFMLRenderer() {};
            void init(Vector2i windowSize) override;
            bool isButtonPressed(Button button) override;

            void startTextInput() override;
            std::string getTextInput() override;
            void endTextInput() override;

            void close() override;

            void drawObj(std::shared_ptr<object::IObject> obj) override;
            void render() override;
            void clearWindow(Color color) override;
            void handleEvents() override;
        private:
            sf::Vector2f convertCellPosToPixelPos(Vector2i pixelPos) const;
        private:
            std::unordered_map<Button, sf::Keyboard::Key> _buttonsMap;
            std::unordered_map<Color, sf::Color> _colorsMap;
            std::unordered_map<object::Type, std::function<void(std::shared_ptr<object::IObject> obj)>> _mapDecorator;
            void drawRect(std::shared_ptr<object::IObject> obj);

            sf::RenderWindow _window;
            sf::Event _event;
            sf::Font _arial;
            std::vector<Button> _buttonsPressed;
            EVENT_MODE _eventMode;
    };

}
