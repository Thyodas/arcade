/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** ICore.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

namespace arcade {
    class ICore {
        public:
            virtual void mainLoop(const std::string displayLib) = 0;

            virtual void setFramerate(int framerate) = 0;
            virtual int getFramerate() const = 0;
            virtual void setScore(int score) = 0;
            virtual int getScore() const = 0;
            virtual std::string getPlayerName() const = 0;
            virtual void setPlayerName(std::string name) = 0;

            virtual void setDisplayModule(const std::string pathToLib) = 0;
            virtual void setGameModule(const std::string pathToLib) = 0;
    };

    class Error : public std::exception {
        public:
            ~Error() {};
            Error(std::string error);
            const char *what() const noexcept override;
        private:
            std::string _error;
    };
}
