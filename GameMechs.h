#ifndef GAMEMECHS_H
#define GAMEMECHS_H

//Libraries for random generator
#include <cstdlib> //provides srand() and rand()
#include <time.h> //can be replaced by <ctime>
                  //provides time()


#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;

        objPos foodPos;
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);

        ~GameMechs();
        
        bool getExitFlagStatus();
        bool getLoseFlagStatus();

        void setExitTrue();
        void setLoseFlag();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getScore();
        void incrementScore();

        int getBoardSizeX();
        int getBoardSizeY();

        void generateFood(objPosArrayList *blockOff); //you need to upgrade this somehow...
        //Need to accept the player body array list 
        //go through each array list element to make sure they are all 
        //blocked off form random food generation 
        
        
        void getFoodPos(objPos &returnPos);
      

};

#endif