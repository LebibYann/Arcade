/*
** EPITECH PROJECT, 2023
** DLLoader
** File description:
** The class can open and manipulate a dynamic library.
*/

#pragma once

#include <dlfcn.h>
#include <string>
#include <functional>
#include <memory>
#include <iostream>
#include "IGame.hpp"
#include "IGraphics.hpp"

namespace Arcade
{
    class DLLoader
    {
    public:
        class BadLibrary : public std::exception
        {
        public:
            BadLibrary(std::string msg);
            const char *what();

        private:
            const std::string _msg;
        };

        DLLoader(std::string lib = "");
        void Load(const std::string &lib);
        /**
         ** @brief Verify if a lib is usable by the core without throwing error.
         **
         ** @param lib the name of the library to check
         ** @return 0 if the lib not valid,
         ** 1 if it's a game and 2 if it's graphic lib.
         */
        int checkLibIntegrity(const std::string &lib);
        template <typename T>
        std::shared_ptr<T> getInstance(std::string symbol)
        {
            void *sym;
            std::shared_ptr<T> (*func)();
            char *error;

            if (_handle == nullptr)
                throw BadLibrary("Library not loaded");
            sym = dlsym(_handle, symbol.c_str());
            if ((error = dlerror()) != NULL)
                throw BadLibrary(error);
            if ((func = reinterpret_cast<std::shared_ptr<T> (*)()>(sym)) == NULL)
                throw BadLibrary("Unable to cast the entry point.");
            return (func());
        }
        void unLoad(void);
        ~DLLoader();
    private:
        void *_handle = NULL;
    };
}
