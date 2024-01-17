#pragma once

#include <iostream>
#include <string>
#include <random>
#include <cassert>


// Define Point to store 2D coordinates
struct Point{
    int x;
    int y;
};

// Define == operator for Point struct to ease unit testing
bool operator==(const Point& p1, const Point& p2);

// Define != operator for Point struct to ease unit testing
bool operator!=(const Point& p1, const Point& p2);

// Define * operator to scale point
Point operator*(const Point& point, const int multiplier);

// Direction enum for better clarity
enum Direction{
    DIRECTION_UP,
    DIRECTION_RIGHT,
    DIRECTION_DOWN,
    DIRECTION_LEFT
};

// Define ++ (postfix) operator for Direction to ease changes in direction logic
Direction operator++(Direction& direction, int);

// Define -- (postfix) operator for Direction to ease changes in direction logic
Direction operator--(Direction& direction, int);

// Action enum for better clarity
enum Action{
    ACTION_LEFT,
    ACTION_FORWARD,
    ACTION_RIGHT,
};

// Difficolty enum for better clarity
enum Difficulty{
    DIFFICULTY_EASY,
    DIFFICULTY_INTERMEDIATE,
    DIFFICULTY_HARD
};

// Generate random Point in range [0, width]x[0, height]
Point get_random_point(const int n_cells_width, const int n_cells_height);

