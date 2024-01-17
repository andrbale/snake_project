#define CATCH_CONFIG_MAIN

#include <iostream>
#include <deque>
#include "../include/catch.hpp"
#include "../src/snake.hpp"
#include "../src/utils.hpp"


// Check that the snake is spawn (constructed) right using each direction (keep in mind that the point (0,0) is at top left)
TEST_CASE("Check snake spawn:", "[snake][spawn]"){

    // Initialize head coordinates and field
    int n_cells_width = 20;
    int n_cells_height = 10;
    Point head = {n_cells_width/2, n_cells_height/2};
    
    // Spawn 2section snake with the 4 possible directions and check if the snake is spawn as expected
    SECTION("Direction UP"){
        Snake snake(head, DIRECTION_UP);
        Point tail = {head.x, head.y+1};

        REQUIRE(snake.get_direction() == DIRECTION_UP);
        REQUIRE(snake.get_body().back() == head);
        REQUIRE(snake.get_body().front() == tail);
    }
    SECTION("Direction RIGHT"){
        Snake snake(head, DIRECTION_RIGHT);
        Point tail = {head.x-1, head.y};

        REQUIRE(snake.get_direction() == DIRECTION_RIGHT);
        REQUIRE(snake.get_body().back() == head);
        REQUIRE(snake.get_body().front() == tail);
    }
    SECTION("Direction DOWN"){
        Snake snake(head, DIRECTION_DOWN);
        Point tail = {head.x, head.y-1};

        REQUIRE(snake.get_direction() == DIRECTION_DOWN);
        REQUIRE(snake.get_body().back() == head);
        REQUIRE(snake.get_body().front() == tail);
    }
    SECTION("Direction LEFT"){
        Snake snake(head, DIRECTION_LEFT);
        Point tail = {head.x+1, head.y};

        REQUIRE(snake.get_direction() == DIRECTION_LEFT);
        REQUIRE(snake.get_body().back() == head);
        REQUIRE(snake.get_body().front() == tail);
    }

}

// Check self collision snake's member function and Point to body collision
TEST_CASE("Check snake self collision", "[snake][collision]"){

    // Initialize head coordinates and field
    int n_cells_width = 20;
    int n_cells_height = 10;
    Point head = {n_cells_width/2, n_cells_height/2};

    // Spawn 2section snake with the 4 possible directions and perform step with 3 possible actions
    SECTION("2 heads body self collision"){

        std::deque<Point> body = {head, head};
        Snake snake(body, DIRECTION_UP);

        REQUIRE(snake.self_collision() == true);
    }
    SECTION("head, tail and outside point point_to_body_collision"){
        
        Point tail = {head.x-1, head.y};
        
        Point outside_point = {0,0};

        std::deque<Point> body {};
        body.push_back(head);
        body.push_back(tail);

        Snake snake(body, DIRECTION_RIGHT);

        REQUIRE(snake.self_collision() == false);
        REQUIRE(snake.point_to_body_collision(head) == true);
        REQUIRE(snake.point_to_body_collision(tail) == true);
        REQUIRE(snake.point_to_body_collision(outside_point) == false);
    }
}

// Check snake update_direction() member function
TEST_CASE("Check snake update_direction()", "[snake][update_direction]"){

    // Initialize head coordinates and field
    int n_cells_width = 20;
    int n_cells_height = 10;
    Point head = {n_cells_width/2, n_cells_height/2};

    // Initialize snake with DIRECTION_UP
    Snake snake(head, DIRECTION_UP);

    // Check if snake update_direction() modifies the direction as expected
    snake.update_direction(ACTION_FORWARD);
    REQUIRE(snake.get_direction() == DIRECTION_UP);

    snake.update_direction(ACTION_LEFT);
    REQUIRE(snake.get_direction() == DIRECTION_LEFT);

    snake.update_direction(ACTION_LEFT);
    REQUIRE(snake.get_direction() == DIRECTION_DOWN);

    snake.update_direction(ACTION_FORWARD);
    REQUIRE(snake.get_direction() == DIRECTION_DOWN);

    snake.update_direction(ACTION_LEFT);
    REQUIRE(snake.get_direction() == DIRECTION_RIGHT);

    snake.update_direction(ACTION_RIGHT);
    REQUIRE(snake.get_direction() == DIRECTION_DOWN);

    snake.update_direction(ACTION_RIGHT);
    REQUIRE(snake.get_direction() == DIRECTION_LEFT);

    snake.update_direction(ACTION_RIGHT);
    REQUIRE(snake.get_direction() == DIRECTION_UP);

    snake.update_direction(ACTION_RIGHT);
    REQUIRE(snake.get_direction() == DIRECTION_RIGHT);
}

// Check snake step() in different scenarios and corner cases
TEST_CASE("Check snake step()", "[snake][step]"){

    // Initialize head coordinates and field
    int n_cells_width = 20;
    int n_cells_height = 10;

    // Normal step and Normal step eating food.
    SECTION("Normal step and Normal step eating food"){

        // Whis the following setup, the snake should eat the food at the second step going forward
        Point head = {n_cells_width/2, n_cells_height/2};
        Point tail = {head.x+1, head.y};
        Point food = {head.x-2, head.y};
        Point food_static = food;
        int score = 0;
        bool game_over = false;

        // Init snake default
        Snake snake(head, DIRECTION_LEFT);

        // 1st step
        snake.step(ACTION_FORWARD, food, score, game_over, n_cells_width, n_cells_height);
        
        // Ground truth body after 1st step
        head.x--;
        tail.x--;
        std::deque<Point> body_expected = {};
        body_expected.push_back(tail);
        body_expected.push_back(head);

        REQUIRE(score == 0);
        REQUIRE(game_over == false);
        REQUIRE(food == food_static);
        REQUIRE(snake.get_body() == body_expected);    

        // 2nd step
        snake.step(ACTION_FORWARD, food, score, game_over, n_cells_width, n_cells_height);  

        // Ground truth body after 2nd step
        head.x--;
        body_expected.push_back(head);
        

        REQUIRE(score == 1);
        REQUIRE(game_over == false);
        REQUIRE(food != food_static);
        REQUIRE(snake.get_body() == body_expected);  

    }
    // Step outside border and teleport to the other side (check each border)
    SECTION("Teleport to other side of the field"){
        
        // Initialize a 2 section snake at each border and in the border direction (step() forward would go outside of the field)
        Point head_border_up = {n_cells_width/2, 0};
        Snake snake_border_up(head_border_up, DIRECTION_UP);

        Point head_border_down = {n_cells_width/2, n_cells_height-1};
        Snake snake_border_down(head_border_down, DIRECTION_DOWN);

        Point head_border_left = {0, n_cells_height/2};
        Snake snake_border_left(head_border_left, DIRECTION_LEFT);

        Point head_border_right = {n_cells_width-1, n_cells_height/2};
        Snake snake_border_right(head_border_right, DIRECTION_RIGHT);
        
        // Define other step() arguments (food must not be eaten during step())
        Point food = {0,0};
        int score = 0;
        bool game_over = false;

        // Perform a step forward with each snake
        snake_border_up.step(ACTION_FORWARD, food, score, game_over, n_cells_width, n_cells_height);
        snake_border_down.step(ACTION_FORWARD, food, score, game_over, n_cells_width, n_cells_height);
        snake_border_left.step(ACTION_FORWARD, food, score, game_over, n_cells_width, n_cells_height);
        snake_border_right.step(ACTION_FORWARD, food, score, game_over, n_cells_width, n_cells_height);

        // Check if head positions after step() is as expected
        REQUIRE(snake_border_up.get_head() == head_border_down);
        REQUIRE(snake_border_down.get_head() == head_border_up);
        REQUIRE(snake_border_left.get_head() == head_border_right);
        REQUIRE(snake_border_right.get_head() == head_border_left);

    }
}