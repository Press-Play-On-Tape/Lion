#include <Arduboy2.h>


void playGame(void) {

    // Handle player movements ..

    if (lionAttacking == Direction::None && arduboy.everyXFrames(4)) {

        if (arduboy.pressed(A_BUTTON))              { player2.decYPosition(); }
        if (arduboy.pressed(B_BUTTON))              { player2.incYPosition(); }

        if (arduboy.pressed(UP_BUTTON))             { player1.decYPosition(); }
        if (arduboy.pressed(DOWN_BUTTON))           { player1.incYPosition(); }

    }

    if ((lionAttacking == Direction::None || lionAttackingIndex == Constants::Lion1_Index) && arduboy.everyXFrames(lion1.getSpeed()))     moveLion(lion1, lion2);
    if ((lionAttacking == Direction::None || lionAttackingIndex == Constants::Lion2_Index) && arduboy.everyXFrames(lion2.getSpeed()))     moveLion(lion2, lion1);

    explosions.update(arduboy.everyXFrames(2));

    Sprites::drawOverwrite(0, 0, Images::Tree_LH, 0);
    Sprites::drawOverwrite(96, 0, Images::Tree_RH, 0);


    Sprites::drawOverwrite(115, 57, Images::Scoreboard, 0);
    renderScoreBoard(player1);
    renderScoreBoard(player2);
    drawCage();

    
    Sprites::drawExternalMask(lion1.getXDisplay(), lion1.getYDisplay(), Images::Lion, Images::Lion_Mask, lion1.getFrame(), lion1.getFrame());
    Sprites::drawExternalMask(lion2.getXDisplay(), lion2.getYDisplay(), Images::Lion, Images::Lion_Mask, lion2.getFrame(), lion2.getFrame());

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


    if (lionAttacking == Direction::Left && explosions.getCounter() > 0 || lionAttacking != Direction::Left) {
        Sprites::drawExternalMask(player1.getXDisplay(), player1.getYDisplay(), Images::Player_01, Images::Player_01_Mask, player01Frame, player01Frame);
    }

    if (lionAttacking == Direction::Right && explosions.getCounter() > 0 || lionAttacking != Direction::Right) {
        Sprites::drawExternalMask(player2.getXDisplay(), player2.getYDisplay(), Images::Player_02, Images::Player_02_Mask, player02Frame, player02Frame);
    }


    for (uint8_t i= 0; i < 60; i++) {

        Explosion explosion = explosions.getExplosion(i);
        
        if (explosion.render()) {
            Sprites::drawExternalMask(explosion.getX(), explosion.getY(), Images::Pixel, Images::Pixel_Mask, 0, 0);
        }

    }

    switch (explosions.getCounter()) {

        case 15 ... 16:
        case 11 ... 12:
            Sprites::drawExternalMask(explosions.getX(), explosions.getY(), Images::Scrap, Images::Scrap_Mask, 0, 0);
            break;

        case 13 ... 14:
        case 9 ... 10:
            Sprites::drawExternalMask(explosions.getX(), explosions.getY(), Images::Scrap, Images::Scrap_Mask, 1, 1);
            break;

        case 7 ... 8:
        case 3 ... 4:
            Sprites::drawExternalMask(explosions.getX(), explosions.getY(), Images::Scrap, Images::Scrap_Mask, 2, 2);
            break;

        case 5 ... 6:
        case 1 ... 2:
            Sprites::drawExternalMask(explosions.getX(), explosions.getY(), Images::Scrap, Images::Scrap_Mask, 3, 3);
            break;

    }

}
