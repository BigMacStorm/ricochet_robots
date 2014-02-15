#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// robot struct
    // x and y and color

struct cell
{
    bool occupied;
    bool robot, left, up, right, down;
};
    
struct robot{
   int xPos;
   int yPos;
   char robColor;
   
   robot(int x, int y, char color)
   {
      xPos = x;
      yPos = y;
      robColor = color;
   }
};
    
// Functions
    // move
    bool move(char color, char direction);
    // read in maps
    // display
    // check if win
<<<<<<< HEAD
    // populate board
=======
    bool won();
    void populate(robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);
>>>>>>> 130eb2a13c45807f43c471a50a72ef59ebc20f36

int main()
{
   
    // Read the map(s)
    // Create all objects
<<<<<<< HEAD
=======
    robot redBot(-1, -1, 'r');
    robot orangeBot(-1, -1, 'r');
    robot blueBot(-1, -1, 'r');
    robot greenBot(-1, -1, 'r');
    robot yellowBot(-1, -1, 'r');
    
    populate
    
>>>>>>> 130eb2a13c45807f43c471a50a72ef59ebc20f36
    // Loop 1 start
        // Randomly choose goal
        // Loop start
            // Display
            // Get command
            // Move (c, d)
            // Check if win
    
    return 0;
}


void populate(robot &redBot, 
              robot &orangeBot, 
              robot &blueBot, 
              robot &greenBot, 
              robot &yellowBot)
{
   //put robots on board and shit
}
