#include <Arduboy2.h>

void moveLion(Lion &thisLion, Lion &otherLion) {

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

                        if (rnd && ((thisLionX - otherLionX > 3 && otherLion.getDirection() == Direction::Right) ||
                                    (thisLionX - otherLionX > 5 && otherLion.getDirection() == Direction::Left))) {
// Serial.println("L1");
                            changeLevel(thisLion, otherLion, Direction::Right);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {
// Serial.println("L2");

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
// Serial.println("L4");

                            changeLevel(thisLion, otherLion, Direction::Right);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {
// Serial.println("L5");

                            changeOneLevel(thisLion, otherLion, Direction::Right);

                        }
                        else {
// Serial.println("L6");

                            //thisLion.setDirection(Direction::Right);
                            thisLion.decXPosition();
                            player1.incScore();

                        }

                    }
                    else {
// Serial.println("L7");

                        thisLion.decXPosition();

                    }

                    break;

                case XPosition::LH_Attack: 

                    if (player1.getYPosition() == thisLion.getYPosition() && random(0, 2) == 0) {

                        thisLion.incXPosition();
                        thisLion.setDirection(Direction::Right);

                    }
                    else {

                        thisLion.decXPosition();

                    }

                    break;

                case XPosition::LH_Attack_OutofCage: 

                    if (player1.getYPosition() == thisLion.getYPosition()) {

                        thisLion.incXPosition();
                        thisLion.setDirection(Direction::Right);

                    }
                    else {

                        thisLion.decXPosition();

                    }

                    break;

                case XPosition::LH_Attacking:

                    lionAttacking = Direction::Left;
                    lionAttackingIndex = thisLion.getIndex();

                    if (player1.getYPosition() < thisLion.getYPosition()) {

                        thisLion.setXPosition(XPosition::LH_Attacking_Up);

                    }
                    else if (player1.getYPosition() > thisLion.getYPosition()) {

                        thisLion.setXPosition(XPosition::LH_Attacking_Down);
                    }
                    else {

                        thisLion.setXPosition(XPosition::LH_Attacking_Left);

                    }

                    break;

                case XPosition::LH_Attacking_Up:
                case XPosition::LH_Attacking_Down:
                case XPosition::LH_Attacking_Left:

                    if (!explosionSet) {

                        uint8_t y = 0;

                        switch (thisLion.getXPosition()) {

                            case XPosition::LH_Attacking_Up:
                                y = player1.getXDisplay() + 8;
                                break;

                            case XPosition::LH_Attacking_Down:
                                y = player1.getXDisplay() - 8;
                                break;

                            case XPosition::LH_Attacking_Left:
                                y = player1.getXDisplay();
                                break;

                            default:    break;

                        }
                        Serial.println(y);
                        thisLion.setXPosition(XPosition::LH_Attacking_Left);
                        explosions.setExplosions(7, y);
                        explosionSet = true;

                    }

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
                        if (rnd && ((otherLionX - thisLionX > 3 && otherLion.getDirection() == Direction::Left) ||
                                    (otherLionX - thisLionX > 5 && otherLion.getDirection() == Direction::Right))) {

// Serial.println("R1");

                            changeLevel(thisLion, otherLion, Direction::Left);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {
// Serial.println("R2");

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

// Serial.println("R4");
                            changeLevel(thisLion, otherLion, Direction::Left);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {

// Serial.println("R5");
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

        default: break;

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