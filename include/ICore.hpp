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
/**
 * @brief This namespace will contain all of the core element of
 * the project
 */
namespace arcade {
    /**
     * @brief Main interface for our core class
     * You have to implement this interface in order for the arcade to work.
     */
    class ICore {
        public:
            virtual ~ICore() = default;
            /**
             * @brief Main core loop, this is the method that we
             * will call and that will handle our main loop.
             */
            virtual void mainLoop(const std::string displayLib) = 0;
            /**
             * @brief Set the Framerate object
             *
             * @param framerate
             */
            virtual void setFramerate(int framerate) = 0;
            /**
             * @brief Get the Framerate object
             *
             * @return int
             */
            virtual int getFramerate() const = 0;
            /**
             * @brief Set the Score object
             *
             * @param score
             */
            virtual void setScore(int score) = 0;
            /**
             * @brief This function will be called when a game is finished or the user exits a game
             * It could probably be smart to implement an observer here but i'm lazy
             * @param score
             */
            virtual int getScore() const = 0;
            /**
             * @brief Get the Player Name object
             *
             * @return std::string
             */
            virtual std::string getPlayerName() const = 0;
            /**
             * @brief Set the Player object
             *
             * @param name
             */
            virtual void setPlayerName(std::string name) = 0;

            /**
             * @brief Set the Display Module object
             *
             * @param display
             */
            virtual void setDisplayModule(const std::string pathToLib) = 0;
            /**
             * @brief Set the Game Module object
             *
             * @param game
             */
            virtual void setGameModule(const std::string pathToLib) = 0;
    };

    /**
     * @brief This our error class
     * This class derives from std::exception and allows us to implement
     * custom error messages
     */
    class Error : public std::exception {
        public:
            ~Error() {};
            Error(std::string error);
            const char *what() const noexcept override;
        private:
            std::string _error;
    };
}
