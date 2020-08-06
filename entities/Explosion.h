#pragma once

#include <Arduboy2.h>
#include "../images/Images.h"
#include "../utils/Consts.h"

struct Explosion {

    private:

        int16_t x = 0;
        int16_t y = 0;
        int8_t counter = 0;
        uint8_t direction = 0;

    public:

        int16_t getX()                              { return this->x; }
        int16_t getY()                              { return this->y; }
        int8_t getCounter()                         { return this->counter; }
        uint8_t getDirection()                      { return this->direction; }

        void setX(int16_t val)                      { this->x = val; }
        void setY(int16_t val)                      { this->y = val; }
        void setCounter(int8_t val)                 { this->counter = val; }
        void setDirection(uint8_t val)              { this->direction = val; }

    public:

        void update(bool altFrame) {

            switch (this->counter) {

                case -127 ... -1:    
                    this->counter++;
                    break;

                case 0 ... 60:
                    this->counter++;

                    switch (this->direction) {

                        case 0:                              // N
                            this->y = this->y - 1;
                            break;

                        case 1:                              // NNE
                            this->y = this->y - 1;
                            if (altFrame) this->x = this->x + 1;
                            break;

                        case 2:                              // NE
                            this->x = this->x + 1;
                            this->y = this->y - 1;
                            break;

                        case 3:                              // ENE
                            if (altFrame) this->y = this->y - 1;
                            this->x = this->x + 1;
                            break;

                        case 4:                              // E
                            this->x = this->x + 1;
                            break;

                        case 5:                              // ESE
                            if (altFrame) this->y = this->y + 1;
                            this->x = this->x + 1;
                            break;

                        case 6:                              // SE
                            this->x = this->x + 1;
                            this->y = this->y + 1;
                            break;

                        case 7:                              // SSE
                            this->y = this->y + 1;
                            if (altFrame) this->x = this->x + 1;
                            break;

                        case 8:                              // S
                            this->y = this->y + 1;
                            break;

                        case 9:                              // SSW
                            this->y = this->y + 1;
                            if (altFrame) this->x = this->x - 1;
                            break;

                        case 10:                             // SW
                            this->x = this->x - 1;
                            this->y = this->y + 1;
                            break;

                        case 11:                              // WSW
                            if (altFrame) this->y = this->y + 1;
                            this->x = this->x - 1;
                            break;

                        case 12:                             // W
                            this->x = this->x - 1;
                            break;

                        case 13:                             // WNW
                            if (altFrame) this->y = this->y - 1;
                            this->x = this->x - 1;
                            break;

                        case 14:                             // NW
                            this->x = this->x - 1;
                            this->y = this->y - 1;
                            break;

                        case 15:                             // NNW
                            this->y = this->y - 1;
                            if (altFrame) this->x = this->x - 1;
                            break;

                    }

                    break;

            }

        }

        bool render() {

            switch (this->counter) {

                case -127 ... -1:
                    return false;

                case 0 ... 60:
                    return true;

                default:
                    return false;

            }

        }

};