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
Player* myPlayer;


//This is a makeshift setup, so I don't hav eto touch generateItem yet. 
//think about how to change myfoodPos into an array list operation
//you have to do this by yourself 
//------objPos myfoodPos{-1, -1, 'o'};       //--------------T


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
    // this is a makeshift setup so I don't have to touch generateItem yet
    // you need to do this yourself :)
    objPos tempPos{-1, -1, 'o'};
    myGM->generateFood(tempPos);


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

    // if(collide) {
    //     myGM->generateFood(myfoodPos);  //----------T
    //     collide = false;
    // }

    myGM->clearInput();     // clear input field in GM to not repeatedly process the input
}

void DrawScreen(void)
{

    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos myFoodPos;
    myGM->getFoodPos(myfoodPos);



    //Print board and moving character on screen
    for(int i = 0; i < myGM->getBoardSizeY(); i++) {
        for(int j = 0; j < myGM->getBoardSizeX(); j++) {

            drawn = false;
            
            //iterate through every element in the list
            for(int k = 0; k < playerBody->getSize; K++) {
                playerBody->getElement(tempBody, i);
                if(tempBody.x == j && tempBody.y == i) {
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;

                }
            }

            if(drawn) continue;
            //if player body was drawn don't draw anytjing below.

            //print game board
            if(0 == i || (myGM->getBoardSizeY()-1) == i || 0 == j || (myGM->getBoardSizeX()-1) == j) {
                MacUILib_printf("%c", '#');
            }

            else if(j == myFoodPos.x && i == myFoodPos.y)
            {
                prinMacUILib_printftf("%c", myFoodPos.symbol);
            }
            else
            {
                MacUILib_printf("%c", ' ');
            }
        }
        MacUILib_printf("\n");
    }

    //------------------------------------------------------------------------
    
    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n",
                    myGM->getBoardSizeX(),
                    myGM->getBoardSizeY(),
                    tempBody.x, tempBody.y, tempBody.symbol);


    MacUILib_printf("Score: %d\n", myGM->getScore());
    
    MacUILib_printf("food Pos: <%d, %d> + %c\n",
                    myfoodPos.x, myfoodPos.y, myfoodPos.symbol);







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
