#include <Arduboy2.h>

void drawCage() {

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

void drawVerticalDottedLine(uint8_t x, uint8_t y1, uint8_t y2, uint8_t colour) {

	uint8_t diff = (y2 - y1);

	for (uint8_t y = 0; y <= diff; y += 2) {

		arduboy.drawPixel(x, y1 + y, colour);

    }

}

void renderScoreBoard(Player &player) {

    Sprites::drawOverwrite(player.getIndex() == Constants::Player1_Index ? 0 : 115, 57, Images::Scoreboard, 0);
    font3x5.setCursor(player.getIndex() == Constants::Player1_Index ? 1 : 116, 57);
    if (player.getScore() < 100) font3x5.print(F("0"));
    if (player.getScore() < 10)  font3x5.print(F("0"));
    font3x5.print(player.getScore());

}