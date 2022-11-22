/*
   Christmas tree by designer2k2.at
   Stephan Martin 2016
   http://www.designer2k2.at
   https://github.com/designer2k2/xmas-tree
   This code is made to run on a Digispark
   Feeding Neopixel Rings, stacked to a tree.
   Brightness is reduced as there is only USB power supply.
   Needs Adafruit NeoPixel Lib to work: https://github.com/adafruit/Adafruit_NeoPixel
   Use the build in Library manager in the Arduino IDE: "Adafruit NeoPixel"
   Use the ATTinyCore set to ATtiny85 (Micronucleus / Digispark) in the Arduino IDE
   https://github.com/SpenceKonde/ATTinyCore
*/

#include <Adafruit_NeoPixel.h>  //needed for the WS2812

#if defined(ESP32)
#pragma message "ESP32 based board, Pin 8"
#define PIN 8          //Pin 8, A3 is DATA In on the bottom Ring
#else
#pragma message "AVR based board, Pin 1"
#define PIN 1          //Pin 1 is DATA In on the bottom Ring
#endif

#define BRIGHTNESS 40  // brightness reduced (about 180mA max, 100mA average)
#define SIZEOFARRAY(X) sizeof(X) / sizeof(X[0])

#define TOTAL_LED 61  // Fill by hand
const uint8_t ringsSize[] = { 1, 8, 12, 16, 24 };


//Lookups for the X-M-A-S Letters viewed from above:
const uint8_t charX[] PROGMEM = { 4, 27, 54, 61, 58, 35, 16, 10, 31, 56, 60, 39, 22 };
const uint8_t charM[] PROGMEM = { 4, 26, 25, 40, 22, 39, 60, 61, 58, 35, 16, 34, 33, 32, 10 };
const uint8_t charA[] PROGMEM = { 4, 27, 42, 53, 60, 51, 37, 19, 49, 58, 57, 61, 46, 31, 10 };
const uint8_t charS[] PROGMEM = { 22, 38, 37, 36, 35, 34, 47, 57, 61, 53, 41, 26, 27, 28, 29, 30, 10 };

//Lookup for the Candle light
const uint8_t candles[] PROGMEM = { 15, 10, 48, 45, 36, 19, 59, 29, 5, 43, 41, 39, 24, 3, 61 };


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(TOTAL_LED, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  pinMode(PIN, OUTPUT);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);  // set brightness
  strip.show();                     // Initialize all pixels to 'off'

  // XMAS Letters:
  xmas(1000);
  delay(2000);
}

void loop() {

  //Tree light [Green]
  tree(strip.Color(0, 50, 0));
  delay(1000);

  //Color crazy:
  colorcrazy();
  delay(1000);

  warpdrive(strip.Color(255, 255, 255));
  comet(strip.Color(0, 0, 255));


  /*
    // Some example procedures showing how to display to the pixels:
    colorWipe(strip.Color(255, 0, 0), 50); // Red
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
    // Send a theater pixel chase in...
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127,   0,   0), 50); // Red
    theaterChase(strip.Color(  0,   0, 127), 50); // Blue
    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);
  */
}

//Sub-----------------------------------------------------------------------

//Comet
void comet(uint32_t _color) {
  for (uint16_t i = strip.numPixels(); i > 0; i--) {
    strip.setPixelColor(i, _color);
    fadethemall(10);
    fadethemall(10);
  }
}

//From top down white pulses
void warpdrive(uint32_t _color) {
  uint8_t totalLed = TOTAL_LED;
  uint8_t ringSize, led;

  for (ringSize = 0; ringSize < SIZEOFARRAY(ringsSize); ++ringSize) {
    // 60 -> 61 (1) | 52 -> 60 (8) | 40 -> 52 (12) ...
    for (led = totalLed - ringsSize[ringSize]; led < totalLed; ++led) {
      strip.setPixelColor(led, _color);
    }
    strip.show();

    for (uint8_t i = 0; i < 20; i++) fadethemall(20);
    totalLed -= ringsSize[ringSize];
  }
}

//This reduces the brightness of all leds
void fadethemall(uint8_t _wait) {
  uint8_t r, g, b, counter;
  uint32_t color;

  for (counter = 0; counter < TOTAL_LED; counter++) {
    color = strip.getPixelColor(counter);

    r = (uint8_t)(color >> 16);
    g = (uint8_t)(color >> 8);
    b = (uint8_t)color;

    if (r > 0) --r;
    if (g > 0) --g;
    if (b > 0) --b;

    strip.setPixelColor(counter, strip.Color(r, g, b));
  }

  strip.show();
  delay(_wait);
}

//This drives the WS2812 in a crazy pattern, fun!
void colorcrazy() {
  colorWipe(strip.Color(255, 0, 0), 25);  // Red
  colorWipe(strip.Color(0, 255, 0), 25);  // Green
  colorWipe(strip.Color(0, 0, 255), 25);  // Blue
  theaterChaseRainbow(5);
}

//This lights up the tree in green, then add the white "candles"
void tree(uint32_t _color) {

  colorWipe(_color, 50);  // Green

  //light "candles"
  //Show the S:
  for (uint8_t i = 0; i < SIZEOFARRAY(candles); i++) {
    strip.setPixelColor(pgm_read_byte(&candles[i]) - 1, strip.Color(255, 255, 255));
    strip.show();
    delay(50);
  }
}

//This shows the X-M-A-S when viewed from above
void xmas(uint16_t _wait) {
  uint8_t i;
  colorWipe(strip.Color(0, 0, 0), 0);  // blank

  //Show the X:
  for (i = 0; i < SIZEOFARRAY(charX); i++) {
    strip.setPixelColor(pgm_read_byte(&charX[i]) - 1, strip.Color(255, 0, 0));
    strip.show();
    delay(50);
  }
  delay(_wait);
  colorWipe(strip.Color(0, 0, 0), 0);  // blank

  //Show the M:
  for (i = 0; i < SIZEOFARRAY(charM); i++) {
    strip.setPixelColor(pgm_read_byte(&charM[i]) - 1, strip.Color(0, 255, 0));
    strip.show();
    delay(50);
  }
  delay(_wait);
  colorWipe(strip.Color(0, 0, 0), 0);  // blank

  //Show the A:
  for (i = 0; i < SIZEOFARRAY(charA); i++) {
    strip.setPixelColor(pgm_read_byte(&charA[i]) - 1, strip.Color(0, 0, 255));
    strip.show();
    delay(50);
  }
  delay(_wait);
  colorWipe(strip.Color(0, 0, 0), 0);  // blank

  //Show the S:
  for (i = 0; i < SIZEOFARRAY(charS); i++) {
    strip.setPixelColor(pgm_read_byte(&charS[i]) - 1, strip.Color(125, 125, 125));
    strip.show();
    delay(50);
  }

  delay(_wait);
  colorWipe(strip.Color(0, 0, 0), 0);  // blank
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t _c, uint8_t _wait) {
  for (uint8_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, _c);
    strip.show();
    delay(_wait);
  }
}

void rainbow(uint8_t _wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(_wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t _wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) {  // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(_wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t _c, uint8_t _wait) {
  for (uint8_t j = 0; j < 10; j++) {  //do 10 cycles of chasing
    for (uint8_t q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, _c);  //turn every third pixel on
      }
      strip.show();

      delay(_wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);  //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t _wait) {
  for (int j = 0; j < 256; j++) {  // cycle all 256 colors in the wheel
    for (uint8_t q = 0; q < 3; q++) {
      for (uint8_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel((i + j) % 255));  //turn every third pixel on
      }
      strip.show();

      delay(_wait);

      for (uint8_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);  //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
