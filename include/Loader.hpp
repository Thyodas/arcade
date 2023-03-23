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

            void closeGraphicLib() {
                if (_graphicLib)
                    dlclose(_graphicLib);
                _graphicLib = nullptr;
            }
            void closeGameLib() {
                if (_gameLib)
                    dlclose(_gameLib);
                _gameLib = nullptr;
            };

            void *loadLib(const std::string path) {
                char *error = NULL;
                void *handle = dlopen(path.c_str(), RTLD_LAZY);
                if (!handle || (error = dlerror()) != NULL)
                    throw Error(error);
                return handle;
            }

            void setDisplay(void *display) {
                _graphicLib = display;
            }

            void setGame(void *game) {
                _gameLib = game;
            }

            template<typename T>
            T *getEntryPoint(void *handle) const {
                char *error = NULL;
                T *(*ptr)(void) = (T *(*)(void))dlsym(handle, "entryPoint");
                if ((error = dlerror()) != NULL) {
                    throw Error(error);
                }
                return dynamic_cast<T *>(ptr());
            }
    };
}
