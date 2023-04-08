/**
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** externCFunction
** \file externCFunction.hpp
*/

#pragma once

#include <memory>

#include "IGraphics.hpp"

/**
 ** @brief Do not forget to add extern "C" before the function itself.
 ** Since this function is made for both IGraphics and IGame you must put
 ** the correct type between the <>.
 **
 */
extern "C" std::shared_ptr<Arcade::IGraphics> entry_point();

/**
 ** @brief Do not forget to add extern "C" before the function itself.
 ** This function must return 0 if it's a game library and
 ** 1 if it's a graphical library.
 **
 */
extern "C" int get_type(void);
