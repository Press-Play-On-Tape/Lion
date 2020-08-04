#include <Arduboy2.h>
#include "../images/images.h"
#include "../utils/consts.h"

struct Player {

    private:

        uint8_t index = 0;
        uint8_t x = 0;
        YPosition y = YPosition::Level_1;
        uint16_t score;

    public:

        uint8_t getX()                              { return this->x; }
        YPosition getYPosition()                    { return this->y; }
        uint16_t getScore()                         { return this->score; }

        void setX(uint8_t val)                      { this->x = val; }
        void setY(YPosition val)                    { this->y = val; }
        void setScore(uint16_t val)                 { this->score = val; }

    public:

        void incScore()                             { this->score++; }

        void decYPosition()                         { if (this->y != YPosition::Level_1) this->y--; }
        void incYPosition()                         { if (this->y != YPosition::Level_3) this->y++; }

        uint8_t getXDisplay()                       { return this->x; }
        uint8_t getYDisplay()                       { return static_cast<uint8_t>(this->y) * 21; }

        void reset(uint8_t index,  uint8_t x, YPosition y) {

            this->index = index;
            this->x = x;
            this->y = y;

        }

};

