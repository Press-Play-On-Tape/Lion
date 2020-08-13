#include <Arduboy2.h>

void title() {

    if (counter >= 0) counter++;
    if (soundCounter > 0) soundCounter--;
    marqueeCounter++; 
    if (marqueeCounter == 195) marqueeCounter = 0;

    Sprites::drawOverwrite(0, 0, Images::Title_LionTop, 0);

    if (arduboy.justPressed(A_BUTTON)) { 

        gameMode = GameMode::Easy;
        
        if (counter == -1) {

            counter = 0;
            #ifdef SOUNDS
            sound.tones(Sounds::Roar);
            #endif

        }
        else {

            gameState = GameState::Instructions_Init;

        }

    }

    if (arduboy.justPressed(B_BUTTON)) { 
        
        gameMode = GameMode::Normal;

        if (counter == -1) {

            counter = 0;
            #ifdef SOUNDS
            sound.tones(Sounds::Roar);
            #endif

        }
        else {

            gameState = GameState::Instructions_Init;

        }

    }

    if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON)) {

        sounds = EEPROM_Utils::toggleSoundSettings(arduboy);
        soundCounter = 16;
        
    }

    switch (counter) {

        case -1:
            drawElements(true, 0);
            break;

        case 0 ... 9:
            drawElements(false, 0);
            break;

        case 10:
            explosions.setExplosions(35, 35);
            drawElements(true, 1);
            break;

        case 11 ... 120:
            drawElements(false, 1);
            Sprites::drawOverwrite(52 + ((counter % 3) - 1), 6 + ((counter % 3) - 1), Images::Roar, 0);
            break;

        case 121 ... 130:
            drawElements(false, 1);
            break;

        case 131:
            drawElements(true, 0);
            gameState = GameState::Instructions_Init;
            break;

    }

    if (counter < 0) {

        switch (marqueeCounter) {

            case 0 ... 14:
            case 65 ... 79:
            case 130 ... 144:
                break;

            case 15 ... 64:
                Sprites::drawOverwrite(73, 54, Images::Mode, 0);
                break;

            case 80 ... 129:
                Sprites::drawOverwrite(73, 54, Images::Mode, 1);
                break;

            case 145 ... 194:
                {

                    uint8_t digits[3] = {};
                    extractDigits(digits, score);
                    Sprites::drawOverwrite(72, 54, Images::Hard, 0);
                    
                    for (uint8_t i = 3, x = 88; i > 0; i--, x = x + 4) {

                        Sprites::drawErase(x, 54, Images::Font, digits[i - 1]);

                    }

                }
                break;

        }

    }

    if (soundCounter > 0) {

        Sprites::drawOverwrite(119, 55, Images::Sound, !sounds);

    }


    // Render roar ..

    for (uint8_t i = 0; i < Constants::Particle_Count; i++) {

        Explosion explosion = explosions.getExplosion(i);

        if (explosion.getCounter() > 0) {
            Sprites::drawExternalMask(explosion.getX() + 1, explosion.getY(), Images::Pixel, Images::Pixel_Mask, 0, 0);
        }

    }

    explosions.update(arduboy.frameCount);

}

void drawElements(bool title, uint8_t lionFrame) {

    if (title) Sprites::drawOverwrite(50, 10, Images::Title, 0);
    Sprites::drawOverwrite(0, 32, Images::Title_Lion_Bottom, lionFrame);

}
