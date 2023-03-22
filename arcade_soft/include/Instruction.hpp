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
    virtual void setId(int id) = 0;
};

class AInstruction: public IInstruction {
public:
    int getId(void) const {return (this->_id);}
    void setId(int id) {this->_id = id;}
protected:
    int _id;
};

class InstFill: public AInstruction {
protected:
    int _color;
};

class InstDrawTile: public AInstruction {
protected:
    int _x;
    int _y;
    int _textureId;
};

class InstDrawText: public AInstruction {
protected:
    int _color;
    int _x;
    int _y;
    std::string _text;
};

class InstPlaySound: public AInstruction {
protected:
    std::string _audioPath;
};
