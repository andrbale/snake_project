#include "snake.hpp"

using namespace raylib_ns;

// Blank constructor
Snake::Snake(){}

// Initialize snake with a 2-Points body given initial head and direction
Snake::Snake(Point head, Direction direction){

    this->direction = direction;

    Point next = head;

    if(direction == DIRECTION_UP) next.y++;
    else if(direction == DIRECTION_RIGHT) next.x--;
    else if(direction == DIRECTION_DOWN) next.y--;
    else next.x++;

    this->body.push_back(next);
    this->body.push_back(head);
}

// Constructor to externally set body and direction. This constructor is used to ease unit testing of target functions
Snake::Snake(std::deque<Point> body, Direction direction){
    this->body = body;
    this->direction = direction;
}

// Get current direction
Direction Snake::get_direction(){
    return this->direction;
}

// Update direction given an action
void Snake::update_direction(const Action& action){

    if(action == ACTION_LEFT) this->direction--;
    else if(action == ACTION_RIGHT) this->direction++;

    return;
}

// Get body (used for testing and debugging)
std::deque<Point> Snake::get_body(){
    return this->body;
}

// Get head coordinates
Point Snake::get_head(){
    return this->body.back();
}

// Return next position of the head after a step.
// Inputs: number of cells in horizontal and vertical dimensions
Point Snake::get_next_head(const int n_cells_width, const int n_cells_height){

    Point next_head = get_head();

    // Calculate coordinates given the direction
    switch (this->direction)
    {
    case DIRECTION_UP:
        next_head.y--;
        break;
    
    case DIRECTION_RIGHT:
        next_head.x++;
        break;

    case DIRECTION_DOWN:
        next_head.y++;
        break;
    
    case DIRECTION_LEFT:
        next_head.x--;
        break;

    default: //Do nothing, never happening
        break;
    }

    // Handle border teleport cases
    if(next_head.x<0) next_head.x = n_cells_width-1;
    if(next_head.x>=n_cells_width) next_head.x = 0;
    if(next_head.y<0) next_head.y = n_cells_height-1;
    if(next_head.y>=n_cells_height) next_head.y = 0;
    
    return next_head;
}

// Check if head collides with body (true if yes)
bool Snake::self_collision(){

    Point head = this->get_head();

    int n = this->body.size();

    for(int i=0; i<n-1; i++){
        if(head == this->body[i]) return true;
    }

    return false;
}

// Check if target point is inside of snake (true if yes)
bool Snake::point_to_body_collision(const Point& target){
    int n = this->body.size();

    for(int i=0; i<n; i++){
        if(target == this->body[i]) return true;
    }

    return false;
}

// Perform step by pushing the new head given current direction and checking for self collision (that would result in game over)
void Snake::step(const Action& action, Point& food, int& score, bool& game_over, const int n_cells_width, const int n_cells_height){

    // Update direction given current action
    update_direction(action);

    // Get head
    Point curr_head = get_head();

    // Get coordinates of next head
    Point next_head = get_next_head(n_cells_width, n_cells_height);

    // Push next head to the body deque
    this->body.push_back(next_head);

    // If next head is in the same cell as food do not pop tail
    if(food == next_head){
        score++;
        do{
            food = get_random_point(n_cells_width, n_cells_height);
        }while(point_to_body_collision(food));
        
    }
    // Pop tail if food was not eaten
    else{
        this->body.pop_front();
    }

    // Chech if head collides with body -> game over
    if(self_collision()){
        game_over = true;
    }

    return;
}

// Draw snake
void Snake::draw(const int cell_size){

    // Get length of snake
    int n = this->body.size();

    for(int i=0; i<n; i++){

        // Draw each snake's segment
        DrawRectangle(this->body[i].x*cell_size, this->body[i].y*cell_size, cell_size, cell_size, GREEN);
        DrawRectangleLines(this->body[i].x*cell_size, this->body[i].y*cell_size, cell_size, cell_size, DARKGREEN);

        // Draw eyes to head segment
        if(i==n-1){

            Point left_eye = this->body[i]*cell_size;
            Point right_eye = this->body[i]*cell_size;
            int radius_eye = cell_size/8;

            if(this->direction == DIRECTION_UP){
                left_eye.x += cell_size/3;
                left_eye.y += cell_size/3;
                right_eye.x += cell_size*2/3;
                right_eye.y += cell_size/3;
            }
            else if(this->direction == DIRECTION_RIGHT){
                left_eye.x += cell_size*2/3;
                left_eye.y += cell_size/3;
                right_eye.x += cell_size*2/3;
                right_eye.y += cell_size*2/3;
            }
            else if(this->direction == DIRECTION_DOWN){
                left_eye.x += cell_size*2/3;
                left_eye.y += cell_size*2/3;
                right_eye.x += cell_size/3;
                right_eye.y += cell_size*2/3;
            }
            else{ // DIRECTION_LEFT
                left_eye.x += cell_size/3;
                left_eye.y += cell_size*2/3;
                right_eye.x += cell_size/3;
                right_eye.y += cell_size/3;
            }

            DrawCircle(left_eye.x, left_eye.y, radius_eye, BLUE);
            DrawCircle(right_eye.x, right_eye.y, radius_eye, BLUE);

        }
    }

    return;
}

