#ifndef __GAME_ENGINE_H
#define __GAME_ENGINE_H

#include <stdint.h>


typedef enum {
    PLAY = 0,
    END_WIN_PLAYER_1,
    END_WIN_PLAYER_2
} Game_States;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pixel_Type;



class GameEngine {
    public:
        GameEngine(uint8_t pixel_number);
        virtual Game_States process(uint8_t player_button) = 0;

        uint8_t pixel_total;
        uint8_t *pixel_array;
        float speed_factor;

        enum {
            BUTTON_PLAYER_NO,
            BUTTON_PLAYER_1,
            BUTTON_PLAYER_2
        };

    protected:
        void setState(Game_States state);
        Game_States getState(void);
        void setPlayerWin(uint8_t player);

        const pixel_Type symbol_end = {255*brighness/100, 255*brighness/100, 0};
        const pixel_Type symbol_zone_player_1 = {153*brighness/100, 255*brighness/100, 51*brighness/100};
        const pixel_Type symbol_zone_player_2 = {255*brighness/100, 255*brighness/100, 0};
        const pixel_Type symbol_off = {0, 0, 0};
        const pixel_Type symbol_winner = {255*brighness/100, 0, 0};
        const pixel_Type symbol_looser = {0, 255*brighness/100, 0};
        const float brighness = 30; // TODO: Better use

    private:
        Game_States state;
};

#endif // __GAME_ENGINE_H
