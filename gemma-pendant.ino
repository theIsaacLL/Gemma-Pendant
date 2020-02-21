#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, 0); // 16-led neopixel ring, pin D0 on Gemma

uint32_t color  = 0xFF8000; // Amber

int mode = 0; // Current animation mode
int offset = 0;
int i;

void setup() {
  pixels.begin();
  pixels.setBrightness(35);
  pixels.show(); // Clear all pixels
  pinMode(A1, INPUT); // Pin for touch
  while (analogRead(A1) < 900) delay(1); // Wait for someone to touch the pad before starting
}

void loop() {
  animate();
  checkForTouch();
}

void checkForTouch() {
  if (analogRead(A1) > 1000) {
    pixels.clear();
    mode++;
    if(mode > 1) {
      mode = 0;
      color >>= 8;
      if(!color) color = 0xFF8000;
    }
    delay(1000);
  }
}

void animate() {
  switch (mode) {
    case 0:
      //int count = 0;
      i = random(16);
      pixels.setPixelColor(i, color);
      pixels.show();
      pixels.setPixelColor(i, 0);
      //count++;
      //if (count > 5) {color >>= 8; if(!color) color = 0xFF8000;}
      delay(65);
      break;
     case 1:
      for(i=0; i<16; i++) {
        uint32_t c = 0;
        if(((offset + i) & 7) < 2) {
          c = color;
        }
        pixels.setPixelColor(i, c);
      }
      pixels.show();
      delay(60);
      offset++;
      break;
      
      /*i = 0;
      pixels.setPixelColor(i, Wheel(random(0, 255)));
      pixels.setPixelColor(random(1, 59), Wheel(random(0, 255)));
      pixels.show();
      i++;
      if (i >= 16) i = 0;
      delay(10);
      break;*/
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
