#include <iostream>

// Class Libraries:
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

// Global pointer to the instances of the two class
GameMechs* myGM;
Player* myPlayer;


//This is a makeshift setup, so I don't hav eto touch generateItem yet. 
//think about how to change myfoodPos into an array list operation
//you have to do this by yourself 


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    //Run program when the exit flag is false
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
    myGM->generateFood(myPlayer->getPlayerPos()); //myPlayer->getPlayerPos()

}

void GetInput(void)
{
    // Collects the input ASCII character into the corresponding field in the gameMechs object
    myGM-> getInput();
    
}

void RunLogic(void)
{
    //Movement Control Of Player 
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    //Initialization of variables:
    objPos newInsert;
    objPos myFoodPos;
    objPos tempBody;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myGM->getFoodPos(myFoodPos);


    //Food Collection
    playerBody->getHeadElement(tempBody);
    if(tempBody.isPosEqual(&myFoodPos))
    {
        myGM->incrementScore();
        newInsert.setObjPos(tempBody.x, tempBody.y, '*');
        playerBody->insertHead(newInsert);
        myGM->generateFood(playerBody);
    }

    //Self collision detection
    if(myPlayer->selfCollision())
    {
        myGM->setLoseFlag();
    }

    // Clears input field in GM to not repeatedly process the input
    myGM->clearInput();     
}

void DrawScreen(void)
{

    MacUILib_clearScreen();

    //initializing variables for this func:
    bool drawn;
    objPos tempBody;
    objPos myFoodPos;
    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    myGM->getFoodPos(myfoodPos);
    

    // Game header message
    MacUILib_printf("-------------------GROW UR SSSSSSNAKE!!!---------------------\n"); 

    //GAMEBOARD PRINTING
    
    for(int i = 0; i < myGM->getBoardSizeY(); i++) {
        for(int j = 0; j < myGM->getBoardSizeX(); j++) {

            drawn = false;
            
            //DRAWING THE PLAYER: iterate through every element in the list...
            for(int k = 0; k < playerBody->getSize; k++) {
                playerBody->getElement(tempBody, k);

                if(tempBody.x == j && tempBody.y == i) {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                    
                }
            }

            if(drawn) continue;
            //if player body was drawn don't draw anything below.

            //print game board borders
            if(0 == i || (myGM->getBoardSizeY()-1) == i || 0 == j || (myGM->getBoardSizeX()-1) == j) {
                MacUILib_printf("%c", '#');
            }

            //Print Food on the Board
            else if(j == myFoodPos.x && i == myFoodPos.y)
            {
                MacUILib_printf("%c", myFoodPos.symbol);
            }

            //Fill Board with empty spaces
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    //------------------------------------------------------------------------
    
    // MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n",
    //                 myGM->getBoardSizeX(),
    //                 myGM->getBoardSizeY(),
    //                 tempBody.x, tempBody.y, tempBody.symbol);


    MacUILib_printf("Score: %d\n", myGM->getScore());

    MacUILib_printf("food Pos: <%d, %d> + %c\n",
                    myfoodPos.x, myfoodPos.y, myfoodPos.symbol);

    //WELCOME MESSAGE?

    // QUIT GAME MESSAGE
    if(myGM->getExitFlagStatus()) {
        MacUILib_printf("Quit game."); 
    }

    // LOST GAME MESSAGE        
    if(myGM->getLoseFlagStatus()) {
        MacUILib_printf("You LOST!"); 
        myGM->setExitTrue();
    }


}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{

//delete GM object from heap
    // MacUILib_clearScreen();    
  
    MacUILib_uninit();

    // remove heap instances
    delete myGM;
    delete myPlayer;
}
