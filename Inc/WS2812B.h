#ifndef __WS2812B_H
#define __WS2812B_H

#include <stdint.h>
#include <inttypes.h>

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} s_color;

class WS2812B {
public:
  WS2812B(uint8_t led_number);
  bool setColorAll(s_color color);
  bool setColorIndex(uint8_t index, s_color color);
  bool setColorRange(uint8_t index, uint8_t range, s_color color);
  void update();

private:
  uint8_t led_number;
  uint8_t *pixel_array;
  const uint8_t color_data_bytes = 3; // 3 For RGB, 4 for RGBW (Not yet implemented)
};

#endif /* __WS2812B_H */
