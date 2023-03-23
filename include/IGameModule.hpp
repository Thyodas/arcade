/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** IGameModule.hpp
*/

#pragma once

#include "IDisplayModule.hpp"

namespace game {
    class IGameModule {
        public:
            virtual ~IGameModule() = default;
            virtual void init() = 0;
            virtual void update(display::IDisplayModule *display) = 0;
            virtual void stop() = 0;
    };
}

