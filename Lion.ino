#include <Arduboy2.h>
#include "src/images/Images.h"
#include "src/utils/Consts.h"
#include "src/entities/Player.h"
#include "src/entities/Lion.h"
#include "src/entities/Explosions.h"
#include "src/entities/Explosion.h"
#include "src/fonts/Font3x5.h"

Arduboy2Base arduboy;
Font3x5 font3x5 = Font3x5();

Player player1;
Player player2;
Lion lion1;
Lion lion2;
Explosions explosions;

bool explosionSet = false;
Direction lionAttacking = Direction::None;
uint8_t lionAttackingIndex = 0;
GameState gameState = GameState::Title;

void setup(void) {

	arduboy.boot();
	arduboy.flashlight();
	arduboy.systemButtons();
	arduboy.audio.begin();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(70);

    font3x5.setTextColor(0);

    player1.reset(Constants::Player1_Index, Constants::Player1_XPos, Constants::Player1_YPos); 
    player2.reset(Constants::Player2_Index, Constants::Player2_XPos, Constants::Player2_YPos); 

    lion1.setDirection(Direction::Left);
    lion1.setYPosition(YPosition::Level_1);
    lion1.setIndex(Constants::Lion1_Index);

    lion2.setDirection(Direction::Right);
    lion2.setYPosition(YPosition::Level_2);
    lion2.setIndex(Constants::Lion2_Index);
	
}

void loop(void) {

	if (!arduboy.nextFrame()) return;

	arduboy.pollButtons();
    arduboy.clear();

    switch (gameState) {

        case GameState::Title:
            title();
            break;

        case GameState::PlayGame:
            playGame();
            break;

    }


    arduboy.display();

}

