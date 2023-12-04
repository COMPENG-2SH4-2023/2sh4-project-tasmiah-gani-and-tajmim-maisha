#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

// Global pointer to specific classes
GameMechs* myGM;

objPos myPos;

//This is a makeshift setup, so I don't hav eto touch generateItem yet. 
//think about how to change myfoodPos into an array list operation
//you have to do this by yourself 
objPos myfoodPos{-1, -1, 'o'};       //--------------T


Player* myPlayer;


bool exitFlag;
bool collide;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

char gameBoard[15][30];

int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    // Create a gameMechanics object on the heap and initialize its fields    
    myGM = new GameMechs(30, 15); //makes board size 30x15
    
    myPlayer = new Player(myGM);
    
    collide = true;

    //Think about when to generate the new food...

    //Think about whether you want to set up a debug key to call the food generation routine fro verification 

    //remember, generateFood() requires player reference. You will need to provide it AFTER player object is instantiated


}

void GetInput(void)
{

    //access correct info using getter method
    char input = myGM-> getInput();
    
    //collects input char 
    myGM->setInput(input);

    // Debug: Press 'i' to increment the score
        if (input == 'i')
        {
            myGM->incrementScore();
            cout << "Debug: Score incremented. New score: " << myGM->getScore() << endl;
        }

        // Debug: Press 'l' to set the lose fla
        else if (input == 'l')
        {
            myGM->setLoseFlag();
            cout << "Debug: Lose flag set. Game will end with lose message." << endl;
        }

    
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    if(collide) {
        myGM->generateFood(myfoodPos);  //----------T
        collide = false;
    }

    //clear input field in GM
    // so to not repeatedly process the input
    myGM->clearInput();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();

    objPosArrayList* playerBody = getPlayerPos();

    // objPos tempPos;
    myPlayer->getPlayerPos(myPos);

    myGM->getFoodPos(myfoodPos);    //----------T

    // MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", 
    //                 myGM->getBoardSizeX(),
    //                 myGM->getBoardSizeY(),
    //                 tempPos.x, tempPos.y, tempPos.symbol);

    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n",
                    myGM->getBoardSizeX(),
                    myGM->getBoardSizeY(),
                    myPos.x, myPos.y, myPos.symbol);


    MacUILib_printf("food: <%d, %d> + %c\n",
                    myfoodPos.x, myfoodPos.y, myfoodPos.symbol);

    MacUILib_printf("Score: %d, Player Pos: <%d, %d>\n",
    myGM->getScore(), myPos.x, myPos.y);

    //Print board and moving character on screen
    for(int row = 0; row < myGM->getBoardSizeY(); row++) {
        for(int col = 0; col < myGM->getBoardSizeX(); col++) {

            //print game board
            if(0 == row || (myGM->getBoardSizeY()-1) == row || 0 == col || (myGM->getBoardSizeX()-1) == col) {
                printf("%c", '#');
            }
            else if(j == tempPos.x && i == tempPos.y)
            {
                printf("%c", tempPos.symbol);
            }
            else if(j == myFoodPos.x && i == myFoodPos.y)
            {
                printf("%c", myFoodPos.symbol);
            }
            else
            {
                printf("%c", ' ');
            }
/*
            //print moving character
            else if(myPos.y == row && myPos.x == col) {
                gameBoard[row][col] = myPos.symbol;
            }

            //print food character
            else if(myfoodPos.y == row && myfoodPos.x == col) {
                printf("%c", my.symbol);
            }

            //print empty space on board
            else {
                printf("%c", ' ');
            }
        }

        printf("\n");
        */

    }


}
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

//delete GM object from heap
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    // remove heap instances
    delete myGM;
    delete myPlayer;
}
