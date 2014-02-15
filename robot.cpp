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
    void display(int sent,
                  robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);
    // check if win
    // populate board
    bool win(int sent, robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);
                  
    void populate(robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot);
    void updateMap(int oldx, int oldy, int x, int y);

cell board[16][16];

int main()
{
   char temp;
   char color;
   char direction;
   int oldx, oldy, newx, newy;
   int numTokes = 17;
   int tokenArray[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
   
   
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
        while(numTokes > 0)
        {
            // Display
            display(tokenArray[numTokes-1], redBot, orangeBot, blueBot, greenBot, yellowBot);
            // Get command
            cout << "Enter move: " << "┖";
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
            updateMap(oldx, oldy, newx, newy);
            // Check if win
            if(win(tokenArray[numTokes-1], redBot, orangeBot, blueBot, greenBot, yellowBot))
            {
               numTokes--;                              
            }
         }
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
    //cout << "reading in data" << endl;
    fin >> cellContents;
    //cout << "got val " << cellContents << " for wall spot" << endl;
    fin >> dummy;
    //cout << "got val " << dummy << " for dummy" << endl;
    fin >> tokes;
    //cout << "got val " << tokes << " for wall spot" << endl;
    fin >> dummy;
    //cout << "got val " << dummy << " for dummy" << endl;
    //cin >> dummy;
        }
        
    
    }
    
    fin.close();
}

void display(int sent,
             robot &redBot, 
             robot &orangeBot, 
             robot &blueBot, 
             robot &greenBot, 
             robot &yellowBot)
{
    char walls[11] = {' ', '^', '_', ']', (char)221, (char)191, (char)217, 
                      192, 218, '=', 186};
                      
    char tokens[18] = {' ', '1','2','3','4','5','6','7','8','9',
                       'A','B','C','D','E','F','G','H'};
    
   robot* redPtr = &redBot;
   robot* orangePtr = &orangeBot;
   robot* bluePtr = &blueBot;
   robot* greenPtr = &greenBot;
   robot* yellowPtr = &yellowBot;
   
   robot* bots[5] = {redPtr, orangePtr, bluePtr, greenPtr, yellowPtr};
    
    cout << endl << endl;
    
    for(int row = 0; row < 16; row++)
    {
        for(int col = 0; col < 16; col++)
        {
            if(board[row][col].token == 0 && board[row][col].hasRobot == false)
            {
                cout << walls[board[row][col].walls];
            }
            else if(board[row][col].token != 0 && 
                    board[row][col].hasRobot == false)
            {
                cout << tokens[board[row][col].token];
            }
            else
            {
                int i = 0;
                while((*(bots[i])).xPos != col || (*(bots[i])).yPos != row)
                {
                    i++;
                }
                
                cout << (*(bots[i])).robColor;
            }
            cout << "  ";
        }
        cout << endl;
    }
    
    cout << "Goal: ";
    
    if(sent <= 9)
    {
        cout << sent << " ";
    }
    else
    {
        cout << (char)('A' + (sent - 10)) << " ";
    }
    cout << endl << endl << "================================" << endl;
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
   if(direction == 'u')
   {
      while((!(board[sent.yPos][sent.xPos].up)) && (!(board[sent.yPos-1][sent.xPos].hasRobot)))
      {
         sent.yPos = sent.yPos-1;
      }
   }
   
   if(direction == 'd')
   {
      while((!(board[sent.yPos][sent.xPos].down)) && (!(board[sent.yPos+1][sent.xPos].hasRobot)))
      {
         sent.yPos = sent.yPos+1;
      }      
   }
   
   if(direction == 'l')
   {
      while((!(board[sent.yPos][sent.xPos].left)) && (!(board[sent.yPos][sent.xPos-1].hasRobot)))
      {
         sent.xPos = sent.xPos-1;
      }      
   }
   
   if(direction == 'r')
   {
      while((!(board[sent.yPos][sent.xPos].right)) && (!(board[sent.yPos][sent.xPos+1].hasRobot)))
      {
         sent.xPos = sent.xPos+1;
      }       
   }
   newx = sent.xPos;
   newy = sent.yPos;
   return true;
}

void updateMap(int oldx, int oldy, int x, int y)
{
   board[oldy][oldx].hasRobot = false;
   board[y][x].hasRobot = true;
}

bool win(int sent, robot &redBot, 
                  robot &orangeBot, 
                  robot &blueBot, 
                  robot &greenBot, 
                  robot &yellowBot)
{
   switch(sent)
   {
      case 2:
      case 5:
      case 12:
      case 16:
         if(board[redBot.yPos][redBot.xPos].token == sent) return true;
         break;
      case 1:
      case 4:
      case 10:
      case 11:
         if(board[blueBot.yPos][blueBot.xPos].token == sent) return true;
         break;
      case 6:
      case 7:
      case 13:
      case 17:
         if(board[greenBot.yPos][greenBot.xPos].token == sent) return true;
         break;
      case 8:
      case 9:
      case 14:
      case 15:
         if(board[yellowBot.yPos][yellowBot.xPos].token == sent) return true;
         break;
   }   
   return false;
}
