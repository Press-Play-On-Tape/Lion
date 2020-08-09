#include <Arduboy2.h>

void playGame_Init() {

    lifeReset();

    arduboy.setFrameRate(50);
    
    gameState = GameState::PlayGame;
    frameRate = 50;
    frameRate = 50;
    counter = 159;

}

void lifeReset() {

    explosionSet = false;
    explosions.reset();

    lionAttacking = Direction::None;
    lionAttackingIndex = 0;

    player1.reset(Constants::Player1_Index, Constants::Player1_YPos); 
    player2.reset(Constants::Player2_Index, Constants::Player2_YPos); 

    lion1.reset(Direction::Left, YPosition::Level_1, 8, Constants::Lion1_Index);
    lion2.reset(Direction::Right, YPosition::Level_3, 8, Constants::Lion2_Index);

}

void playGame(void) {


    // --------------------------------------------------------------------------
    //  Update entity positions ..

    if (counter > 0) counter--;


    // Handle explosion (if one is happening) ..

    bool finished = explosions.update(arduboy.everyXFrames(2));


    // Return to main menu ..

    if (numberOfLives == 0 && finished && lionAttacking != Direction::None) {

        if (arduboy.pressed(A_BUTTON))              { gameState = GameState::Title_Init; }

    }


    // Update player positions ..

    if (counter == 0 && lionAttacking == Direction::None && arduboy.everyXFrames(4)) {

        if (arduboy.pressed(A_BUTTON))              { player2.incYPosition(); }
        if (arduboy.pressed(B_BUTTON))              { player2.decYPosition(); }

        if (arduboy.pressed(UP_BUTTON))             { player1.decYPosition(); }
        if (arduboy.pressed(DOWN_BUTTON))           { player1.incYPosition(); }

    }


    // Handle lion movements ..

    if (counter == 0 && (lionAttacking == Direction::None || lionAttackingIndex == Constants::Lion1_Index) && arduboy.everyXFrames(lion1.getSpeed()))     moveLion(lion1, lion2);
    if (counter == 0 && (lionAttacking == Direction::None || lionAttackingIndex == Constants::Lion2_Index) && arduboy.everyXFrames(lion2.getSpeed()))     moveLion(lion2, lion1);


    // --------------------------------------------------------------------------
    //  Render the screen ..

    renderBackground();



    // Lions ..

    Sprites::drawExternalMask(lion1.getXDisplay(), lion1.getYDisplay(), Images::Lion, Images::Lion_Mask, lion1.getFrame(), lion1.getFrame());
    Sprites::drawExternalMask(lion2.getXDisplay(), lion2.getYDisplay(), Images::Lion, Images::Lion_Mask, lion2.getFrame(), lion2.getFrame());


    // Player ..

    uint8_t player01Frame = 0;
    uint8_t player02Frame = 0;

    if (arduboy.frameCount % 8 < 4) {

        XPosition lion1X = lion1.getXPosition();
        YPosition lion1Y = lion1.getYPosition();
        XPosition lion2X = lion2.getXPosition();
        YPosition lion2Y = lion2.getYPosition();

        {
            YPosition player1Y = player1.getYPosition();
            player01Frame = ((player1Y == lion1Y && lion1X <= XPosition::LH_Attack) || (player1Y == lion2Y && lion2X <= XPosition::LH_Attack));
        }

        {
            YPosition player2Y = player2.getYPosition();
            player02Frame = ((player2Y == lion1Y && lion1X >= XPosition::RH_Attack) || (player2Y == lion2Y && lion2X >= XPosition::RH_Attack));

        }

    }

    if ((lionAttacking == Direction::Left && explosions.getCounter() > 0) || lionAttacking != Direction::Left) {
        Sprites::drawExternalMask(player1.getXDisplay(), player1.getYDisplay(), Images::Player_01, Images::Player_01_Mask, player01Frame, player01Frame);
    }

    if ((lionAttacking == Direction::Right && explosions.getCounter() > 0) || lionAttacking != Direction::Right) {
        Sprites::drawExternalMask(player2.getXDisplay(), player2.getYDisplay(), Images::Player_02, Images::Player_02_Mask, player02Frame, player02Frame);
    }

    if (!renderExplosion()) {

        renderScoreBoards(score, numberOfLives);
        
    }


    // Is the game over ?

    if (finished && lionAttacking != Direction::None) {

        if (numberOfLives == 0) {
    
            Sprites::drawExternalMask(24, 21, Images::GameOver, Images::GameOver_Mask, 0, 0);

        }
        else {
            
            lifeReset();
            counter = 159;            

        }

    }


    // Render counter?
    {
        uint8_t frame = 255;

        switch (counter) {

            case 5 ... 39:
                frame = 3;
                break;

            case 45 ... 79:
                frame = 2;
                break;

            case 85 ... 119:
                frame = 1;
                break;

            case 125 ... 159:
                frame = 0;
                break;

            default: break;

        }
     
        if (frame != 255) {
            Sprites::drawExternalMask(52, 21, Images::Count, Images::Count_Mask, frame, 0);
        }

    }

}
