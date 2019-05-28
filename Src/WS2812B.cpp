#include "WS2812B.h"
#include <string.h>
#include "light_ws2812_cortex.h"

WS2812B::WS2812B(uint8_t led_number): led_number(led_number) {
  pixel_array = new uint8_t[led_number * 3];
}

bool WS2812B::setColorAll(s_color color) {
  for (uint8_t i = 0; i < led_number; i++) {
    pixel_array[i * color_data_bytes + 0] = color.r;
    pixel_array[i * color_data_bytes + 1] = color.g;
    pixel_array[i * color_data_bytes + 2] = color.b;
  }

  return true;
}

bool WS2812B::setColorIndex(uint8_t index, s_color color) {
  if (led_number <= index) {
    return false;
  }
  pixel_array[index * color_data_bytes + 0] = color.r;
  pixel_array[index * color_data_bytes + 1] = color.g;
  pixel_array[index * color_data_bytes + 2] = color.b;
  return true;
}

bool WS2812B::setColorRange(uint8_t index, uint8_t range, s_color color) {
  if (led_number <= index+range) {
    return false;
  }
  for (uint8_t i = index; i <= index+range; i++) {
    pixel_array[i * color_data_bytes + 0] = color.r;
    pixel_array[i * color_data_bytes + 1] = color.g;
    pixel_array[i * color_data_bytes + 2] = color.b;
  }
  return true;
}

// TODO: Should not exists
bool WS2812B::setMemory(uint8_t *buffer, uint8_t size) {
  memcpy(pixel_array, buffer, size * color_data_bytes);
  return true;
}

void WS2812B::update() {
  ws2812_sendarray(pixel_array, led_number * color_data_bytes);
}
