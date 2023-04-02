/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Instruction
*/

#pragma once

#include <string>

typedef enum e_instruction_id {
    INST_FILL,
    INST_DRAW_TILE,
    INST_DRAW_TEXT,
    INST_PLAY_SOUND,
    INST_TOTAL
} t_instruction_id;

class IInstruction {
public:
    virtual ~IInstruction() = default;

    virtual int getId(void) const = 0;
};

class InstFill: public IInstruction {
public:
    int getId(void) const {return (INST_FILL);}
protected:
    int _color;
};

class InstDrawTile: public IInstruction {
public:
    InstDrawTile(int x, int y, int textureId) : _x(x), _y(y), _textureId(textureId) {}
    int getId(void) const {return (INST_DRAW_TILE);}
protected:
    int _x;
    int _y;
    int _textureId;
};

class InstDrawText: public IInstruction {
public:
    int getId(void) const {return (INST_DRAW_TEXT);}
protected:
    int _color;
    int _x;
    int _y;
    std::string _text;
};

class InstPlaySound: public IInstruction {
public:
    int getId(void) const {return (INST_PLAY_SOUND);}
protected:
    std::string _audioPath;
};
