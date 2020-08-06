#pragma once

#include <Arduboy2.h>
#include "../images/Images.h"
#include "../utils/Consts.h"
#include "Explosion.h"

struct Explosions {

    private:

        Explosion explosion[60];

    public:

        void setExplosions(uint8_t x, uint8_t y) {

            for (uint8_t i = 0; i < 60; i++) {

                this->explosion[i].setX(x + ((i / 10) - 3));
                this->explosion[i].setY(y + ((i / 10) - 3));
                this->explosion[i].setCounter(-random(0, 30));
                this->explosion[i].setDirection(random(0, 16));
                
            }

        }

        void update(bool altFrame) {

            for (uint8_t i = 0; i < 60; i++) {

                this->explosion[i].update(altFrame);
                
            }

        }

        Explosion & getExplosion(uint8_t index) {

            return this->explosion[index];

        }

};