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
    bool hasRobot, left, up, right, down;
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
    void readInMap();
    // display
    // check if win
    // populate board
    bool won();
    void populate(robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);

cell board[16][16];

int main()
{
   char temp;
   
    // Read the map(s)
    // Create all objects
    robot redBot(-1, -1, 'r');
    robot orangeBot(-1, -1, 'r');
    robot blueBot(-1, -1, 'r');
    robot greenBot(-1, -1, 'r');
    robot yellowBot(-1, -1, 'r');
    
    populate(redBot, orangeBot, blueBot, greenBot, yellowBot);
    
    while(temp != N)
    {
        // Randomly choose goal
        // Loop start
            // Display
            // Get command
            // Move (c, d)
            // Check if win
      cout << "Play Again? : ";
      cin >> temp;
    }
    
    return 0;
}

void readInMap()
{
    ifstream fin;
    
    fin.clear();
    fin.open("map1");
    
    char cellContents;
    
    fin >> cellContents;
    
    for(int row = 0; row < 16 && fin.good(); row++)
    {
        for(int col = 0; col < 16 && fin.good(); col++)
        {
            board[row][col].occupied = false;
            
            if(cellContents == '1' || cellContents == '5' ||
               cellContents == '8')
            {
                board[row][col].left = true;
                board[row][col].occupied = true;
            }
            
            if(cellContents == '2' || cellContents == '6' ||
               cellContents == '1')
            {
                board[row][col].up = true;
                board[row][col].occupied = true;
            }
            
            if(cellContents == '3' || cellContents == '7' ||
               cellContents == '2')
            {
                board[row][col].right = true;
                board[row][col].occupied = true;
            }
            
            if(cellContents == '4' || cellContents == '8' ||
               cellContents == '3')
            {
                board[row][col].down = true;
                board[row][col].occupied = true;
            }
        }
        
        fin >> cellContents;
    }
    
    fin.close();
}

void populate(robot &redBot, 
              robot &orangeBot, 
              robot &blueBot, 
              robot &greenBot, 
              robot &yellowBot)
{
   //put robots on board and shit
}
