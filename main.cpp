#include <iostream>
#include <thread>
#include "src/snake.hpp"
#include "include/raylib.h"
#include "src/game.hpp"

using namespace raylib_ns; // I added the namespace to the raylib to avoid conflicts with catch.hpp definitions

int main(){

    // Initialize game. TODO: take user input to change difficulty and walls implementation
    Game game = init_game(DIFFICULTY_INTERMEDIATE);

    // Initialize default action
    Action action = ACTION_FORWARD;

    // Define termination condition for while loop in get_user_action function used in thread 
    bool stop_get_user_action = false;

    // Use parallel thread to loop until game_over (or window closed) while getting user input and change action if needed (default forward)
    // Increases responsivness of the snake
    std::thread handle_user_inputs(get_user_action, std::ref(action), std::ref(stop_get_user_action));

    // Main loop until game over or window closed
    while(WindowShouldClose()==false && !game.is_game_over()){
        // reset action to default
        action = ACTION_FORWARD;

        // Render state of the game
        game.draw_game_state();

        // Perform game step with current action
        game.step(action);

    }
    CloseWindow();

    // Stop get_user_action loop and wait until thread is terminated.
    stop_get_user_action = true;
    handle_user_inputs.join();

    // Print score at the end of the game.
    std::cout << "Game Over! Your score is: " << game.get_score() << "\n";

    return 0;
}



