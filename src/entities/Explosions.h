#pragma once

#include <Arduboy2.h>
#include "../images/Images.h"
#include "../utils/Consts.h"
#include "Explosion.h"

struct Explosions {

    private:

        bool explosionSet = false;
        Explosion explosion[60];
        uint8_t counter = 0;
        int16_t x = 0;
        int16_t y = 0;

    public:

        int16_t getX()                              { return this->x; }
        int16_t getY()                              { return this->y; }
        uint8_t getCounter()                        { return this->counter; }
        bool getExplosionSet()                      { return this->explosionSet; }

        void setX(int16_t val)                      { this->x = val; }
        void setY(int16_t val)                      { this->y = val; }
        void setCounter(uint8_t val)                { this->counter = val; }
        void setExplosionSet(bool val)              { this->explosionSet = val; }


    public:

        void setExplosions(int16_t x, int16_t y) {

            this->setExplosionSet(true);
            this->counter = 17;
            this->x = x;
            this->y = y;

            for (uint8_t i = 0; i < 60; i++) {

                this->explosion[i].setX(x + ((i % 6) - 3));
                this->explosion[i].setY(y + ((i % 6) - 3));
                this->explosion[i].setCounter(-random(0, 32));
                this->explosion[i].setDirection(random(0, 16));
                
            }

        }

        void setExplosionsTitle(int16_t x, int16_t y) {

            this->counter = 17;
            this->x = x;
            this->y = y;

            for (uint8_t i = 0; i < 30; i++) {

                this->explosion[i].setX(x + ((i % 14) - 7));
                this->explosion[i].setY(y + ((i % 14) - 7));
                this->explosion[i].setCounter(-random(0, 32));
                this->explosion[i].setDirection(random(3, 6));
                
            }

        }

        bool update(bool altFrame) {

            bool finished = true;

            for (uint8_t i = 0; i < 60; i++) {

                if (!this->explosion[i].update(altFrame)) {

                    finished = false;

                }
                else {
                }
                
            }

            if (this->counter > 0) this->counter--;
            return finished;

        }

        Explosion & getExplosion(uint8_t index) {

            return this->explosion[index];

        }

        void reset() {

            this->counter = 0;
            
            for (uint8_t i = 0; i < 60; i++) {

                this->explosion[i].setCounter(-127);
                
            }

        }

};