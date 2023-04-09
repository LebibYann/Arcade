/**
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Instruction
** \file Instruction.hpp
*/

#pragma once

#include <string>

/**
 ** @brief This enum is used to recognize the different instructions
 ** at the interpretation time when they're all contained in a
 ** std::vector<std::shared_ptr<IInstruction>>.
 ** If the instruction id isn't in the range of this enum it will be ignored.
 **
 */
typedef enum e_instruction_id {
    INST_FILL, // Indicates that the instruction is made for fill drawing
    INST_DRAW_TILE, // Indicates that the instruction is made for tile drawing
    INST_DRAW_TEXT, // Indicates that the instruction is made for text drawing
    INST_PLAY_SOUND, // Not supported/ignored by the interpreter
    INST_TOTAL // Not an instruction onlya way to know the total number of instruction
} t_instruction_id;

/**
 ** @brief Generic class that helps to containing various class of instructions.
 **
 */
class IInstruction {
public:
    /**
     ** @brief Destroy the IInstruction object.
     **
     */
    virtual ~IInstruction() = default;
    /**
     ** @brief Get the instruction id to let interpretor decide what to do with.
     **
     ** @return int return the instruction id.
     */
    virtual int getId(void) const = 0;
};

/**
 ** @brief Use this instruction if you want to fill the background.
 **
 */
class InstFill: public IInstruction {
public:
    /**
     ** @brief Construct a new InstFill object
     **
     ** @param color A color based on the enum ArcadeColor.
     */
    InstFill(int color) {_color = color;};
    int getId(void) const {return (INST_FILL);};
    /**
     ** @brief Get the color id.
     **
     ** @return int A color based on the enum ArcadeColor.
     */
    int get_color(void) const {return _color;};
protected:
    int _color;
};

/**
 ** @brief Use this instruction if you want to place a tile.
 **
 */
class InstDrawTile: public IInstruction {
public:
    /**
     ** @brief Construct a new InstDrawTile object
     **
     ** @param x X position of the tile to draw.
     ** @param y Y position of the tile to draw.
     ** @param textureId The id must match with one of the
     ** t_tile_config.id recovered by the program
     ** when calling the IGame method: getTilesConfig
     */
    InstDrawTile(int x, int y, int textureId) {_x = x; _y = y; _textureId = textureId;};
    int getId(void) const {return (INST_DRAW_TILE);};
    /**
     ** @brief Get the X tiled position.
     **
     ** @return int X position of the tile to draw.
     */
    int get_x(void) const {return _x;};
    /**
     ** @brief Get the Y tiled position.
     **
     ** @return int Y position of the tile to draw.
     */
    int get_y(void) const {return _y;};
    /**
     ** @brief Gives you an id that you must match with one of t_tile_config.id
     ** set by the IGame method: getTilesConfig
     **
     ** @return int An existing t_tile_config.id for the game loaded.
     */
    int get_texture(void) const {return _textureId;};
protected:
    int _x;
    int _y;
    int _textureId;
};

/**
 ** @brief Use this instruction if you want to write text.
 **
 */
class InstDrawText: public IInstruction {
public:
    /**
     ** @brief Construct a new InstDrawText object.
     **
     ** @param x X position of the tile to draw.
     ** @param y Y position of the tile to draw.
     ** @param color A color based on the enum ArcadeColor.
     ** @param text The text you want the instruction gives to the interpretor.
     */
    InstDrawText(int x, int y, int color, std::string text) {_x = x; _y = y; _color = color; _text = text;};
    int getId(void) const {return (INST_DRAW_TEXT);};
    /**
     ** @brief Get the X tiled position.
     **
     ** @return int X position of the tile to draw.
     */
    int get_x(void) const {return _x;};
    /**
     ** @brief Get the Y tiled position.
     **
     ** @return int Y position of the tile to draw.
     */
    int get_y(void) const {return _y;};
    /**
     ** @brief Get the color id.
     **
     ** @return int A color based on the enum ArcadeColor.
     */
    int get_color(void) const {return _color;};
    std::string get_text(void) const {return _text;};
protected:
    int _color;
    int _x;
    int _y;
    std::string _text;
};

/**
 ** @brief An unsupported instruction that was supposed to let you play audio.
 **
 */
class InstPlaySound: public IInstruction {
public:
    InstPlaySound(std::string audioPath) {_audioPath = audioPath;};
    int getId(void) const {return (INST_PLAY_SOUND);};
    std::string get_audio(void) const {return _audioPath;};
protected:
    std::string _audioPath;
};
