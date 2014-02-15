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
    bool move(char color, char direction, int &newx, int &newy);
    // read in maps
    // display
    // check if win
    // populate board
    bool won();
    void populate(robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);
    void updateMap(char color, int oldx, int oldy, int x, int y);

int main()
{
   char temp;
   char color;
   char direction;
   int oldx, oldy, newx, newy;
   
    // Read the map(s)
    // Create all objects
    robot redBot(-1, -1, 'r');
    robot orangeBot(-1, -1, 'r');
    robot blueBot(-1, -1, 'r');
    robot greenBot(-1, -1, 'r');
    robot yellowBot(-1, -1, 'r');
    
    populate(redBot, orangeBot, blueBot, greenBot, yellowBot);
    
    while(temp != 'N')
    {
        // Randomly choose goal
        // Loop start
            // Display
            // Get command
            cout << "Enter move: ";
            cin >> color;
            cin >> direction;
            if(color == 'r'){oldx = redBot.xPos;oldy = redBot.yPos;}
            if(color == 'o'){oldx = orangeBot.xPos;oldy =   orangeBot.yPos;}
            if(color == 'b'){oldx = blueBot.xPos;oldy = blueBot.yPos;}
            if(color == 'g'){oldx = greenBot.xPos;oldy = greenBot.yPos;}
            if(color == 'y'){oldx = yellowBot.xPos;oldy = yellowBot.yPos;}
            // Move (c, d)
            move(color, direction, newx, newy);
            // update
            updateMap(color, oldx, oldy, newx, newy);
            // Check if win
      cout << "Play Again? : ";
      cin >> temp;
    }
    
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


bool move(char color, char direction, int &newx, int &newy)
{
   return true;
}

void updateMap(char color, int oldx, int oldy, int x, int y)
{
}
