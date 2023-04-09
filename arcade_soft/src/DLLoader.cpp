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

void Arcade::DLLoader::Load(const std::string &lib)
{
    char *error;

    if (_handle != nullptr)
        dlclose(_handle);
    _handle = dlopen(lib.c_str(), RTLD_LAZY);
    if ((error = dlerror()) != NULL)
        throw BadLibrary(error);
}

void Arcade::DLLoader::unLoad(void)
{
    if (_handle != nullptr){
        dlclose(_handle);
        _handle = nullptr;
    }
}

Arcade::DLLoader::~DLLoader()
{
    this->unLoad();
}

int Arcade::DLLoader::checkLibIntegrity(const std::string &lib)
{
    int state = 0;
    void *sym;
    void *handle = dlopen(lib.c_str(), RTLD_LAZY);
    char *error;
    int (*typeFunc)();

    if (dlerror() != NULL)
        return (state);
    sym = dlsym(handle, "get_type");
    if ((error = dlerror()) != NULL)
        return (state);
    typeFunc = reinterpret_cast<int (*)()>(sym);
    state = typeFunc() + 1;
    dlclose(handle);
    return ((state == 1 || state == 2) * state);
}
