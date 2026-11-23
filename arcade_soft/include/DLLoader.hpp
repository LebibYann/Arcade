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
            const char *what() const noexcept override;

        private:
            const std::string _msg;
        };

        DLLoader(const std::string &lib = "");
        DLLoader(const DLLoader &) = delete;
        DLLoader &operator=(const DLLoader &) = delete;
        void Load(const std::string &lib);
        /**
         ** @brief Verify if a lib is usable by the core without throwing error.
         **
         ** @param lib the name of the library to check
         ** @return 0 if the lib not valid,
         ** 1 if it's a game and 2 if it's graphic lib.
         */
        int checkLibIntegrity(const std::string &lib);
        /**
         ** @brief Call the library entry point and take ownership of the
         ** instance it returns.
         ** The instance must be released before the library is unloaded,
         ** since its destructor lives in the library.
         */
        template <typename T>
        std::shared_ptr<T> getInstance(const std::string &symbol)
        {
            T *(*func)();
            T *instance;

            if (_handle == nullptr)
                throw BadLibrary("Library not loaded");
            dlerror();
            func = reinterpret_cast<T *(*)()>(dlsym(_handle, symbol.c_str()));
            if (const char *error = dlerror())
                throw BadLibrary(error);
            if (func == nullptr)
                throw BadLibrary("The entry point " + symbol + " is null.");
            if ((instance = func()) == nullptr)
                throw BadLibrary("The entry point " + symbol + " returned null.");
            return (std::shared_ptr<T>(instance));
        }
        void unLoad(void);
        ~DLLoader();
    private:
        void *_handle = NULL;
    };
}
