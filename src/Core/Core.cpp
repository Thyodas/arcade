/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Core.cpp
*/

#include "Core.hpp"
#include "Loader.hpp"
#include <vector>
#include <unistd.h>
#include <csignal>
#include <filesystem>
#include <iostream>

namespace arcade {
    bool Core::_loop = true;

    Error::Error(std::string error)
    : _error(std::move(error))
    {
    }

    const char *Error::what() const noexcept
    {
        return _error.c_str();
    }

    Core::Core()
    {
        _framerate = 60;
        _score = 0;
        _playerName = "";
        _indexGameLibs = 0;
        _indexGraphicLibs = 0;
    }

    Core::~Core() {}

    void Core::setFramerate(int framerate)
    {
        _framerate = framerate;
    }

    int Core::getFramerate() const
    {
        return _framerate;
    }

    void Core::setScore(int score)
    {
        _score = score;
    }

    int Core::getScore() const
    {
        return _score;
    }

    void Core::setPlayerName(std::string playerName)
    {
        _playerName = playerName;
    }

    std::string Core::getPlayerName() const
    {
        return _playerName;
    }

    void Core::setDisplayModule(const std::string pathToLib)
    {
        void *handle = _loader.loadLib(pathToLib);
        if (!handle)
            throw Error("Couldn't load display lib");
        _loader.closeGraphicLib();
        _display = _loader.getEntryPoint<display::IDisplayModule *>(handle, "entryPointDisplay");
        if (_display == nullptr)
            throw Error("Couldn't get entry point");
        _loader.setDisplay(handle);
    }

    void Core::setGameModule(const std::string pathToLib)
    {
        void *handle = _loader.loadLib(pathToLib);
        if (!handle)
            throw Error("Couldn't load display lib");
        _loader.closeGameLib();
        _game = _loader.getEntryPoint<game::IGameModule *>(handle, "entryPointGame");
        if (_game == nullptr)
            throw Error("Couldn't get entry point");
        _loader.setGame(handle);
    }

    void Core::testLib(const std::string pathToLib)
    {
        game::IGameModule *testGame = nullptr;
        display::IDisplayModule *testDisplay = nullptr;
        void *handle = _loader.loadLib(pathToLib);
        if (!handle)
            return;
        if ((testGame = _loader.getEntryPoint<game::IGameModule *>(handle, "entryPointGame")) != nullptr) {
            delete testGame;
            dlclose(handle);
            _gameLibs.push_back(pathToLib);
            return;
        }
        if ((testDisplay = _loader.getEntryPoint<display::IDisplayModule *>(handle, "entryPointDisplay")) != nullptr) {
            delete testDisplay;
            dlclose(handle);
            _graphicLibs.push_back(pathToLib);
            return;
        }
    }

    void Core::setListLibs()
    {
        for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
            std::string path_str = std::string(entry.path().c_str());
            if (path_str.compare(0, 7, "arcade_"))
                testLib(path_str);
        }
    }

    void Core::sigHandler(int signum)
    {
        if (signum == 2)
            Core::_loop = false;
    }

    void Core::mainLoop(const std::string displayLib)
    {
        setGameModule(std::string("lib/arcade_menu.so"));
        setListLibs();
        setDisplayModule(displayLib);
        _game->init();
        _display->init(display::Vector2i{1920, 1080});
        std::signal(SIGINT, sigHandler);
        while (_loop) {
            if (_display->isButtonPressed(display::F1)) {
                _indexGraphicLibs--;
                _indexGraphicLibs = (_indexGraphicLibs < 0) ? 0 : _indexGraphicLibs;
                _display->close();
                setDisplayModule(_graphicLibs[_indexGraphicLibs % _graphicLibs.size()]);
                _display->init(display::Vector2i{1920, 1080});
                continue;
            }
            if (_display->isButtonPressed(display::F2)) {
                _indexGraphicLibs++;
                _display->close();
                setDisplayModule(_graphicLibs[_indexGraphicLibs % _graphicLibs.size()]);
                _display->init(display::Vector2i{1920, 1080});
                continue;
            }
            if (_display->isButtonPressed(display::F7))
                _loop = false;
            _display->clearWindow(display::BLACK);
            _display->handleEvents();
            _game->update(_display);
            _display->render();
        }
        _display->close();
        _game->stop();
        _loader.closeGameLib();
        _loader.closeGraphicLib();
    }

}
