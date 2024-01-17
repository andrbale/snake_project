#include "game.hpp"

using namespace raylib_ns;

// Blank constructor
Game::Game(){}

// Main constructor: spawn 2cells snake in the middle of the game field
Game::Game(const int n_cells_width, const int n_cells_height, const int cell_size){
    this->score = 0;
    this->game_over = false;
    this->n_cells_width = n_cells_width;
    this->n_cells_height = n_cells_height;
    this->cell_size = cell_size; 
    this->food = get_random_point(n_cells_width, n_cells_height);

    Point head = {n_cells_width/2, n_cells_height/2};
    Snake snake(head, DIRECTION_LEFT);

    this->snake = snake;

}

// Perform a game step
void Game::step(const Action& action){

    snake.step(action, this->food, this->score, this->game_over, this->n_cells_width, this->n_cells_height);

    return;
}

// Draw grid in the grafic with cells edges length = cell_size
void Game::draw_grid(){

    ClearBackground(GRAY);

    int window_width = this->n_cells_width*this->cell_size;
    int window_height = this->n_cells_height*this->cell_size;
    
    // Draw vertical lines
    for(int x=0; x<=window_width; x+=this->cell_size){
        DrawLine(x, 0, x, window_height, WHITE);
    }

    // Draw horizontal lines
    for(int y=0; y<=window_height; y+=this->cell_size){
        DrawLine(0, y, window_width, y, WHITE);
    }

    return;
}

// Draw current state of the game
void Game::draw_game_state(){
    BeginDrawing();
    draw_grid();

    this->snake.draw(this->cell_size);

    // Draw food
    DrawCircle(this->food.x*this->cell_size + this->cell_size/2, this->food.y*this->cell_size + this->cell_size/2, this->cell_size*0.4, RED);
    
    EndDrawing();
    return;
}

// Check if game over
bool Game::is_game_over(){
    return this->game_over;
}

// Get score
int Game::get_score(){
    return this->score;
}

// Initialize game. For now difficuly changes and walls are not implemented
Game init_game(const Difficulty& difficulty, const bool wall_presence){

    // Set default game parameters. (TODO: possible changes in the future)
    const int n_cells_width = 20;
    const int n_cells_height = 10;
    const int cell_size = 50;

    // Game constructor
    Game game(n_cells_width, n_cells_height, cell_size);


    int fps;
    if(difficulty == DIFFICULTY_EASY) fps = 5;
    else if(difficulty == DIFFICULTY_INTERMEDIATE) fps = 10;
    else fps = 20; //hard

    // Initialize grafic
    InitWindow(n_cells_width*cell_size, n_cells_height*cell_size, "Snake");

    // Set FPS depending on difficulty
    SetTargetFPS(fps);

    return game;

}

// Take user action, designed to be used in a thread
// loop until stop_loop is set to true in main while getting user input and change action if needed (default forward)
void get_user_action(Action& action, const bool& stop_loop){

    // Set default action
    action = ACTION_FORWARD;
    
    // Bool variable to avoid multiple action execution with one button press
    bool released = true;

    while(!stop_loop){

        // Change action if action keys are pressed after released = true
        if(IsKeyPressed(KEY_LEFT) && released){
            action = ACTION_LEFT;
            released = false;
        }
        if(IsKeyPressed(KEY_RIGHT) && released){
            released = false;
            action = ACTION_RIGHT;
        }

        // Check if action keys are both up
        if(IsKeyUp(KEY_LEFT) && IsKeyUp(KEY_RIGHT)) released = true;
    }
    
    std::cout << "Get user action loop terminated!\n";
    return;
}

// Get user difficulty
Difficulty get_user_difficulty(){

    int difficulty;

    std::cout << "Enter a difficulty. 0: easy, 1: intermediate, 2: hard: \n";
    std::cin >> difficulty;

    // Check if user input is valid
    assert(("You need to input an integer between [0,2]", difficulty>=0 && difficulty<=2));

    return static_cast<Difficulty>(difficulty);
}