/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** Core.hpp
*/

#include "ICore.hpp"
#include "IDisplayModule.hpp"
#include "IGameModule.hpp"

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

        void setDisplayModule(const std::string pathToLib) override;
        void setGameModule(const std::string pathToLib) override;
    private:
        std::unique_ptr<IDisplayModule> _display;
        std::unique_ptr<IGameModule> _game;

        int _framerate;
        int _score;
        std::string _playerName;
};
