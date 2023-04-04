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
    InstFill(int color) {_color = color;};
    int getId(void) const {return (INST_FILL);};
    int get_color(void) const {return _color;};
protected:
    int _color;
};

class InstDrawTile: public IInstruction {
public:
    InstDrawTile(int x, int y, int textureId) {_x = x; _y = y; _textureId = textureId;};
    int getId(void) const {return (INST_DRAW_TILE);};
    int get_x(void) const {return _x;};
    int get_y(void) const {return _y;};
    int get_texture(void) const {return _textureId;};
protected:
    int _x;
    int _y;
    int _textureId;
};

class InstDrawText: public IInstruction {
public:
    InstDrawText(int x, int y, int color, std::string text) {_x = x; _y = y; _color = color; _text = text;};
    int getId(void) const {return (INST_DRAW_TEXT);};
    int get_x(void) const {return _x;};
    int get_y(void) const {return _y;};
    int get_color(void) const {return _color;};
    std::string get_text(void) const {return _text;};
protected:
    int _color;
    int _x;
    int _y;
    std::string _text;
};

class InstPlaySound: public IInstruction {
public:
    InstPlaySound(std::string audioPath) {_audioPath = audioPath;};
    int getId(void) const {return (INST_PLAY_SOUND);};
    std::string get_audio(void) const {return _audioPath;};
protected:
    std::string _audioPath;
};
