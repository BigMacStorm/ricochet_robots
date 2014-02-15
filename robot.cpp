#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// robot struct
    // x and y and color
    
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
    bool won();
    void populate(robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);

int main()
{
   
    // Read the map(s)
    // Create all objects
    robot redBot(-1, -1, 'r');
    robot orangeBot(-1, -1, 'r');
    robot blueBot(-1, -1, 'r');
    robot greenBot(-1, -1, 'r');
    robot yellowBot(-1, -1, 'r');
    
    populate
    
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
