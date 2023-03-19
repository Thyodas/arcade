/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** snake.hpp
*/

#include "IGameModule.hpp"
#include "../../Objects/Rectangle/Rectangle.hpp"

class Snake : public IGameModule {
    public:
        Snake() {};
        ~Snake() {};
        void update(std::unique_ptr<IDisplayModule> &display) override {};
};