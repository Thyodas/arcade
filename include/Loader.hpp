/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Loader.hpp
*/

#include <iostream>
#include <memory>
#include "ICore.hpp"

extern "C" {
    #include <dlfcn.h>
}

class Loader {
    protected:
        static std::shared_ptr<Loader> _loader;
        void *_graphicLib;
        void *_gameLib;
    public:
        Loader() {
            _graphicLib = nullptr;
            _gameLib = nullptr;
        };
        Loader(Loader &other) = delete;
        void operator=(const Loader &) = delete;

        static std::shared_ptr<Loader> getLoader() {
            if (_loader == nullptr)
                _loader =  std::make_shared<Loader>();
            return _loader;
        }

        void closeGraphicLib() { dlclose(_graphicLib); _graphicLib = nullptr; }
        void closeGameLib() {dlclose(_gameLib); _gameLib = nullptr; };
        void *setGraphicLib(const std::string path) {
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle)
                throw Error(dlerror());
            if (_graphicLib)
                dlclose(_graphicLib);
            _graphicLib = handle;
            return _graphicLib;
        };
        void *setGameLib(const std::string path) {
            void *handle = dlopen(path.c_str(), RTLD_LAZY);
            if (!handle)
                throw Error(dlerror());
            if (_gameLib)
                dlclose(_gameLib);
            _gameLib = handle;
            return _gameLib;
        };
};

std::shared_ptr<Loader> Loader::_loader = nullptr;

