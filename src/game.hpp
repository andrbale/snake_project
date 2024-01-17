#pragma once

#include <iostream>
#include "snake.hpp"
#include "../include/raylib.h"


class Game{

    Snake snake;
    Point food;

    bool game_over;
    int score;

    // Window size variables
    int n_cells_height; 
    int n_cells_width;
    int cell_size;

public:

    // Blank constructor
    Game();

    // Main constructor: spawn 2cells snake in the middle of the game field
    Game(int n_cells_width, int n_cells_height, int cell_size);

    // Perform a game step
    void step(const Action& action);

    // Draw grid in the grafic with cells edges length = cell_size
    void draw_grid();

    // Draw current state of the game
    void draw_game_state();

    // Check if game over
    bool is_game_over();

    // Get score
    int get_score();

};

// Initialize game. For now difficuly changes and walls are not implemented
Game init_game(const Difficulty& difficulty = DIFFICULTY_EASY, const bool wall_presence = false);

// Take user action, designed to be used in a thread
// loop until stop_loop is set to true in main while getting user input and change action if needed (default forward)
void get_user_action(Action& action, const bool& stop_loop);

// Get user difficulty
Difficulty get_user_difficulty();