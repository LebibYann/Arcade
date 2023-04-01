/*
** EPITECH PROJECT, 2023
** snake
** File description:
** game
*/

#include "../include/snake.hpp"

void moveHandler(t_snake_data *game, std::vector<bool> inputs)
{
    if (inputs[UP] == true && game->snake.direction != DOWN)
        game->snake.direction = UP;
    else if (inputs[DOWN] == true && game->snake.direction != UP)
        game->snake.direction = DOWN;
    else if (inputs[LEFT] == true && game->snake.direction != RIGHT)
        game->snake.direction = LEFT;
    else if (inputs[RIGHT] == true && game->snake.direction != LEFT)
        game->snake.direction = RIGHT;
}

int get_next_tile(t_snake_data *game)
{
    if (game->snake.direction == UP)
        return (game->map[game->snake.headPos[1] - 1][game->snake.headPos[0]]);
    else if (game->snake.direction == DOWN)
        return (game->map[game->snake.headPos[1] + 1][game->snake.headPos[0]]);
    else if (game->snake.direction == LEFT)
        return (game->map[game->snake.headPos[1]][game->snake.headPos[0] - 1]);
    else if (game->snake.direction == RIGHT)
        return (game->map[game->snake.headPos[1]][game->snake.headPos[0] + 1]);
    return (1);
}

int collisionHandler(t_snake_data *game)
{
    int next_tile = get_next_tile(game);

    if (next_tile == WALL)
        return (0);
    else if (next_tile == SNAKE_BODY)
        return (0);
    else if (next_tile == FOOD) {
        game->snake.size += 1;
        game->score += 1;
        return (2);
    }
    return (1);
}

void move_snake(t_snake_data *game, int collision)
{
    if (collision == 0)
        return;
    if (game->snake.direction == UP) {
        game->map[game->snake.headPos[1] - 1][game->snake.headPos[0]] = SNAKE_HEAD;
        game->map[game->snake.headPos[1]][game->snake.headPos[0]] = SNAKE_BODY;
        game->snake.headPos[1] -= 1;
    }
    else if (game->snake.direction == DOWN) {
        game->map[game->snake.headPos[1] + 1][game->snake.headPos[0]] = SNAKE_HEAD;
        game->map[game->snake.headPos[1]][game->snake.headPos[0]] = SNAKE_BODY;
        game->snake.headPos[1] += 1;
    }
    else if (game->snake.direction == LEFT) {
        game->map[game->snake.headPos[1]][game->snake.headPos[0] - 1] = SNAKE_HEAD;
        game->map[game->snake.headPos[1]][game->snake.headPos[0]] = SNAKE_BODY;
        game->snake.headPos[0] -= 1;
    }
    else if (game->snake.direction == RIGHT) {
        game->map[game->snake.headPos[1]][game->snake.headPos[0] + 1] = SNAKE_HEAD;
        game->map[game->snake.headPos[1]][game->snake.headPos[0]] = SNAKE_BODY;
        game->snake.headPos[0] += 1;
    }
    game->snake.body.insert(game->snake.body.begin(), game->snake.headPos);
    if (collision != 2) {
        game->map[game->snake.body.back()[1]][game->snake.body.back()[0]] = GROUND;
        game->snake.body.pop_back();
    }
}

std::vector <IInstruction> computeGame(t_snake_data *game, std::vector<bool> inputs)
{
    std::vector <IInstruction> instructions;
    int collision = -1;

    if (collision != 0) {
        moveHandler(game, inputs);
        collision = collisionHandler(game);
        move_snake(game, collision);
    }
    return (instructions);
}