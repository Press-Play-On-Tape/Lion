#include <Arduboy2.h>
#include "images/images.h"
#include "utils/consts.h"
#include "entities/player.h"
#include "entities/lion.h"

Arduboy2 arduboy;

Player player1;
Player player2;
Lion lion1;
Lion lion2;

void setup(void) {

	arduboy.boot();
	arduboy.flashlight();
	arduboy.systemButtons();
	arduboy.audio.begin();
	arduboy.initRandomSeed();
	arduboy.setFrameRate(70);

    player1.reset(Constants::Player1_Index, Constants::Player1_XPos, Constants::Player1_YPos); 
    player2.reset(Constants::Player2_Index, Constants::Player2_XPos, Constants::Player2_YPos); 

    lion1.setDirection(Direction::Left);
    lion2.setDirection(Direction::Right);
	
}

void loop(void) {

	if (!arduboy.nextFrame()) return;

	arduboy.pollButtons();
    arduboy.clear();


    // Handle player movements ..

    if (arduboy.everyXFrames(8)) {

        if (arduboy.pressed(A_BUTTON))              { player2.decYPosition(); }
        if (arduboy.pressed(B_BUTTON))              { player2.incYPosition(); }

        if (arduboy.pressed(UP_BUTTON))             { player1.decYPosition(); }
        if (arduboy.pressed(DOWN_BUTTON))           { player1.incYPosition(); }

    }

    if (arduboy.everyXFrames(lion1.getSpeed()))     moveLion(lion1, lion2);
    if (arduboy.everyXFrames(lion2.getSpeed()))     moveLion(lion2, lion1);

    drawCage();

    
    Sprites::drawExternalMask(lion1.getXDisplay(), lion1.getYDisplay(), Images::Lion, Images::Lion_Mask, lion1.getFrame(), lion1.getFrame());
    Sprites::drawExternalMask(lion2.getXDisplay(), lion2.getYDisplay(), Images::Lion, Images::Lion_Mask, lion2.getFrame(), lion2.getFrame());

    Sprites::drawSelfMasked(player1.getXDisplay(), player1.getYDisplay(), Images::Player_01, 0);
    Sprites::drawSelfMasked(player2.getXDisplay(), player2.getYDisplay(), Images::Player_02, 0);


    arduboy.display();

}


void moveLion(Lion &thisLion, Lion &otherLion) {
// Serial.print("Dir ");
// Serial.print((uint8_t)thisLion.getDirection());
// Serial.print(", Pos ");
// Serial.println((uint8_t)thisLion.getXPosition());

    // Handle lion moves ..

    switch (thisLion.getDirection()) {

        case Direction::Up:
        case Direction::Down:
            thisLion.decSteps();
            break;

        case Direction::Left:

            switch (thisLion.getXPosition()) {

                case XPosition::LH_Position3 ... XPosition::LH_Position1:
                    {
                        bool rnd = (random(0, 6) == 0);
                        uint8_t thisLionX = static_cast<uint8_t>(thisLion.getXPosition());
                        uint8_t otherLionX = static_cast<uint8_t>(otherLion.getXPosition());

                        if (rnd && (thisLionX - otherLionX > 3 && otherLion.getDirection() == Direction::Right) ||
                                   (thisLionX - otherLionX > 5 && otherLion.getDirection() == Direction::Left)) {
Serial.println("L1");
                            changeLevel(thisLion, otherLion, Direction::Right);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {
Serial.println("L2");

                            changeOneLevel(thisLion, otherLion, Direction::Right);

                        }
                        else {
// Serial.println("L3");

                            thisLion.decXPosition();

                        }

                    }
                    break;

                case XPosition::LH_Position4:

                    if (player1.getYPosition() == thisLion.getYPosition()) {

                        bool rnd = (random(0, 3) == 0);

                        if (otherLion.getXPosition() >= XPosition::Centre && !otherLion.isMovingUpDown() && rnd) {
Serial.println("L4");

                            changeLevel(thisLion, otherLion, Direction::Right);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {
Serial.println("L5");

                            changeOneLevel(thisLion, otherLion, Direction::Right);

                        }
                        else {
// Serial.println("L6");

                            thisLion.setDirection(Direction::Right);

                        }

                    }
                    else {
// Serial.println("L7");

                        thisLion.decXPosition();

                    }

                    break;

                case XPosition::LH_Attack: 
                    // if (player1.getY() == thisLion.getY()) {
// Serial.println("L8");

                        thisLion.setDirection(Direction::Right);

                    // }

                    break;

                default:
// Serial.println("L9");

                    thisLion.decXPosition();
                    break;

            }

            break;

        case Direction::Right:

            switch (thisLion.getXPosition()) {

                case XPosition::RH_Position1 ... XPosition::RH_Position3:
                    {
                        bool rnd = (random(0, 6) == 0);
                        uint8_t thisLionX = static_cast<uint8_t>(thisLion.getXPosition());
                        uint8_t otherLionX = static_cast<uint8_t>(otherLion.getXPosition());

//                        if (otherLion.getXPosition() <= XPosition::Centre && !otherLion.isMovingUpDown() && rnd) {
                        if (rnd && (otherLionX - thisLionX > 3 && otherLion.getDirection() == Direction::Left) ||
                                   (otherLionX - thisLionX > 5 && otherLion.getDirection() == Direction::Right)) {

Serial.println("R1");

                            changeLevel(thisLion, otherLion, Direction::Left);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {
Serial.println("R2");

                            changeOneLevel(thisLion, otherLion, Direction::Left);

                        }
                        else {
// Serial.println("R3");

                            thisLion.incXPosition();

                        }

                    }
                    break;

                case XPosition::RH_Position4:

                    if (true /*player1.getYPosition() == thisLion.getYPosition()*/) {

                        bool rnd = (random(0, 3) == 0);

                        if (otherLion.getXPosition() <= XPosition::Centre && !otherLion.isMovingUpDown() && rnd) {

Serial.println("R4");
                            changeLevel(thisLion, otherLion, Direction::Left);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {

Serial.println("R5");
                            changeOneLevel(thisLion, otherLion, Direction::Left);

                        }
                        else {

// Serial.println("R6");
                            thisLion.setDirection(Direction::Left);

                        }

                    }
                    else {
// Serial.println("R7");

                        thisLion.incXPosition();

                    }

                    break;

                case XPosition::RH_Attack: 
                    // if (player1.getY() == thisLion.getY()) {
// Serial.println("R8");

                        thisLion.setDirection(Direction::Left);

                    // }

                    break;

                default:
// Serial.println("R9");

                    thisLion.incXPosition();
                    break;

            }

            break;

    }

}

void changeLevel(Lion &thisLion, Lion &otherLion, Direction newDirection) {

    switch (thisLion.getYPosition()) {

        case YPosition::Level_1:

            switch (otherLion.getYPosition()) {

                case YPosition::Level_1:
                case YPosition::Level_3:
// Serial.println("X1");

//                    thisLion.setYPosition(YPosition::Level_2);
                    thisLion.setSteps(3);
                    thisLion.setDirection(Direction::Down);
                    thisLion.setNextDirection(newDirection);
                    break;

                case YPosition::Level_2:
// Serial.println("X2");
//                    thisLion.setYPosition(YPosition::Level_2);
                    thisLion.setSteps(6);
                    thisLion.setDirection(Direction::Down);
                    thisLion.setNextDirection(newDirection);
                    break;

            }

            break;

        case YPosition::Level_2:

            switch (otherLion.getYPosition()) {

                case YPosition::Level_1:
                case YPosition::Level_2:
// Serial.println("X3");
//                    thisLion.setYPosition(YPosition::Level_3);
                    thisLion.setSteps(3);
                    thisLion.setDirection(Direction::Down);
                    thisLion.setNextDirection(newDirection);
                    break;

                case YPosition::Level_3:
// Serial.println("X4");
                    thisLion.setSteps(3);
                    thisLion.setDirection(Direction::Up);
                    thisLion.setNextDirection(newDirection);
                    break;

            }

            break;

        case YPosition::Level_3:

            switch (otherLion.getYPosition()) {

                case YPosition::Level_1:
                case YPosition::Level_3:
// Serial.println("X5");
                    thisLion.setSteps(3);
                    thisLion.setDirection(Direction::Up);
                    thisLion.setNextDirection(newDirection);
                    break;

                case YPosition::Level_2:
// Serial.println("X6");
                    thisLion.setSteps(6);
                    thisLion.setDirection(Direction::Up);
                    thisLion.setNextDirection(newDirection);
                    break;

            }

            break;

    }

}

void changeOneLevel(Lion &thisLion, Lion &otherLion, Direction newDirection) {

    if (thisLion.getYPosition() == YPosition::Level_2) {
// Serial.println("Y1");

        thisLion.setSteps(3);
        thisLion.setDirection(otherLion.getYPosition() == YPosition::Level_1 ? Direction::Down : Direction::Up);
        thisLion.setNextDirection(newDirection);

    }
    else {
// Serial.println("Y2");

        thisLion.setSteps(3);
        thisLion.setDirection(thisLion.getYPosition() == YPosition::Level_1 ? Direction::Down : Direction::Up);
        thisLion.setNextDirection(newDirection);

    }

}