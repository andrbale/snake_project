#include "utils.hpp"

// Define == operator for Point struct to ease unit testing
bool operator==(const Point& p1, const Point& p2){
    return p1.x == p2.x && p1.y == p2.y;
}

// Define != operator for Point struct to ease unit testing
bool operator!=(const Point& p1, const Point& p2){
    return !(p1.x == p2.x && p1.y == p2.y);
}

// Define * operator to scale point
Point operator*(const Point& point, const int multiplier){
    return {point.x*multiplier, point.y*multiplier};
}

// Define ++ (postfix) operator for Direction to ease changes in direction logic
Direction operator++(Direction& direction, int) {
    Direction tmp = direction;
    direction = static_cast<Direction>((static_cast<int>(direction) + 1 + 4) % 4);
    return tmp;
}

// Define -- (postfix) operator for Direction to ease changes in direction logic
Direction operator--(Direction& direction, int) {
    Direction tmp = direction;
    direction = static_cast<Direction>((static_cast<int>(direction) - 1 + 4) % 4);
    return tmp;
}

// Generate random Point in range [0, n_cells_width)x[0, n_cells_height)
Point get_random_point(const int n_cells_width, const int n_cells_height){
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribution_x(0, n_cells_width-1); // Uniform distribution on x-axis
    std::uniform_int_distribution<> distribution_y(0, n_cells_height-1); // Uniform distribution on y-axis

    Point random_point = {distribution_x(gen), distribution_y(gen)};

    return random_point;
}

