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
 ** It returns a new instance allocated with new: Arcade::IGame * for a game
 ** library, Arcade::IGraphics * for a graphics library.
 ** The core takes ownership of it and deletes it before closing the library.
 ** A raw pointer is used because a C++ class such as std::shared_ptr
 ** cannot cross an extern "C" boundary safely.
 **
 */
extern "C" Arcade::IGraphics *entry_point();

/**
 ** @brief Do not forget to add extern "C" before the function itself.
 ** This function must return 0 if it's a game library and
 ** 1 if it's a graphical library.
 **
 */
extern "C" int get_type(void);
