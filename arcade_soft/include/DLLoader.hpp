/*
** EPITECH PROJECT, 2023
** DLLoader
** File description:
** The class can open and manipulate a dynamic library.
*/

#pragma once

#include <dlfcn.h>
#include <string>
#include <memory>

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
        void Load(std::string lib);
        template <typename T>
        std::shared_ptr<T> getInstance(std::string symbol)
        {
            void *sym;
            std::shared_ptr<T> (*func)();
            char *error;

            if (_handle == NULL)
                throw BadLibrary("Library not loaded");
            sym = dlsym(_handle, symbol.c_str());
            if ((error = dlerror()) != NULL)
                throw BadLibrary(error);
            func = reinterpret_cast<std::shared_ptr<T> (*)()>(sym);
            return (func());
        }
        ~DLLoader();

    private:
        void *_handle;
    };
}
