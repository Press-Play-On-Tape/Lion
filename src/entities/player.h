#pragma once

#include <Arduboy2.h>
#include "../images/Images.h"
#include "../utils/Consts.h"

struct Player {

    private:

        const uint8_t xPositions[6]= { 13, 9, 5, 91, 95, 99 };

        uint8_t index = 0;
        YPosition y = YPosition::Level_1;

    public:

        YPosition getYPosition()                    { return this->y; }
        uint8_t getIndex()                          { return this->index; }

        void setY(YPosition val)                    { this->y = val; }

    public:

        void decYPosition()                         { if (this->y != YPosition::Level_1) this->y--; }
        void incYPosition()                         { if (this->y != YPosition::Level_3) this->y++; }
        
        uint8_t getYDisplay()                       { return static_cast<uint8_t>(this->y) * 21; }

        uint8_t getXDisplay() { 

            switch (this->index) {

                case Constants::Player1_Index:
                    return xPositions[static_cast<uint8_t>(this->y)];

                case Constants::Player2_Index:
                    return xPositions[static_cast<uint8_t>(this->y) + 3];

            }

        }

        void reset(uint8_t index,  YPosition y) {

            this->index = index;
            this->y = y;

        }

};

