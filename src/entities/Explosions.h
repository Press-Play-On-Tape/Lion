#pragma once

#include <Arduboy2.h>
#include "../images/Images.h"
#include "../utils/Consts.h"
#include "Explosion.h"

struct Explosions {

    private:

        Explosion explosion[60];
        uint8_t counter = 0;
        int16_t x = 0;
        int16_t y = 0;

    public:

        int16_t getX()                              { return this->x; }
        int16_t getY()                              { return this->y; }
        uint8_t getCounter()                        { return this->counter; }

        void setX(int16_t val)                      { this->x = val; }
        void setY(int16_t val)                      { this->y = val; }
        void setCounter(uint8_t val)                { this->counter = val; }


    public:

        void setExplosions(uint8_t x, uint8_t y) {

            this->counter = 17;
            this->x = x;
            this->y = y;

            for (uint8_t i = 0; i < 60; i++) {

                this->explosion[i].setX(x + ((i / 10) - 3));
                this->explosion[i].setY(y + ((i / 10) - 3));
                this->explosion[i].setCounter(-random(30, 60));
                this->explosion[i].setDirection(random(0, 16));
                
            }

        }

        void update(bool altFrame) {

            for (uint8_t i = 0; i < 60; i++) {

                this->explosion[i].update(altFrame);
                
            }

            if (this->counter > 0) this->counter--;

        }

        Explosion & getExplosion(uint8_t index) {

            return this->explosion[index];

        }



};