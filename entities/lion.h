#include <Arduboy2.h>
#include "../images/images.h"
#include "../utils/consts.h"

struct Lion {

    const uint8_t xPositions[11] =      { 28, 33, 38, 43, 48,   53,   58, 63, 68, 73, 78 };
    const uint8_t leftImages[11] =      { 2,  0,  1,  0,  1,    0,    1,  0,  1,  0,  1 };
    const uint8_t rightImages[11] =     { 3,  4,  3,  4,  3,    4,    3,  4,  3,  4,  5 };

    private:

        XPosition x = XPosition::Centre;
        YPosition y = YPosition::Level_1;
        Direction direction = Direction::Left;
        Direction nextDirection = Direction::Left;
        uint8_t speed = 8;
        uint8_t steps = 0;
        uint8_t stepsOrig = 0;

    public:

        XPosition getXPosition()                    { return this->x; }
        YPosition getYPosition()                    { return this->y; }
        Direction getDirection()                    { return this->direction; }
        Direction getNextDirection()                { return this->nextDirection; }
        uint8_t getSpeed()                          { return this->speed; }
        uint8_t getSteps()                          { return this->steps; }

        void setXPosition(XPosition val)            { this->x = val; }
        void setYPosition(YPosition val)            { this->y = val; }
        void setDirection(Direction val)            { this->direction = val; this->setSpeed(random(6, 11)); }
        void setNextDirection(Direction val)        { this->nextDirection = val; }
        void setSpeed(uint8_t val)                  { this->speed = val; }
        void setSteps(uint8_t val)                  { this->steps = val; this->stepsOrig = val; }

    public:

        void decXPosition()                         { this->x--; }
        void incXPosition()                         { this->x++; }
        void decYPosition()                         { if (this->y != YPosition::Level_1) this->y--; }
        void incYPosition()                         { if (this->y != YPosition::Level_3) this->y++; }

        uint8_t getXDisplay()                       { return this->xPositions[static_cast<uint8_t>(this->x)]; }
        
        bool decSteps() { 

            this->steps--; 
// Serial.print("Steps ");
// Serial.println(this->steps);
            if (this->steps % 3 == 0) {

                this->stepsOrig = this->stepsOrig - 3;

                switch (this->direction) {

                    case Direction::Up:
                        this->y--;
                        break;

                    case Direction::Down:
                        this->y++;
                        break;

                    default: break;
                
                }

            }

            if (this->steps == 0) {
                this->stepsOrig = 0;
                this->direction = this->nextDirection;                
            }

            return (this->steps == 0);
//            return (this->steps % 3 == 0);

        }
        
        uint8_t getYDisplay() { 
            
            uint8_t yPos = static_cast<uint8_t>(this->y) * 21; 
Serial.print("getYDisplay() stepsOrig ");            
Serial.print(this->stepsOrig);
Serial.print(" steps ");            
Serial.print(this->steps);
Serial.print(" = ");            
Serial.println((this->stepsOrig - this->steps));
            switch (this->direction) {

                case Direction::Up:
                    yPos = yPos - ((this->stepsOrig - this->steps) * 7);
                    return yPos;

                case Direction::Down:
                    yPos = yPos + ((this->stepsOrig - this->steps) * 7);
                    return yPos;

                default:
                    return yPos;

            }
        
        }

        uint8_t getFrame() {

            switch (this->direction) {

                case Direction::Left:
                    return this->leftImages[static_cast<uint8_t>(this->x)];

                case Direction::Right:
                    return this->rightImages[static_cast<uint8_t>(this->x)];
                
                default:

                    switch (this->nextDirection) {
                        
                        case Direction::Left:
                            return this->leftImages[static_cast<uint8_t>(this->x)];

                        default:
                            return this->rightImages[static_cast<uint8_t>(this->x)];

                    }

            }

        }


        bool isMovingUpDown() {

            return this->direction == Direction::Up || this->direction == Direction::Down;

        }

};