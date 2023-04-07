/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Core.hpp
*/

#include "ICore.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"
#include "Loader.hpp"
#include <list>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <vector>

namespace arcade {
    class Core : public ICore {
        public:
            Core();
            ~Core();
            void mainLoop(const std::string displayLib) override;

            void setFramerate(int framerate) override;
            int getFramerate() const override;
            void setScore(int score) override;
            int getScore() const override;
            std::string getPlayerName() const override;
            void setPlayerName(std::string name) override;


            static void sigHandler(int signum);
        private:
            void setDisplayModule(const std::string pathToLib) override;
            void setGameModule(const std::string pathToLib) override;
            void setListLibs(void);
            void testLib(const std::string pathToLib);

            bool handleEvents(void);
        public:
            static bool _loop;
        private:
            display::IDisplayModule *_display;
            game::IGameModule *_game;
            std::vector<std::string> _graphicLibs;
            int _indexGraphicLibs;
            std::vector<std::string> _gameLibs;
            int _indexGameLibs;

            Loader _loader;

            int _framerate;
            int _score;
            std::string _playerName;
    };

}
