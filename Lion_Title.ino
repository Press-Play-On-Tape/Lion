#include <Arduboy2.h>

void title() {

    if (counter >= 0) counter++;

    #ifdef SOUNDS
        if (soundCounter > 0) soundCounter--;
    #endif

    #ifdef THREE_IMAGES
        marqueeCounter++; 
        if (marqueeCounter == 195) marqueeCounter = 0;
    #else
        marqueeCounter++; 
        if (marqueeCounter == 166) marqueeCounter = 0;
    #endif

    Sprites::drawOverwrite(0, 0, Images::Title_LionTop, 0);

    if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) { 

        gameMode = arduboy.justPressed(A_BUTTON) ? GameMode::Easy : GameMode::Hard;

        #ifdef SHOW_ROAR
            
            if (counter == -1) {

                #ifdef SOUNDS
                    sound.noTone();
                #endif
                counter = 0;
                
                #ifdef SOUNDS
                    soundVars.reset();
                #endif

            }
            else {

                #ifdef SHOW_INSTUCTIONS
                    gameState = GameState::Instructions_Init;
                #else
                    gameState = GameState::PlayGame_Init;
                #endif

            }

        #else

            #ifdef SHOW_INSTUCTIONS
                gameState = GameState::Instructions_Init;
            #else
                gameState = GameState::PlayGame_Init;
            #endif

            counter = 131;

        #endif

    }

    #ifdef SOUNDS
        if (arduboy.justPressed(UP_BUTTON) || arduboy.justPressed(DOWN_BUTTON)) {

            sounds = EEPROM_Utils::toggleSoundSettings(arduboy);
            soundCounter = 16;
            
        }
    #endif

    #ifdef SHOW_ROAR

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

            case 11 ... 61:

                #ifdef SOUNDS
                    makeRoar();
                #endif

                drawElements(false, 1);
                Sprites::drawOverwrite(52 + ((counter % 3) - 1), 6 + ((counter % 3) - 1), Images::Roar, 0);
                break;

            case 62:

                #ifdef SOUNDS
                    beep.noTone();
                #endif

                drawElements(false, 1);
                Sprites::drawOverwrite(52 + ((counter % 3) - 1), 6 + ((counter % 3) - 1), Images::Roar, 0);
                break;

            case 63 ... 120:
                drawElements(false, 1);
                Sprites::drawOverwrite(52 + ((counter % 3) - 1), 6 + ((counter % 3) - 1), Images::Roar, 0);
                break;

            case 121 ... 130:
                drawElements(false, 1);
                break;

            case 131:
                drawElements(true, 0);
                #ifdef SHOW_INSTUCTIONS
                    gameState = GameState::Instructions_Init;
                #else
                    gameState = GameState::PlayGame_Init;
                #endif
                break;

        }

    #else
        drawElements(true, 0);
    #endif

    if (counter < 0) {

        #ifdef THREE_IMAGES

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

        #else

            switch (marqueeCounter) {

                case 0 ... 14:
                case 85 ... 99:
                    break;

                case 15 ... 84:
                    Sprites::drawOverwrite(59, 54, Images::Mode, 0);
                    Sprites::drawOverwrite(88, 54, Images::Mode, 1);
                    break;

                case 100 ... 165:
                    {

                        uint8_t digits[3] = {};
                        Sprites::drawOverwrite(64, 54, Images::High, 0);
                        
                        extractDigits(digits, EEPROM_Utils::getScore(GameMode::Easy));
                        for (uint8_t i = 3, x = 81; i > 0; i--, x = x + 4) {

                            Sprites::drawErase(x, 54, Images::Font, digits[i - 1]);

                        }
                        
                        extractDigits(digits, EEPROM_Utils::getScore(GameMode::Hard));
                        for (uint8_t i = 3, x = 96; i > 0; i--, x = x + 4) {

                            Sprites::drawErase(x, 54, Images::Font, digits[i - 1]);

                        }

                    }
                    break;

            }

        #endif

    }

    #ifdef SOUNDS

        if (soundCounter > 0) {
            Sprites::drawOverwrite(119, 55, Images::Sound, !sounds);
        }

    #endif


    // Render roar ..

    #ifdef SHOW_ROAR

        for (uint8_t i = 0; i < Constants::Particle_Count; i++) {

            Explosion explosion = explosions.getExplosion(i);

            if (explosion.getCounter() > 0) {
                Sprites::drawExternalMask(explosion.getX() + 1, explosion.getY(), Images::Pixel, Images::Pixel_Mask, 0, 0);
            }

        }

        explosions.update(arduboy.frameCount);

    #endif

}

void drawElements(bool title, uint8_t lionFrame) {

    if (title) Sprites::drawOverwrite(50, 10, Images::Title, 0);
    Sprites::drawOverwrite(0, 32, Images::Title_Lion_Bottom, lionFrame);

}

#ifdef SHOW_ROAR
#ifdef SOUNDS

    void makeRoar() {

        beep.tone(soundVars.note, 5);
        //delay(soundVars.duration);
        //beep.noTone();
        //delay(soundVars.duration/3);

        soundVars.note += soundVars.delta;

        if (soundVars.note == soundVars.minimum) {

            soundVars.delta = -soundVars.delta; 
            soundVars.duration = 44; 
            soundVars.up = true; 
            soundVars.down = false;
        }
        else if (soundVars.note == soundVars.maximum) {
            
            soundVars.delta = -soundVars.delta; 
            soundVars.down = true; 
            soundVars.up = false;
            
        }

        if (soundVars.up) soundVars.duration -= 2;
        else if (soundVars.down) soundVars.duration += 2;

    }

#endif
#endif