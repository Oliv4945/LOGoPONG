#include "gameEngine.h"
#include <stdlib.h>
#include <string.h>

GameEngine::GameEngine(uint8_t pixel_number): pixel_total(pixel_number) {
    this->state = PLAY;
    this->speed_factor = 1;
}

void GameEngine::setState(Game_States state) {
    this->state = state;
}

Game_States GameEngine::getState(void) {
    return this->state;
}

// TODO: Rename to endGame
void GameEngine::setPlayerWin(uint8_t winner) {
    const uint8_t size = 8; // TODO: More explicit
    uint8_t symbol_width = sizeof(symbol_off);

    // Set all fields
    for (uint8_t i=0; i<pixel_total; i++) {
      memcpy(this->pixel_array+i*symbol_width, &symbol_end, symbol_width);
    }

    switch (winner) {
        case END_WIN_PLAYER_1:
          for (uint8_t i=0; i<pixel_total/2; i++) {
            memcpy(this->pixel_array+i*symbol_width, &symbol_winner, symbol_width);
          }
          for (uint8_t i=pixel_total/2; i<pixel_total; i++) {
            memcpy(this->pixel_array + i * symbol_width, &symbol_looser, symbol_width);
          }
          break;

        case END_WIN_PLAYER_2:
          for (uint8_t i=0; i<pixel_total/2; i++) {
            memcpy(this->pixel_array+i*symbol_width, &symbol_looser, symbol_width);
          }
          for (uint8_t i=pixel_total/2; i<pixel_total; i++) {
            memcpy(this->pixel_array + i * symbol_width, &symbol_winner, symbol_width);
          }
          break;
    }
}
