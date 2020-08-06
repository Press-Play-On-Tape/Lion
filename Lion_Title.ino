#include <Arduboy2.h>

void title() {

    if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::PlayGame; }

    Sprites::drawOverwrite(0, 0, Images::Title, 0);

}