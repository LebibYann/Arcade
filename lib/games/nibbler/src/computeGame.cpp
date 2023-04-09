/*
** EPITECH PROJECT, 2023
** snake
** File description:
** game
*/

#include "nibbler.hpp"

int reduceTime(t_nibbler_data *game)
{
    (void) game;
    return (1);
}

void softReset(t_nibbler_data *game)
{
    while (game->snake.body.size() > 0)
        game->snake.body.pop_back();
    initSnake(game);
    game->level += 1;
    if ((size_t) game->level > game->maps.size())
        game->level = 1;
    game->map = game->maps[game->level - 1];
    game->score += game->timer;
    game->timer = 999;
    game->lastEaten = 0;
}

void isFoodLeft(t_nibbler_data *game)
{
    for (size_t i = 0; i < game->map.size(); i++) {
        for (size_t j = 0; j < game->map[i].size(); j++) {
            if (game->map[i][j] == FOOD)
                return;
        }
    }
    softReset(game);
}

std::vector<std::shared_ptr<IInstruction>> getMapInstructions(t_nibbler_data *game)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;

    for (size_t i = 0; i < game->map.size(); i++) {
        for (size_t j = 0; j < game->map[i].size(); j++) {
            if (game->map[i][j] == GROUND)
                instructions.push_back(std::make_shared<InstDrawTile>((int) j, (int) i, 0));
            else if (game->map[i][j] == WALL)
                instructions.push_back(std::make_shared<InstDrawTile>((int) j, (int) i, 1));
            else if (game->map[i][j] == SNAKE_HEAD)
                instructions.push_back(std::make_shared<InstDrawTile>((int) j, (int) i, 2));
            else if (game->map[i][j] == SNAKE_BODY)
                instructions.push_back(std::make_shared<InstDrawTile>((int) j, (int) i, 3));
            else if (game->map[i][j] == FOOD)
                instructions.push_back(std::make_shared<InstDrawTile>((int) j, (int) i, 4));
        }
    }
    return (instructions);
}

std::vector<std::shared_ptr<IInstruction>> getInstructions(t_nibbler_data *game)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;

    if (game->gameOver == false)
        instructions = getMapInstructions(game);
    else {
        if (game->snake.body.size() > 0)
            instructions = getMapInstructions(game);
        else
            instructions.push_back(std::make_shared<InstDrawText>(5, 5, WHITE, "Game over !"));
    }
    return (instructions);
}

std::vector<std::shared_ptr<IInstruction>> computeGame(t_nibbler_data *game, std::vector<bool> inputs)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;
    int collision = -1;

    if (game == nullptr)
        game = loadConfig();
    if (game->timer > 0 && collision != 1) {
        moveHandler(game, inputs);
        collision = collisionHandler(game);
        if (!game->gameOver) {
            move_snake(game, collision);
            game->timer -= reduceTime(game);
            game->lastEaten += 1;
            isFoodLeft(game);
        }
        if (collision == 3 || game->timer <= 0)
            game->gameOver = true;
        if (game->gameOver && game->snake.body.size() > 0) {
            game->map[game->snake.body.back()[1]][game->snake.body.back()[0]] = GROUND;
            game->snake.body.pop_back();
        }
    }
    instructions = getInstructions(game);
    return (instructions);
}
