#include "Objects.h"

#define NUM_LEDS 10
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
}

void loop() {
  updateObjects(leds);
  FastLED.show();
}
