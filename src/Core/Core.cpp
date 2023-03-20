/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Core.cpp
*/

#include "Core.hpp"
#include "Loader.hpp"
#include <vector>

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
    char *error = NULL;
    std::shared_ptr<Loader> loader = Loader::getLoader();
    void *handle = loader->setGraphicLib(pathToLib);
    std::unique_ptr<IDisplayModule> (*ptr)(void) = (std::unique_ptr<IDisplayModule> (*)(void))dlsym(handle, "entryPointDisplay");
    if ((error = dlerror()) != NULL)
        throw Error(error);
    _display = ptr();
}

void Core::setGameModule(const std::string pathToLib)
{
    char *error = NULL;
    std::shared_ptr<Loader> loader = Loader::getLoader();
    void *handle = loader->setGameLib(pathToLib);
    std::unique_ptr<IGameModule> (*ptr)(void) = (std::unique_ptr<IGameModule> (*)(void))dlsym(handle, "entryPointGame");
    if ((error = dlerror()) != NULL)
        throw Error(error);
    _game = ptr();
}

void Core::mainLoop(const std::string displayLib)
{
    int index = 0;
    std::vector<std::string> graphicLibs = {"lib/arcade_sfml.so",
                                        "lib/arcade_ncurses.so"};
    setGameModule(std::string("lib/arcade_menu.so"));
    setDisplayModule(displayLib);
    _game->init();
    while (1) {
        if (_display->isButtonPressed(IDisplayModule::F1)) {
            index--;
            index = (index < 0) ? 0 : index;
            _display->close();
            setDisplayModule(graphicLibs[index]);
            continue;
        }
        if (_display->isButtonPressed(IDisplayModule::F2)) {
            index++;
            index = (index >= graphicLibs.size()) ? 0 : index;
            _display->close();
            setDisplayModule(graphicLibs[index]);
            continue;
        }
        _display->clearWindow(IDisplayModule::BLACK);
        _display->handleEvents();
        _game->update(_display);
        _display->render();
    }
}



