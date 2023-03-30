/*
** EPITECH PROJECT, 2023
** snake
** File description:
** main
*/

#include "snake.hpp"

int main()
{
    std::vector <int> vect = loadMap();
    std::cout << vect.size() << std::endl;
    return (0);
}
