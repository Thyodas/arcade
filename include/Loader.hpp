/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Loader.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include "ICore.hpp"

extern "C" {
    #include <dlfcn.h>
}

namespace arcade {
    class Loader {
        protected:
            void *_graphicLib;
            void *_gameLib;
        public:
            Loader() {
                _graphicLib = nullptr;
                _gameLib = nullptr;
            };
            ~Loader() {
                if (_graphicLib)
                    dlclose(_graphicLib);
                if (_gameLib)
                    dlclose(_gameLib);
            }

            /**
             * @brief Close the handler of the graphic library
             */
            void closeGraphicLib() {
                if (_graphicLib)
                    dlclose(_graphicLib);
                _graphicLib = nullptr;
            }
            /**
             * @brief Close the handler of the game library
             */
            void closeGameLib() {
                if (_gameLib)
                    dlclose(_gameLib);
                _gameLib = nullptr;
            };

            /**
             * @brief This function will open the lib based on the path passed
             * in argument. MAKE SURE to check the return value of this function
             * as this function will not throw in case of an error
             * @param path
             * @return void*
             */
            void *loadLib(const std::string path) {
                char *error = NULL;
                void *handle = dlopen(path.c_str(), RTLD_LAZY);
                if (!handle || (error = dlerror()) != NULL)
                    return nullptr;
                return handle;
            }
            /**
             * @brief Set the Display object
             *
             * @param display
             */
            void setDisplay(void *display) {
                _graphicLib = display;
            }

            /**
             * @brief Set the Game object
             *
             * @param game
             */
            void setGame(void *game) {
                _gameLib = game;
            }
            /**
             * @brief Get the Entry Point object
             * This function return a certain type of library based on the handler
             * and the name of the entryPoint passed in argument. MAKE SURE
             * to check the return value of this function as it will not throw
             * in case of an error
             * @tparam T 
             * @param handle 
             * @param entryPoint 
             * @return T 
             */
            template<typename T>
            T getEntryPoint(void *handle, const char *entryPoint) const {
                char *error = NULL;
                T (*ptr)(void) = (T (*)(void))dlsym(handle, entryPoint);
                if ((error = dlerror()) != NULL)
                    return nullptr;
                return ptr();
            }
    };
}
