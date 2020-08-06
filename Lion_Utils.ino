#include <Arduboy2.h>


void drawVerticalDottedLine(uint8_t x, uint8_t y1, uint8_t y2, uint8_t colour) {

	uint8_t diff = (y2 - y1);

	for (uint8_t y = 0; y <= diff; y += 2) {

		arduboy.drawPixel(x, y1 + y, colour);

    }

}
