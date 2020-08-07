#include <Arduboy2.h>

void title() {

    counter++;
    if (counter == 176) counter = 0;

    if (arduboy.justPressed(A_BUTTON)) { gameMode = GameMode::TwoPlayer; gameState = GameState::PlayGame_Init; }
    if (arduboy.justPressed(B_BUTTON)) { gameMode = GameMode::OnePlayer; gameState = GameState::PlayGame_Init; }

    Sprites::drawOverwrite(0, 0, Images::Title, 0);

    switch (counter) {

        case 0 ... 63:
            Sprites::drawOverwrite(74, 45, Images::Players, 0);
            break;

        case 64 ... 87:
            break;

        case 88 ... 151:
            Sprites::drawOverwrite(74, 45, Images::Players, 1);
            break;

        case 152 ... 175:
            break;

    }

}