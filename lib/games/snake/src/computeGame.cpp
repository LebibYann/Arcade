/*
** EPITECH PROJECT, 2023
** snake
** File description:
** game
*/

#include "snake.hpp"

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
        return (game->map[game->snake.headPos[1] - 1]
        [game->snake.headPos[0]]);
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

void addFood(t_snake_data *game)
{
    bool isFood = false;
    bool isGround = false;

    for (size_t i = 0; i < game->map.size() && isFood == false; i++) {
        for (size_t j = 0; j < game->map[i].size(); j++) {
            if (game->map[i][j] == FOOD)
                isFood = true;
        }
    }
    if (isFood == false) {
        for (size_t i = 0; i < game->map.size() && isGround == false; i++) {
            for (size_t j = 0; j < game->map[i].size(); j++) {
                if (game->map[i][j] == GROUND)
                    isGround = true;
            }
        }
        int x = rand() % game->map[0].size();
        int y = rand() % game->map.size();
        while (game->map[y][x] != GROUND) {
            x = rand() % game->map[0].size();
            y = rand() % game->map.size();
        }
        game->map[y][x] = FOOD;
    }
}

std::vector<std::shared_ptr<IInstruction>> getMapInstructions(t_snake_data *game)
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

std::vector<std::shared_ptr<IInstruction>> getInstructions(t_snake_data *game)
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

std::vector<std::shared_ptr<IInstruction>> computeGame(t_snake_data *game, std::vector<bool> inputs)
{
    std::vector<std::shared_ptr<IInstruction>> instructions;
    int collision = -1;

    if (game == nullptr)
        game = loadConfig();
    if (collision != 0) {
        moveHandler(game, inputs);
        collision = collisionHandler(game);
        move_snake(game, collision);
        addFood(game);
        if (collision == 0)
            game->gameOver = true;
        if (game->gameOver && game->snake.body.size() > 0){
            game->map[game->snake.body.back()[1]][game->snake.body.back()[0]] = GROUND;
            game->snake.body.pop_back();
        }
    }
    instructions = getInstructions(game);
    return (instructions);
}
