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
        _loader.closeGraphicLib();
        _display = _loader.getEntryPoint<display::IDisplayModule>(handle);
        _loader.setDisplay(handle);
    }

    void Core::setGameModule(const std::string pathToLib)
    {
        void *handle = _loader.loadLib(pathToLib);
        _loader.closeGameLib();
        _game = _loader.getEntryPoint<game::IGameModule>(handle);
        _loader.setGame(handle);
    }

    void Core::sigHandler(int signum)
    {
        if (signum == 2)
            Core::_loop = false;
    }

    void Core::mainLoop(const std::string displayLib)
    {
        int index = 0;
        std::vector<std::string> graphicLibs = {"lib/arcade_sfml.so",
                                            "lib/arcade_ncurses.so"};
        setGameModule(std::string("lib/arcade_menu.so"));
        setDisplayModule(displayLib);
        _game->init();
        std::signal(SIGINT, sigHandler);
        while (_loop) {
            if (_display->isButtonPressed(display::F1)) {
                index--;
                index = (index < 0) ? 0 : index;
                _display->close();
                setDisplayModule(graphicLibs[index % graphicLibs.size()]);
                continue;
            }
            if (_display->isButtonPressed(display::F2)) {
                index++;
                _display->close();
                setDisplayModule(graphicLibs[index % graphicLibs.size()]);
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




