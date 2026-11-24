/*
** EPITECH PROJECT, 2023
** B-OOP-400-PAR-4-1-arcade-yann.lebib
** File description:
** Tests of Snake and Nibbler through the IGame interface
*/

#include "../Test.hpp"
#include "DLLoader.hpp"
#include "GridSnake.hpp"

#include <map>

typedef std::vector<std::shared_ptr<IInstruction>> Instructions;

// Keeps the library loaded for as long as the game exists
class LoadedGame {
public:
    explicit LoadedGame(const std::string &path) : _loader(path)
    {
        game = _loader.getInstance<Arcade::IGame>("entry_point");
    }
    ~LoadedGame() { game.reset(); }

    /**
     ** @brief Play one move: the games move once every 5 frames, on the
     ** first frame of the cycle.
     */
    Instructions step(int button = -1)
    {
        std::vector<bool> buttons(Arcade::TOTAL_INPUT, false);
        Instructions out;

        if (button >= 0)
            buttons[button] = true;
        out = game->computeFrame(buttons);
        std::fill(buttons.begin(), buttons.end(), false);
        for (int i = 0; i < 4; ++i)
            game->computeFrame(buttons);
        return (out);
    }

    std::shared_ptr<Arcade::IGame> game;

private:
    Arcade::DLLoader _loader;
};

static std::map<int, int> countTiles(const Instructions &frame)
{
    std::map<int, int> count;

    for (const auto &instr : frame)
        if (auto tile = std::dynamic_pointer_cast<InstDrawTile>(instr))
            count[tile->get_texture()] += 1;
    return (count);
}

static GridSnake::Cell findTile(const Instructions &frame, int id)
{
    for (const auto &instr : frame)
        if (auto tile = std::dynamic_pointer_cast<InstDrawTile>(instr))
            if (tile->get_texture() == id)
                return {tile->get_x(), tile->get_y()};
    return {-1, -1};
}

static bool hasText(const Instructions &frame, const std::string &text)
{
    for (const auto &instr : frame)
        if (auto drawText = std::dynamic_pointer_cast<InstDrawText>(instr))
            if (drawText->get_text().find(text) != std::string::npos)
                return (true);
    return (false);
}

TEST(snake_starts_with_a_three_cell_snake_and_an_apple)
{
    LoadedGame snake("./lib/arcade_snake.so");
    std::map<int, int> tiles = countTiles(snake.step());

    CHECK(snake.game->getWindowSize() == std::vector<int>({10, 10}));
    CHECK_EQ(snake.game->getTilesConfig().size(), (std::size_t)5);
    CHECK_EQ(tiles[GridSnake::HEAD], 1);
    // The first move can eat the apple if it was placed just above the head
    CHECK_EQ(tiles[GridSnake::BODY], 2 + (int)snake.game->getScore());
    CHECK_EQ(tiles[GridSnake::FOOD], 1);
    CHECK_EQ(tiles[GridSnake::WALL], 36);
}

TEST(snake_turns_with_the_arrow_buttons)
{
    LoadedGame snake("./lib/arcade_snake.so");
    GridSnake::Cell head = findTile(snake.step(Arcade::LEFT_ARROW), GridSnake::HEAD);

    // It starts at (4, 4) going up: turning left moves it to (3, 4)
    CHECK_EQ(head.x, 3);
    CHECK_EQ(head.y, 4);
}

TEST(snake_cannot_turn_back_onto_itself)
{
    LoadedGame snake("./lib/arcade_snake.so");
    GridSnake::Cell head = findTile(snake.step(Arcade::DOWN_ARROW), GridSnake::HEAD);

    CHECK_EQ(head.x, 4);
    CHECK_EQ(head.y, 3);
}

TEST(snake_dies_against_a_wall)
{
    LoadedGame snake("./lib/arcade_snake.so");
    bool over = false;

    for (int i = 0; i < 20 && !over; ++i)
        over = hasText(snake.step(), "Game over");
    // An apple on the way can be eaten before hitting the wall
    CHECK(over);
}

TEST(snake_scores_when_eating_an_apple)
{
    LoadedGame snake("./lib/arcade_snake.so");
    Instructions frame = snake.step();
    int direction = Arcade::UP_ARROW;

    for (int i = 0; i < 100 && snake.game->getScore() == 0; ++i) {
        GridSnake::Cell head = findTile(frame, GridSnake::HEAD);
        GridSnake::Cell food = findTile(frame, GridSnake::FOOD);
        int wanted = (food.x < head.x) ? Arcade::LEFT_ARROW :
            (food.x > head.x) ? Arcade::RIGHT_ARROW :
            (food.y < head.y) ? Arcade::UP_ARROW : Arcade::DOWN_ARROW;

        // Turning back is ignored, so go around first
        if ((wanted == Arcade::UP_ARROW && direction == Arcade::DOWN_ARROW) ||
            (wanted == Arcade::DOWN_ARROW && direction == Arcade::UP_ARROW))
            wanted = (head.x > 1) ? Arcade::LEFT_ARROW : Arcade::RIGHT_ARROW;
        if ((wanted == Arcade::LEFT_ARROW && direction == Arcade::RIGHT_ARROW) ||
            (wanted == Arcade::RIGHT_ARROW && direction == Arcade::LEFT_ARROW))
            wanted = (head.y > 1) ? Arcade::UP_ARROW : Arcade::DOWN_ARROW;
        direction = wanted;
        frame = snake.step(wanted);
    }
    CHECK_EQ(snake.game->getScore(), (std::size_t)1);
    CHECK_EQ(countTiles(frame)[GridSnake::BODY], 3);
}

TEST(nibbler_shows_its_level_and_timer)
{
    LoadedGame nibbler("./lib/arcade_nibbler.so");
    Instructions frame = nibbler.step();

    // One more row than the maze for the timer
    CHECK(nibbler.game->getWindowSize() == std::vector<int>({19, 20}));
    CHECK(hasText(frame, "Level 1"));
    CHECK(hasText(frame, "Time 998"));
    CHECK_EQ(countTiles(frame)[GridSnake::BODY], 2);
}

TEST(nibbler_stops_against_walls_without_dying)
{
    LoadedGame nibbler("./lib/arcade_nibbler.so");
    Instructions frame;

    // It starts at (10, 17) going right, and the wall is at x = 18
    for (int i = 0; i < 15; ++i)
        frame = nibbler.step();
    CHECK_EQ(findTile(frame, GridSnake::HEAD).x, 17);
    CHECK(!hasText(frame, "Game over"));
    CHECK(hasText(frame, "Time 984"));
}
