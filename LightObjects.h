#include <Arduino_AVRSTL.h>
#include <FastLED.h>

// Base class for object
class LightObject {
  public:
    int pos;
    int num_leds;
    long init_time;

    LightObject(int pos, int num_leds) : pos(pos), num_leds(num_leds) {
      init_time = millis();
    }

    virtual void update(CRGB* leds) = 0;

    long time() {return millis() - init_time;}

    void setLeds(CRGB* leds, CRGB color, int n=num_leds, int offset=0) {
      for (int i = 0; i < n; i++){
        leds[pos + offset + i] = color;
      }
    }
    void setLeds(CRGB* leds, std::vector<CRGB>& colors, int offset=0) {
      for (int i = 0; i < colors.size(); i++){
        leds[pos + offset + i] = colors[i];
      }
    }
    void clearLeds(CRGB* leds, int n=num_leds, int offset=0) {
      for (int i = 0; i < n; i++) {
        leds[pos + offset + i] = CRGB::Black;
      }
    }
};


// Set to a single color constantly
class AlwaysOn : public LightObject {
  public:
    std::vector<CRGB> colors;

    AlwaysOn(int pos, CRGB color, int num_leds=1) : LightObject(pos, num_leds), colors(std::vector<CRGB>(num_leds, color)) {}
    AlwaysOn(int pos, std::vector<CRGB>& colors) : LightObject(pos, colors.size()), colors(colors) {}
    void update(CRGB* leds) { setLeds(leds, color); }
};


// A basic blinker
class Blinker : public LightObject {
  public:
    CRGB color;
    long time_on, time_off;
    long total_time;
    int num_leds;

    Blinker(int pos, CRGB color, long time_on, long time_off, int num_leds=1) : 
      LightObject(pos), color(color), time_on(time_on), time_off(time_off), num_leds(num_leds) {
        total_time = time_on + time_off;
      }
    
    void update(CRGB* leds){
      long mod_time = time() % total_time;
      if (mod_time > time_on) setLeds(leds, color, num_leds);
      else clearLeds(leds, color, num_leds);
    }
};


// Cycle through multiple colors
class Cycle : public LightObject {
  public:
    std::vector<CRGB> colors;
    long time_per_color;
    int num_leds;

    Cycle(int pos, std::vector<CRGB>& colors, int time_per_color, int num_leds=1) :
      LightObject(pos), colors(colors), time_per_color(time_per_color), num_leds(num_leds) {}
    
    void update(CRGB* leds) {
      long mod_time = time() % (time_per_color * colors.size());
      CRGB curr_color = colors[mod_time / colors.size()];
      for (int i = 0; i < num_leds; i++) {

      }
    }
};
