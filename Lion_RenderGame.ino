
void renderBackground() {

    Sprites::drawOverwrite(0, 0, Images::Tree_LH, 0);
    Sprites::drawOverwrite(96, 0, Images::Tree_RH, 0);

}

void renderCage() {

    arduboy.drawFastHLine(36, 0, 55);
    arduboy.drawFastHLine(36, 21, 55);
    arduboy.drawFastHLine(36, 42, 55);
    arduboy.drawFastHLine(36, 63, 55);

    arduboy.drawFastVLine(36, 0, 3);
    arduboy.drawFastVLine(36, 19, 5);
    arduboy.drawFastVLine(36, 40, 5);
    arduboy.drawFastVLine(36, 61, 3);

    arduboy.drawFastVLine(90, 0, 3);
    arduboy.drawFastVLine(90, 19, 5);
    arduboy.drawFastVLine(90, 40, 5);
    arduboy.drawFastVLine(90, 61, 3);

    drawVerticalDottedLine(45, 0, 64, 1);
    drawVerticalDottedLine(54, 0, 64, 1);
    drawVerticalDottedLine(63, 0, 64, 1);
    drawVerticalDottedLine(72, 0, 64, 1);
    drawVerticalDottedLine(81, 0, 64, 1);

}

void renderScoreBoard(Player &player) {

    Sprites::drawOverwrite(player.getIndex() == Constants::Player1_Index ? -1 : 114, 56, Images::Scoreboard, 0);

    font3x5.setCursor(player.getIndex() == Constants::Player1_Index ? 1 : 116, 57);
    if (player.getScore() < 100) font3x5.print(F("0"));
    if (player.getScore() < 10)  font3x5.print(F("0"));
    font3x5.print(player.getScore());

}

void renderExplosion() {

    for (uint8_t i= 0; i < 60; i++) {

        Explosion explosion = explosions.getExplosion(i);
        
        if (explosion.render()) {
            Sprites::drawExternalMask(explosion.getX(), explosion.getY(), Images::Pixel, Images::Pixel_Mask, 0, 0);
        }

    }

    switch (explosions.getCounter()) {

        case 15 ... 16:
        case 11 ... 12:
            Sprites::drawExternalMask(explosions.getX() - 8, explosions.getY() - 8, Images::Scrap, Images::Scrap_Mask, 0, 0);
            break;

        case 13 ... 14:
        case 9 ... 10:
            Sprites::drawExternalMask(explosions.getX() - 8, explosions.getY() - 8, Images::Scrap, Images::Scrap_Mask, 1, 1);
            break;

        case 7 ... 8:
        case 3 ... 4:
            Sprites::drawExternalMask(explosions.getX() - 8, explosions.getY() - 8, Images::Scrap, Images::Scrap_Mask, 2, 2);
            break;

        case 5 ... 6:
        case 1 ... 2:
            Sprites::drawExternalMask(explosions.getX() - 8, explosions.getY() - 8, Images::Scrap, Images::Scrap_Mask, 3, 3);
            break;

    }

}