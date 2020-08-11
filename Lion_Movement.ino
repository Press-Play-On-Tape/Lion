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

                            changeLevel(thisLion, otherLion, Direction::Right);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {

                            changeOneLevel(thisLion, otherLion, Direction::Right);

                        }
                        else {

                            thisLion.decXPosition();

                        }

                    }
                    break;

                case XPosition::LH_Position4:

                    if (player1.getYPosition() == thisLion.getYPosition()) {

                        bool rnd = (random(0, 3) == 0);

                        if (otherLion.getXPosition() >= XPosition::Centre && !otherLion.isMovingUpDown() && rnd) {

                            changeLevel(thisLion, otherLion, Direction::Right);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {

                            changeOneLevel(thisLion, otherLion, Direction::Right);

                        }
                        else {

                            thisLion.decXPosition();
                            increaseScore();

                        }

                    }
                    else {

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

                    lionAttacking = Direction::Left;
                    lionAttackingIndex = thisLion.getIndex();

                    if (!thisLion.getRunning()) {

                        player1.setRunning(true, thisLion.getXPosition());
                        chair.setPosition(player1.getXDisplay() + 14, player1.getYDisplay() + 2, Direction::Left);
                        thisLion.setRunning(true);
                        die();

                    }

                    break;

                default:

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

                        if (rnd && ((thisLionX - otherLionX < -3 && otherLion.getDirection() == Direction::Left) ||
                                    (thisLionX - otherLionX < -5 && otherLion.getDirection() == Direction::Right))) {

                            changeLevel(thisLion, otherLion, Direction::Left);

                        }
                        else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {

                            changeOneLevel(thisLion, otherLion, Direction::Left);

                        }
                        else {

                            thisLion.incXPosition();

                        }

                    }
                    break;

                case XPosition::RH_Position4:
                    {
                        bool rnd = (random(0, 3) == 0);

                        if (gameMode == GameMode::Normal) {

                            if (player2.getYPosition() == thisLion.getYPosition()) {

                                

                                if (otherLion.getXPosition() <= XPosition::Centre && !otherLion.isMovingUpDown() && rnd) {

                                    changeLevel(thisLion, otherLion, Direction::Left);

                                }
                                else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {

                                    changeOneLevel(thisLion, otherLion, Direction::Left);

                                }
                                else {

                                    thisLion.incXPosition();
                                    increaseScore();

                                }

                            }
                            else {

                                thisLion.incXPosition();

                            }

                        }
                        else {

                            if (otherLion.getXPosition() <= XPosition::Centre && !otherLion.isMovingUpDown() && rnd) {

                                changeLevel(thisLion, otherLion, Direction::Left);

                            }
                            else if (otherLion.getYPosition() != YPosition::Level_2 && !otherLion.isMovingUpDown() && rnd) {

                                changeOneLevel(thisLion, otherLion, Direction::Left);

                            }
                            else {

                                thisLion.decXPosition();
                                thisLion.setDirection(Direction::Left);

                            }

                        }

                    }

                    break;

                case XPosition::RH_Attack: 

                    if (player2.getYPosition() == thisLion.getYPosition() && random(0, 2) == 0) {

                        thisLion.decXPosition();
                        thisLion.setDirection(Direction::Left);

                    }
                    else {

                        thisLion.incXPosition();

                    }

                    break;

                case XPosition::RH_Attack_OutofCage: 

                    if (player2.getYPosition() == thisLion.getYPosition()) {

                        thisLion.decXPosition();
                        thisLion.setDirection(Direction::Left);

                    }
                    else {

                        thisLion.incXPosition();

                    }

                    break;

                case XPosition::RH_Attacking:

                    if (player2.getYPosition() < thisLion.getYPosition()) {

                        thisLion.setXPosition(XPosition::RH_Attacking_Up);

                    }
                    else if (player2.getYPosition() > thisLion.getYPosition()) {

                        thisLion.setXPosition(XPosition::RH_Attacking_Down);

                    }
                    else {

                        thisLion.setXPosition(XPosition::RH_Attacking_Left);

                    }

                    break;

                case XPosition::RH_Attacking_Up:
                case XPosition::RH_Attacking_Down:
                case XPosition::RH_Attacking_Left:

                    lionAttacking = Direction::Right;
                    lionAttackingIndex = thisLion.getIndex();

                    if (!thisLion.getRunning()) {

                        player2.setRunning(true, thisLion.getXPosition());
                        chair.setPosition(player2.getXDisplay(), player2.getYDisplay() + 2, Direction::Right);
                        thisLion.setRunning(true);
                        die();

                    }

                    break;

                default:

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

            thisLion.setDirection(Direction::Down);

            switch (otherLion.getYPosition()) {

                case YPosition::Level_1:
                case YPosition::Level_3:

                    thisLion.setSteps(3);
                    break;

                case YPosition::Level_2:

                    thisLion.setSteps(6);
                    break;

            }

            break;

        case YPosition::Level_2:

            thisLion.setSteps(3);

            switch (otherLion.getYPosition()) {

                case YPosition::Level_1:
                case YPosition::Level_2:

                    thisLion.setDirection(Direction::Down);
                    break;

                case YPosition::Level_3:

                    thisLion.setDirection(Direction::Up);
                    break;

            }

            break;

        case YPosition::Level_3:

            thisLion.setDirection(Direction::Up);

            switch (otherLion.getYPosition()) {

                case YPosition::Level_1:
                case YPosition::Level_3:

                    thisLion.setSteps(3);
                    break;

                case YPosition::Level_2:

                    thisLion.setSteps(6);
                    break;

            }

            break;

    }

    thisLion.setNextDirection(newDirection);

}

void changeOneLevel(Lion &thisLion, Lion &otherLion, Direction newDirection) {

    thisLion.setSteps(3);
    thisLion.setNextDirection(newDirection);

    if (thisLion.getYPosition() == YPosition::Level_2) {

        thisLion.setDirection(otherLion.getYPosition() == YPosition::Level_1 ? Direction::Down : Direction::Up);

    }
    else {

        thisLion.setDirection(thisLion.getYPosition() == YPosition::Level_1 ? Direction::Down : Direction::Up);

    }

}

void increaseScore() {

    sound.tones(Sounds::LionBlocked);
    arduboy.setRGBled(GREEN_LED, Constants::LED_Brightness);
    ledDelay = Constants::Led_Delay;
    score++;

}

void die() {

    sound.tones(Sounds::LionEscaped);
    arduboy.setRGBled(GREEN_LED, Constants::LED_Brightness);
    ledDelay = Constants::Led_Delay;
    numberOfLives--;

}