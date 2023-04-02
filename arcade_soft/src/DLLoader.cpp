/*
** EPITECH PROJECT, 2023
** DLLoader
** File description:
** The file contains all the methods of the class DLLoader.
*/

#include "DLLoader.hpp"

Arcade::DLLoader::BadLibrary::BadLibrary(std::string msg) : _msg(msg)
{
}

const char *Arcade::DLLoader::BadLibrary::what()
{
    return (_msg.c_str());
}

Arcade::DLLoader::DLLoader(std::string lib) : _handle(nullptr)
{
    char *error;

    if (lib.compare("") == 0){
        _handle = dlopen(lib.c_str(), RTLD_LAZY);
        if ((error = dlerror()) != NULL)
            throw BadLibrary(error);
    }
}

void Arcade::DLLoader::Load(std::string lib)
{
    char *error;

    if (_handle != nullptr)
        dlclose(_handle);
    _handle = dlopen(lib.c_str(), RTLD_LAZY);
    if ((error = dlerror()) != NULL)
        throw BadLibrary(error);
}

Arcade::DLLoader::~DLLoader()
{
    if (_handle != nullptr)
        dlclose(_handle);
}
