#ifndef __PINGPONG_H
#define __PINGPONG_H

#include "gameEngine.h"

class PingPong: public GameEngine {
    public:
        PingPong(uint8_t pixel_number);
        Game_States process(uint8_t player_button);

    private:
        const uint8_t player_zone = 6;
        int8_t dir;
        int16_t ball_position;

        const pixel_Type symbol_middle = {255, 0, 0};
        const pixel_Type symbol_ball = {0, 0, 255};

        static bool checkZone(uint8_t ball_position, uint8_t start, uint8_t end);
};

#endif // __PINGPONG_H
