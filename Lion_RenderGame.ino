#include <Arduboy2.h>

void renderBackground() {

    Sprites::drawOverwrite(0, 0, Images::Scenery_LH, 0);
    Sprites::drawOverwrite(106, 0, Images::Scenery_RH, 0);
    Sprites::drawOverwrite(27, 0 , Images::Cage, 0);

}

void renderScoreBoards(uint16_t score, uint8_t numberOfLives) {

    Sprites::drawOverwrite(-1, 56, Images::Scoreboard_LH, 0);
    Sprites::drawOverwrite(114, 56, Images::Scoreboard_RH, 0);

    uint8_t digits[3] = {};
    extractDigits(digits, score);
    
    for (uint8_t i = 3, x = 1; i > 0; i--, x = x + 4) {

        Sprites::drawErase(x, 58, Images::Font, digits[i - 1]);

    }

    for (uint8_t x = 126, y = numberOfLives; y > 0; x = x - 2, y--) {

        arduboy.drawFastVLine(x, 58, 5, BLACK);

    }

}

bool renderExplosion() {

    const uint8_t frame[] = { 0, 3, 3, 2, 2, 3, 3, 2, 2, 1, 1, 0, 0, 1, 1, 0, 0 };

    bool anythingRendered = false;
    uint8_t counter = explosions.getCounter();

    for (uint8_t i= 0; i < 60; i++) {

        Explosion explosion = explosions.getExplosion(i);
        
        if (explosion.render()) {
//            arduboy.drawPixel(explosion.getX() + 1, explosion.getY() + 1, BLACK);
//            Sprites::drawExternalMask(explosion.getX(), explosion.getY(), Images::Pixel, Images::Pixel_Mask, 0, 0);
            Sprites::drawExternalMask(explosion.getX() + 1, explosion.getY(), Images::Pixel, Images::Pixel_Mask, 0, 0);
            anythingRendered = true;
        }

    }

    if (counter > 0 && counter <= 16)  {

        Sprites::drawExternalMask(explosions.getX() - 8, explosions.getY() - 8, Images::Scrap, Images::Scrap_Mask, frame[counter], frame[counter]);
        anythingRendered = true;

    }

    return anythingRendered;

}