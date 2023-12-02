#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

objPos myPos;
Player* myPlayer;
char game_board[15][30];

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

    myPlayer = new Player(myGM);

}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
}

void DrawScreen(void)
{

    MacUILib_clearScreen();

    objPos tempPos;
    myPlayer.getPlayerPos(tempPos);

    MacUILib_printf("BoardSize: %dx%d, Player Pos: <%d, %d> + %c\n", 
                    myGM->getBoardSizeX(),
                    myGM->getBoardSizeY(),
                    tempPos.x, tempPos.y, tempPos.symbol);


    // objPos tempPlayer;
    // int yy = 30;
    // int xx = 15;

    // //yy=myGam.get--()

    // for(int row = 0; row < yy; row++) {
    //     for(int col = 0; col < xx; col++) {

    //         item = 0;
    //         //print game board
    //         if(0 == row || (yy-1) == row || 0 == col || (xx-1) == col) {
    //             gameBoard[row][col] = '#';
    //         }

    //         //print moving character
    //         else if(playerPos.y == row && playerPos.x == col) {
    //             gameBoard[row][col] = playerPos.symbol;
    //         }

    //         //print empty space on board
    //         else {
    //             gameBoard[row][col] = ' ';
    //         }
            
    //         // for(count1 = 0; count1 < 5; count1++){
    //         //     if(ItemBin[count1].y == row && ItemBin[count1].x == col) {
    //         //         gameBoard [row][col] = ItemBin[count1].symbol;
    //         //         // MacUILib_printf("%c", ItemBin[count1].symbol);
    //         //         item = 1;
    //         //         break;
    //         //     }
    //         // }

    //         MacUILib_printf("%c", gameBoard[row][col]);

    //         if (item == 0) {
    //             MacUILib_printf("");
    //         }
            
    //     }
    //     printf("\n");
    // }
 

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
