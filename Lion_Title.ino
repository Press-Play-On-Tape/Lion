#include <Arduboy2.h>

void title() {

    Sprites::drawOverwrite(0, 0, Images::Title_LionTop, 0);
    counter++;

    if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::PlayGame_Init; }

    switch (counter) {

        case -200 ... 185:
            Sprites::drawOverwrite(50, 12, Images::Title, 0);
            Sprites::drawOverwrite(0, 32, Images::Title_Lion_00, 0);
            break;

        case 186 ... 195:
            Sprites::drawOverwrite(0, 32, Images::Title_Lion_00, 0);
            break;

        case 196:
            explosions.setExplosionsTitle(35, 35);
            Sprites::drawOverwrite(50, 12, Images::Title, 0);
            Sprites::drawOverwrite(0, 32, Images::Title_Lion_01, 0);
            break;

        case 197 ... 320:
            Sprites::drawOverwrite(0, 32, Images::Title_Lion_01, 0);
            Sprites::drawExternalMask(52 + ((counter % 3) - 1), 6 + ((counter % 3) - 1), Images::Roar, Images::Roar_Mask, 0, 0);
            break;

        case 321 ... 330:
            Sprites::drawOverwrite(0, 32, Images::Title_Lion_01, 0);
            break;

        case 331:
            Sprites::drawOverwrite(50, 12, Images::Title, 0);
            Sprites::drawOverwrite(0, 32, Images::Title_Lion_00, 0);
            counter = 0;
            break;

    }


    // Render roar ..

    for (uint8_t i = 0; i < 30; i++) {

        Explosion explosion = explosions.getExplosion(i);
        arduboy.drawPixel(explosion.getX() + 1, explosion.getY() + 1, BLACK);
//        Sprites::drawExternalMask(explosion.getX(), explosion.getY(), Images::Pixel, Images::Pixel_Mask, 0, 0);

    }

    explosions.update(random(0, 2));

}
