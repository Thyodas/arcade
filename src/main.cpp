/*
** EPITECH PROJECT, 2022
** B-OOP-400-STG-4-1-arcade-marie.giacomel
** File description:
** main.cpp
*/

#include "Core/Core.hpp"

int main(int argc, char **argv)
{
    arcade::Core core;
    try {
        if (argc != 2)
            throw arcade::Error("Wrong number of arguments.");
        core.mainLoop(std::string(argv[1]));
        return 0;
    } catch (const arcade::Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}