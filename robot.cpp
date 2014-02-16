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
    void display(int sent);
    void construct(int sent);
    // check if win
    // populate board
    bool win(int sent);                  
    void populate();
    void updateMap(int oldx, int oldy, int x, int y);

cell board[16][16];

robot redBot(-1, -1, 'r');
robot orangeBot(-1, -1, 'o');
robot blueBot(-1, -1, 'b');
robot greenBot(-1, -1, 'g');
robot yellowBot(-1, -1, 'y');

string represent[33][33];

int main()
{
   srand(time(NULL));
   char temp;
   char color;
   char direction;
   int oldx, oldy, newx, newy;
   int numTokes = 17;
   int tokenArray[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
   
   
    // Read the map(s)
    readInMap();
    // Create all objects
    
    populate();
    
    while(temp != 'N')
    {
        // Randomly choose goal
        for(int i = 0; i < 17; i++)
        {
            int swapWith = rand() % 17;
            int temp;
            
            temp = tokenArray[i];
            tokenArray[i] = tokenArray[swapWith];
            tokenArray[swapWith] = temp;
        }
        
        while(numTokes > 0)
        {
            // Display
            construct(tokenArray[numTokes-1]);
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
            updateMap(oldx, oldy, newx, newy);
            // Check if win
            if(win(tokenArray[numTokes-1]))
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
       fin >> cellContents;
       fin >> dummy;
       fin >> tokes;
       fin >> dummy;
        }
        
    
    }
    
    for(int x=0; x<33; x++)
    {
      for(int y=0; y<33; y++)
      {
         represent[x][y] = '_';
      }
    }
    
    fin.close();
}

void display(int sent)
{   
   bool stupid = false;
   cout << "      Current Board:" << endl << endl;
   for(int x=0; x<33; x++)
   {
      cout << " ";
      for(int y=0; y<33; y++)
      {
         if(x%2==0)
         {
            if(represent[x][y] != "X")
            {
              cout << " " << " ";            
            }
            else 
            {
               cout << represent[x][y] << " ";
            }            
         }
         else
         {
            if(represent[x][y] != "X" && stupid)
            {
              cout << represent[x][y] << " ";
              stupid = !stupid;
            }
            else if(represent[x][y] != "X" && !stupid)
            {
              cout << " " << " "; 
              stupid = !stupid;           
            }
            else 
            {
               cout << represent[x][y] << " ";
               stupid = !stupid;
            }
         }
      }
      stupid = false;
      cout << endl;
   }
  
  //old display, still works
/*   
    string walls[11] = {" ", "‾", "_", "⎹", "⎸", "⌝", "⌟",
                      "⌞", "⌜", "二", "||"};
                 
                    
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
                while((*(bots[i])).xPos != row || (*(bots[i])).yPos != col)
                {
                    i++;
                }
                
                cout << (*(bots[i])).robColor;
            }
            cout << ".";
        }
        cout << endl;
    }*/
}

void construct(int sent)
{    
   int xOffset = 1;
   int yOffset = 1;
   int count = 0;
   robot* redPtr = &redBot;
   robot* orangePtr = &orangeBot;
   robot* bluePtr = &blueBot;
   robot* greenPtr = &greenBot;
   robot* yellowPtr = &yellowBot;
   
   robot* bots[5] = {redPtr, orangePtr, bluePtr, greenPtr, yellowPtr};
   
   char dummy;
   for(int x=0; x<33; x++)
   {
      for(int y=0; y<33; y++)
      {
         if(x==0) represent[x][y] = "X";
         if(y==0) represent[x][y] = "X";
         if(y==32) represent[x][y] = "X";   
         if(x==32) represent[x][y] = "X";   
         if(represent[x][y] == "r" || 
            represent[x][y] == "o" || 
            represent[x][y] == "y" || 
            represent[x][y] == "b" || 
            represent[x][y] == "g")
            represent[x][y] = "_";   
      }
   }
   
   
   for(int x = 0; x < 16; x++)
   {
      yOffset = 1;
      for(int y = 0; y < 16; y++)
      {
         if(board[x][y].walls == 1){represent[x+xOffset-1][y+yOffset] = "X";} //up
         
         else if(board[x][y].walls == 2) represent[x+xOffset+1][y+yOffset] = "X"; //down
         
         else if(board[x][y].walls == 3) represent[x+xOffset][y+yOffset+1] = "X"; //right
         
         else if(board[x][y].walls == 4) represent[x+xOffset][y+yOffset-1] = "X"; //left 
         
         else if(board[x][y].walls == 5){represent[x+xOffset-1][y+yOffset] = "X"; //up
                                    represent[x+xOffset][y+yOffset+1] = "X"; //right
                                    represent[x+xOffset-1][y+yOffset+1] = "X";}//up+right    
                                         
         else if(board[x][y].walls == 6){represent[x+xOffset+1][y+yOffset] = "X"; //down
                                    represent[x+xOffset][y+yOffset+1] = "X"; //right
                                    represent[x+xOffset+1][y+yOffset+1] = "X";}//down+right  
                                           
         else if(board[x][y].walls == 7){represent[x+xOffset+1][y+yOffset] = "X"; //down
                                    represent[x+xOffset][y+yOffset-1] = "X"; //left
                                    represent[x+xOffset+1][y+yOffset-1] = "X";}//down+left     
                                        
         else if(board[x][y].walls == 8){represent[x+xOffset-1][y+yOffset] = "X"; //up
                                    represent[x+xOffset][y+yOffset-1] = "X"; //left
                                    represent[x+xOffset-1][y+yOffset-1] = "X";} //up+left
                                    
         if(board[x][y].token != 0)
         {
            switch(board[x][y].token)
            {
               case 1:
               case 2:
               case 3:
               case 4:
               case 5:
               case 6:
               case 7:
               case 8:
               case 9:
                  represent[x+xOffset][y+yOffset] = board[x][y].token + 48;
                  break;
               case 10:
                  represent[x+xOffset][y+yOffset] = "A";
                  break;
               case 11:
                  represent[x+xOffset][y+yOffset] = "B";
                  break;
               case 12:
                  represent[x+xOffset][y+yOffset] = "C";
                  break;
               case 13:
                  represent[x+xOffset][y+yOffset] = "D";
                  break;
               case 14:
                  represent[x+xOffset][y+yOffset] = "E";
                  break;
               case 15:
                  represent[x+xOffset][y+yOffset] = "F";
                  break;
               case 16:
                  represent[x+xOffset][y+yOffset] = "G";
                  break;
               case 17:
                  represent[x+xOffset][y+yOffset] = "H";
                  break;
            }
               
         }
                                    
         if(board[x][y].hasRobot){represent[x+xOffset][y+yOffset] = "Q";}
                                    
         for(int z=0;z<5;z++)
         {
            if(bots[z]->xPos == x && bots[z]->yPos == y)
            {
               represent[x+xOffset][y+yOffset] = bots[z]->robColor;
            }
         } 
              
         
         yOffset += 1;
      }
      xOffset += 1;
   }
   
    display(sent);
    cout << endl << "    Current objective is: ";
    if(sent <= 9)
    {
        cout << sent << " ";
    }
    else
    {
        cout << (char)('A' + (sent - 10)) << " ";
    } 
    cout << " which is a ";
    switch(sent)
    {
      case 1:
      case 4:
      case 10:
      case 11:
         cout << "blue ";
         break;
      case 2:
      case 5:
      case 12:
      case 16:
         cout << "red ";
         break;
      case 6:
      case 7:
      case 13:
      case 17:
         cout << "green ";
         break;
      case 8:
      case 9:
      case 14:
      case 15:
         cout << "yellow ";
         break;
      case 3:
         cout << "wild ";
         break;
    }
    
    switch(sent)
    {
      case 1:
      case 6:
      case 12:
      case 15:
         cout << "moon";
         break;
      case 2:
      case 9:
      case 11:
      case 17:
         cout << "triangle";
         break;
      case 4:
      case 5:
      case 13:
      case 14:
         cout << "star";
         break;
      case 7:
      case 8:
      case 10:
      case 16:
         cout << "square";
         break;
      case 3:
         cout << "wild";
         break;
    }
    cout << endl << endl << "================================" << endl;
}

void populate()
{
   //put robots on board and shit
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
       
       while(board[thisX][thisY].token != 0)
       {
            thisX = rand() % 16;
            thisY = rand() % 16;
       }
       
       (*(bots[i])).xPos = thisX;
       (*(bots[i])).yPos = thisY;
       board[thisX][thisY].occupied = true;
       board[thisX][thisY].hasRobot = true;
   }
}


bool move(robot &sent, char direction, int &newx, int &newy)
{
   char color = sent.robColor;
   bool end = false;
   char dummy;
   if(direction == 'u')
   {
      while((!(board[sent.xPos][sent.yPos].up)) && (!(board[sent.xPos-1][sent.yPos].hasRobot)))
      {
         sent.xPos = sent.xPos-1;
      }
   }
   
   if(direction == 'd')
   {
      while((!(board[sent.xPos][sent.yPos].down)) && (!(board[sent.xPos+1][sent.yPos].hasRobot)))
      {
         sent.xPos = sent.xPos+1;
      }      
   }
   
   if(direction == 'l')
   {
      while((!(board[sent.xPos][sent.yPos].left)) && (!(board[sent.xPos][sent.yPos-1].hasRobot)))
      {
         sent.yPos = sent.yPos-1;
      }      
   }
   
   if(direction == 'r')
   {
      while((!(board[sent.xPos][sent.yPos].right)) && (!(board[sent.xPos][sent.yPos+1].hasRobot)))
      {
         sent.yPos = sent.yPos+1;
      }       
   }
   newy = sent.yPos;
   newx = sent.xPos;
   return true;
}

void updateMap(int oldx, int oldy, int x, int y)
{
   board[oldx][oldy].hasRobot = false;
   board[x][y].hasRobot = true;
}

bool win(int sent)
{
   switch(sent)
   {
      case 2:
      case 5:
      case 12:
      case 16:
         if(board[redBot.xPos][redBot.yPos].token == sent) return true;
         break;
      case 1:
      case 4:
      case 10:
      case 11:
         if(board[blueBot.xPos][blueBot.yPos].token == sent) return true;
         break;
      case 6:
      case 7:
      case 13:
      case 17:
         if(board[greenBot.xPos][greenBot.yPos].token == sent) return true;
         break;
      case 8:
      case 9:
      case 14:
      case 15:
         if(board[yellowBot.xPos][yellowBot.yPos].token == sent) return true;
         break;
      case 3:
         if(board[yellowBot.xPos][yellowBot.yPos].token == sent) return true;
         else if(board[greenBot.xPos][greenBot.yPos].token == sent) return true;
         else if(board[blueBot.xPos][blueBot.yPos].token == sent) return true;
         else if(board[redBot.xPos][redBot.yPos].token == sent) return true;
   }   
   return false;
}
