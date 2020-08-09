#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
#include "src/images/Images.h"
#include "src/utils/Consts.h"
#include "src/entities/Player.h"
#include "src/entities/Lion.h"
#include "src/entities/Explosions.h"
#include "src/entities/Explosion.h"
#include "src/sounds/Sounds.h"

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Player player1;
Player player2;
Lion lion1;
Lion lion2;
Explosions explosions;

Direction lionAttacking = Direction::None;
uint8_t lionAttackingIndex = 0;
GameState gameState = GameState::Title_Init;

uint8_t frameRate = 50;
int16_t counter = 10;
uint16_t score = 0;
uint8_t numberOfLives = 3;
uint8_t ledDelay = 0;

void setup(void) {

	arduboy.boot();
	arduboy.flashlight();
	arduboy.systemButtons();
	arduboy.audio.begin();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(50);
    arduboy.setRGBled(0, 0, 0);
	
}

void loop(void) {

	if (!arduboy.nextFrame()) return;

	arduboy.pollButtons();

    switch (gameState) {

        case GameState::Title_Init:

            gameState = GameState::Title;
            counter = -1;
            score = 0;
            numberOfLives = 3;
            sound.tones(Sounds::Title);
            [[fallthrough]]

        case GameState::Title:

            title();
            break;

        case GameState::PlayGame_Init:

            playGame_Init();
            [[fallthrough]]

        case GameState::PlayGame:

            playGame();

            if (frameRate != 50 + (score / 8)) {
                frameRate = 50 + (score / 8);
                arduboy.setFrameRate(frameRate);
            }
            break;

    }


    arduboy.displayClearToWhite();

}

