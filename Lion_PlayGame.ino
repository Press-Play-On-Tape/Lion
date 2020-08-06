#include <Arduboy2.h>

void playGame_Init() {

    player1.reset(Constants::Player1_Index, Constants::Player1_XPos, Constants::Player1_YPos); 
    player2.reset(Constants::Player2_Index, Constants::Player2_XPos, Constants::Player2_YPos); 

    lion1.reset(Direction::Left, YPosition::Level_1, 8, Constants::Lion1_Index);
    lion2.reset(Direction::Right, YPosition::Level_2, 8, Constants::Lion2_Index);

    explosions.reset();
    arduboy.setFrameRate(50);
    
    gameState = GameState::PlayGame;
    frameRate = 50;
    explosionSet = false;
    lionAttacking = Direction::None;
    lionAttackingIndex = 0;
    frameRate = 50;

}

void playGame(void) {


    // --------------------------------------------------------------------------
    //  Update entity positions ..


    // Handle explosion (if one is happening) ..

    bool finished = explosions.update(arduboy.everyXFrames(2));


    // Return to main menu ..

    if (finished && lionAttacking != Direction::None) {

        if (arduboy.pressed(A_BUTTON))              { gameState = GameState::Title_Init; }

    }


    // Update player positions ..

    if (lionAttacking == Direction::None && arduboy.everyXFrames(4)) {

        if (arduboy.pressed(A_BUTTON))              { player2.decYPosition(); }
        if (arduboy.pressed(B_BUTTON))              { player2.incYPosition(); }

        if (arduboy.pressed(UP_BUTTON))             { player1.decYPosition(); }
        if (arduboy.pressed(DOWN_BUTTON))           { player1.incYPosition(); }

    }


    // Handle lion movements ..

    if ((lionAttacking == Direction::None || lionAttackingIndex == Constants::Lion1_Index) && arduboy.everyXFrames(lion1.getSpeed()))     moveLion(lion1, lion2);
    if ((lionAttacking == Direction::None || lionAttackingIndex == Constants::Lion2_Index) && arduboy.everyXFrames(lion2.getSpeed()))     moveLion(lion2, lion1);


    // --------------------------------------------------------------------------
    //  Render the screen ..

    renderBackground();
    renderCage();
    
    // Lions ..

    Sprites::drawExternalMask(lion1.getXDisplay(), lion1.getYDisplay(), Images::Lion, Images::Lion_Mask, lion1.getFrame(), lion1.getFrame());
    Sprites::drawExternalMask(lion2.getXDisplay(), lion2.getYDisplay(), Images::Lion, Images::Lion_Mask, lion2.getFrame(), lion2.getFrame());


    // Player ..

    uint8_t player01Frame = (
        arduboy.frameCount % 8 < 4 && 
        (
            (player1.getYPosition() == lion1.getYPosition() && lion1.getXPosition() <= XPosition::LH_Attack) || 
            (player1.getYPosition() == lion2.getYPosition() && lion2.getXPosition() <= XPosition::LH_Attack)
        )         
        ? 1 : 0);

    uint8_t player02Frame = (
        arduboy.frameCount % 8 < 4 && 
        (
            (player1.getYPosition() == lion1.getYPosition() && lion1.getXPosition() >= XPosition::RH_Attack) || 
            (player1.getYPosition() == lion2.getYPosition() && lion2.getXPosition() >= XPosition::RH_Attack)
        )         
        ? 1 : 0);


    if ((lionAttacking == Direction::Left && explosions.getCounter() > 0) || lionAttacking != Direction::Left) {
        Sprites::drawExternalMask(player1.getXDisplay(), player1.getYDisplay(), Images::Player_01, Images::Player_01_Mask, player01Frame, player01Frame);
    }

    if ((lionAttacking == Direction::Right && explosions.getCounter() > 0) || lionAttacking != Direction::Right) {
        Sprites::drawExternalMask(player2.getXDisplay(), player2.getYDisplay(), Images::Player_02, Images::Player_02_Mask, player02Frame, player02Frame);
    }

    renderExplosion();
    renderScoreBoard(player1);
    renderScoreBoard(player2);


    // Is the game over ?

    if (finished && lionAttacking != Direction::None) {

        Sprites::drawExternalMask(25, 21, Images::GameOver, Images::GameOver_Mask, 0, 0);

    }


}
