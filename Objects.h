#include <FastLED.h>
#include "LightObjects.h"


// The number of different objects
#define NUM_OBJECTS 1

LightObject* LIGHT_OBJECTS[NUM_OBJECTS] = {

  // DEFINE ALL NEW OBJECTS HERE

  new AlwaysOn(0, CRGB::Red),


};


void updateObjects(CRGB* leds) {
  for (int i = 0; i < NUM_OBJECTS; i++) LIGHT_OBJECTS[i]->update(leds);
}
