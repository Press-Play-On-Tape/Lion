#include "src/utils/Arduboy2Ext.h"
#include <ArduboyTones.h>
#include "src/images/Images.h"
#include "src/utils/Consts.h"
#include "src/utils/EEPROM_Utils.h"
#include "src/entities/Entities.h"
#include "src/sounds/Sounds.h"

Arduboy2Ext arduboy;
ArduboyTones sound(arduboy.audio.enabled);

Player player1;
Player player2;
Lion lion1;
Lion lion2;
Explosions explosions;
Chair chair;

Direction lionAttacking = Direction::None;
uint8_t lionAttackingIndex = 0;

#ifdef SPLASH
GameState gameState = GameState::Splash_Init;
#else
GameState gameState = GameState::Title_Init;
#endif

GameMode gameMode = GameMode::Easy;

uint8_t frameRate = 50;
int16_t counter = 10;
uint16_t score = 0;
uint8_t numberOfLives = 3;
uint8_t ledDelay = 0;
uint8_t marqueeCounter = 0;
uint8_t soundCounter = 0;

bool gameOver = false;
bool sounds = arduboy.audio.enabled();


void setup(void) {

	arduboy.boot();
	arduboy.flashlight();
	arduboy.systemButtons();
	arduboy.audio.begin();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(40);
    arduboy.setRGBled(0, 0, 0);

    EEPROM_Utils::initEEPROM();
	
}

void loop(void) {

	if (!arduboy.nextFrame()) return;

	arduboy.pollButtons();

    switch (gameState) {

        #ifdef SPLASH

            case GameState::Splash_Init:

                splashScreen_Init();
                gameState = GameState::Splash;
                [[fallthrough]]

            case GameState::Splash:

                splashScreen();
                arduboy.display();
                break;
        #endif

        case GameState::Instructions_Init:
            instructions_Init();
            gameState = GameState::Instructions;
            [[fallthrough]]

        case GameState::Instructions:
            instructions();
            arduboy.displayClearToWhite();
            break;

        case GameState::Title_Init:

            gameState = GameState::Title;
            counter = -1;
            marqueeCounter = 0;
            soundCounter = 0;
            score = 0;
            numberOfLives = 3;
            gameOver = false;
            arduboy.setFrameRate(40);

            #ifdef SOUNDS
            sound.tones(Sounds::Title);
            #endif
            explosions.reset();
            score = EEPROM_Utils::getScore();
            [[fallthrough]]

        case GameState::Title:

            title();
            arduboy.displayClearToWhite();
            break;

        case GameState::PlayGame_Init:

            playGame_Init();
            [[fallthrough]]

        case GameState::PlayGame:

            playGame();

            if (frameRate != 40 + (score / 8)) {
                frameRate = 40 + (score / 8);
                arduboy.setFrameRate(frameRate);
            }
            arduboy.displayClearToWhite();
            break;

    }


}

