#pragma once

#include <iostream>
#include <deque>

#include "utils.hpp"
#include "../include/raylib.h"


class Snake{

    std::deque<Point> body; // Use of the deque for inserting head and popping tail in O(1)
    Direction direction; // Current head direction (used to performe step)

public:

    // Blank constructor
    Snake();

    // Initialize snake with a 2-Points body given initial head and direction
    Snake(Point head, Direction direction);

    // Constructor to externally set body and direction. This constructor is used to ease unit testing of target functions
    Snake(std::deque<Point> body, Direction direction);

    // Check if head collides with body (true if yes)
    bool self_collision();

    // Check if target point is inside of snake (true if yes)
    bool point_to_body_collision(const Point& target);

    // Perform step by pushing the new head given current direction and checking for self collision (that would result in game over)
    void step(const Action& action, Point& food, int& score, bool& game_over, const int n_cells_width, const int n_cells_height);

    // Get head coordinates
    Point get_head();

    // Return next position of the head after a step.
    // Inputs: number of cells in horizontal and vertical dimensions
    Point get_next_head(const int n_cells_width, const int n_cells_height);

    // Get body (used for testing and debugging)
    std::deque<Point> get_body();

    // Get current direction
    Direction get_direction();

    // Update direction given an action
    void update_direction(const Action& action);

    // Draw snake
    void draw(const int cell_size);

};