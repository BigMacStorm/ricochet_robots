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
    bool move(robot& sent, char direction, int &newx, int &newy);
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
    readInMap();
    // Create all objects
    robot redBot(-1, -1, 'r');
    robot orangeBot(-1, -1, 'o');
    robot blueBot(-1, -1, 'b');
    robot greenBot(-1, -1, 'g');
    robot yellowBot(-1, -1, 'y');
    
    populate(redBot, orangeBot, blueBot, greenBot, yellowBot);
    
    while(temp != 'N')
    {
        // Randomly choose goal
        // Loop start
            // Display
            display();
            // Get command
            cout << "Enter move: ";
            cin >> color;
            cin >> direction;
            switch(color)
            {
               case 'r':
                  oldx = redBot.xPos;
                  oldy = redBot.yPos;
                  move(redBot, direction, newx, newy);
                  break;
               case 'o':
                  oldx = orangeBot.xPos;
                  oldy = orangeBot.yPos;
                  move(orangeBot, direction, newx, newy);
                  break;
               case 'b':
                  oldx = blueBot.xPos;
                  oldy = blueBot.yPos;
                  move(blueBot, direction, newx, newy);
                  break;
               case 'y':
                  oldx = yellowBot.xPos;
                  oldy = yellowBot.yPos;
                  move(yellowBot, direction, newx, newy);
                  break;
               case 'g':
                  oldx = greenBot.xPos;
                  oldy = greenBot.yPos;
                  move(greenBot, direction, newx, newy);
                  break;
             }
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
    
    int cellContents;
    int tokes;
    char dummy;
    
    fin >> cellContents;
    fin >> dummy;
    fin >> tokes;
    fin >> dummy;
    
    for(int row = 0; row < 16 && fin.good(); row++)
    {
        for(int col = 0; col < 16 && fin.good(); col++)
        {
            board[row][col].occupied = false;
            board[row][col].token = tokes;
            board[row][col].walls = cellContents;
            
            if(cellContents == 4 || cellContents == 7 ||
               cellContents == 8 || cellContents == 10)
            {
                board[row][col].left = true;
                board[row][col].occupied = true;
            }
            
            if(cellContents == 1 || cellContents == 5 ||
               cellContents == 8 || cellContents == 9)
            {
                board[row][col].up = true;
                board[row][col].occupied = true;
            }
            
            if(cellContents == 3 || cellContents == 5 ||
               cellContents == 6 || cellContents == 10)
            {
                board[row][col].right = true;
                board[row][col].occupied = true;
            }
            
            if(cellContents == 2 || cellContents == 6 ||
               cellContents == 7 || cellContents == 9)
            {
                board[row][col].down = true;
                board[row][col].occupied = true;
            }
        }
        
        fin >> cellContents;
        fin >> dummy;
        fin >> tokes;
        fin >> dummy;
    }
    
    fin.close();
}

void display()
{
    char walls[11] = {' ', '^', '_', 222, 221, 191, 217, 192, 218, '=', 186};
    char tokens[18] = {' ', '1','2','3','4','5','6','7','8','9',
                       'A','B','C','D','E','F','G','H'};
    
    cout << endl << endl;
    
    for(int row = 0; row < 16; row++)
    {
        for(int col = 0; col < 16; col++)
        {
            if(board[row][col].token == 0)
            {
                cout << walls[board[row][col].walls-1];
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


bool move(robot &sent, char direction, int &newx, int &newy)
{
   char color = sent.robColor;
   bool end = false;
   if(direction = 'u')
   {
      while((!(board[sent.yPos][sent.xPos].up)) && (!(board[sent.yPos-1][sent.xPos].hasRobot)))
      {
         sent.yPos = sent.yPos-1;
      }
   }
   
   if(direction = 'd')
   {
      while((!(board[sent.yPos][sent.xPos].down)) && (!(board[sent.yPos+1][sent.xPos].hasRobot)))
      {
         sent.yPos = sent.yPos+1;
      }      
   }
   
   if(direction = 'l')
   {
      while((!(board[sent.yPos][sent.xPos].left)) && (!(board[sent.yPos][sent.xPos-1].hasRobot)))
      {
         sent.xPos = sent.xPos-1;
      }      
   }
   
   if(direction = 'u')
   {
      while((!(board[sent.yPos][sent.xPos].left)) && (!(board[sent.yPos][sent.xPos+1].hasRobot)))
      {
         sent.xPos = sent.xPos+1;
      }       
   }
   
   return true;
}

void updateMap(char color, int oldx, int oldy, int x, int y)
{
}
