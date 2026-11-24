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

const char *Arcade::DLLoader::BadLibrary::what() const noexcept
{
    return (_msg.c_str());
}

Arcade::DLLoader::DLLoader(const std::string &lib) : _handle(nullptr)
{
    if (!lib.empty())
        this->Load(lib);
}

void Arcade::DLLoader::Load(const std::string &lib)
{
    this->unLoad();
    _handle = dlopen(lib.c_str(), RTLD_LAZY);
    if (_handle == nullptr) {
        const char *error = dlerror();
        throw BadLibrary(error ? error : "Unable to open " + lib);
    }
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
    void *handle = dlopen(lib.c_str(), RTLD_LAZY);
    int (*typeFunc)();

    if (handle == nullptr)
        return (0);
    dlerror();
    typeFunc = reinterpret_cast<int (*)()>(dlsym(handle, "get_type"));
    if (dlerror() == nullptr && typeFunc != nullptr &&
        dlsym(handle, "entry_point") != nullptr)
        state = typeFunc() + 1;
    dlclose(handle);
    return ((state == 1 || state == 2) ? state : 0);
}
