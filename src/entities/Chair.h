#pragma once

#include <Arduboy2.h>
#include "../images/Images.h"
#include "../utils/Consts.h"

struct Chair {

    private:

        uint8_t x;
        uint8_t y;
        uint8_t frame;
        uint8_t counter;
        Direction direction = Direction::None;

    public:

        void setPosition(uint8_t x, uint8_t y, Direction direction) {

            this->x = x;
            this->y = y;
            this->direction = direction;
            this->frame = 0;
            this->frame = 8;

        }

        void update() {

            if (this->counter == 0) return;

            this->x = this->x + (this->direction == Direction::Left ? -1 : 0);
            this->frame++;
            this->counter--;

        }

};