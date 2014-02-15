#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// robot struct
    // x and y and color

struct cell
{
    bool occupied;
    int token;
    int walls;
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
    bool move(char color, char direction, int &newx, int &newy);
    // read in maps
    void readInMap();
    // display
    void display();
    // check if win
    // populate board
    bool won();
    void populate(robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);
    void updateMap(char color, int oldx, int oldy, int x, int y);

cell board[16][16];

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

void display()
{
    char walls[11] = {' ', '_', 222, 221, 191, 217, 192, 218, '=', 186};
    char tokens[18] = {' ', '1','2','3','4','5','6','7','8','9',
                       'A','B','C','D','E','F','G','H'};
    
    cout << endl << endl;
    
    for(int row = 0; row < 16; row++)
    {
        for(int col = 0; col < 16; col++)
        {
            if(board[row][col].token == 0)
            {
                cout << walls[board[row][col].walls];
            }
            else
            {
                cout << tokens[board[row][col].token];
            }
        }
        cout << endl;
    }
}

void populate(robot &redBot, 
              robot &orangeBot, 
              robot &blueBot, 
              robot &greenBot, 
              robot &yellowBot)
{
   //put robots on board and shit
   srand(time(NULL));
   
   robot* redPtr = &redBot;
   robot* orangePtr = &orangeBot;
   robot* bluePtr = &blueBot;
   robot* greenPtr = &greenBot;
   robot* yellowPtr = &yellowBot;
   
   robot* bots[5] = {redPtr, orangePtr, bluePtr, greenPtr, yellowPtr};
   
   int thisX, thisY;
   
   for(int i = 0; i < 5; i++)
   {
       thisX = rand() % 16;
       thisY = rand() % 16;
       
       while(board[thisY][thisX].token != 0)
       {
            thisX = rand() % 16;
            thisY = rand() % 16;
       }
       
       (*(bots[i])).xPos = thisX;
       (*(bots[i])).yPos = thisY;
       board[thisY][thisX].occupied = true;
       board[thisY][thisX].hasRobot = true;
   }
}


bool move(char color, char direction, int &newx, int &newy)
{
   return true;
}

void updateMap(char color, int oldx, int oldy, int x, int y)
{
}
