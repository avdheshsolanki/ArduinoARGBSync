#include <Adafruit_NeoPixel.h>
#include <stdlib.h>     /* atoi */

//Config Values
#define PIN 11


#define MODE_RAINBOW 1
#define MODE_RAINBOW_STR "1"
#define MODE_RAINBOW_CYCLE 2
#define MODE_RAINBOW_CYCLE_STR "2"
#define MODE_RAINBOW_THEATRE 3
#define MODE_RAINBOW_THEATRE_STR "3"
#define MODE_THEATRE_WHITE 4
#define MODE_THEATRE_WHITE_STR "4"
#define MODE_THEATRE_RED 5
#define MODE_THEATRE_RED_STR "5"
#define MODE_THEATRE_GREEN 6
#define MODE_THEATRE_GREEN_STR "6"
#define MODE_THEATRE_BLUE 7
#define MODE_THEATRE_BLUE_STR "7"
#define MODE_RED 8
#define MODE_RED_STR "8"
#define MODE_GREEN 9
#define MODE_GREEN_STR "9"
#define MODE_BLUE 10
#define MODE_BLUE_STR "10"
#define MODE_CUSTOM 11
#define MODE_CUSTOM_STR "CUSTOM"

//Commands
#define CHANGE_WAIT_TIME "WT#"



// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
int led_mode = MODE_RAINBOW;
int WAIT_TIME = 10;
int r = 0;
int g = 0;
int b = 0;
void handleSerialInput()
{
  while(Serial.available() > 0)
  {
    String in = Serial.readString();
    int len = in.length() + 1;
    char str[len];
    in.toCharArray(str,len);
    Serial.print("Serial Input: ");
    Serial.println(str);
    if(strcmp(str, MODE_RAINBOW_STR) == 0){
      led_mode = MODE_RAINBOW;
    } else if(strcmp(str,MODE_RAINBOW_CYCLE_STR) == 0) {
      led_mode = MODE_RAINBOW_CYCLE;
    } else if(strcmp(str,MODE_RAINBOW_THEATRE_STR) == 0) {
      led_mode = MODE_RAINBOW_THEATRE;
    } else if(strcmp(str,MODE_THEATRE_WHITE_STR) == 0) {
      led_mode = MODE_THEATRE_WHITE;
    } else if(strcmp(str,MODE_THEATRE_RED_STR) == 0) {
      led_mode = MODE_THEATRE_RED;
    } else if(strcmp(str,MODE_THEATRE_GREEN_STR) == 0) {
      led_mode = MODE_THEATRE_GREEN;
    } else if(strcmp(str,MODE_THEATRE_BLUE_STR) == 0) {
      led_mode = MODE_THEATRE_BLUE;
    } else if(strcmp(str,MODE_RED_STR) == 0) {
      led_mode = MODE_RED;
    } else if(strcmp(str,MODE_GREEN_STR) == 0) {
      led_mode = MODE_GREEN;
    } else if(strcmp(str,MODE_BLUE_STR) == 0) {
      led_mode = MODE_BLUE;
    } else if(strcmp(str,MODE_BLUE_STR) == 0) {
      led_mode = MODE_BLUE;
    } else if(in.indexOf("CUSTOM") > -1) {
      //TODO: Set Custom Colors
      char * token = strtok(str, "#");
      // loop through the string to extract all other tokens
      int c = 1;
      while( token != NULL ) {
        token = strtok(NULL, "#");
        if(c==1)
        {
          r = atoi(token);
          c++;
        } else if(c==2) {
          g = atoi(token);
          c++;
        } else if(c==3) {
          b = atoi(token);
          c++;
        }
       }
       led_mode = MODE_CUSTOM;
    } else if(in.indexOf("WT") > -1) {
      //TODO: Set WAIT_TIME
      char * token = strtok(str, "#");
      int c=1;
      while( token !=  NULL) {
        token = strtok(NULL, "#");
        if(c==1)
        {
          Serial.print("Changing WAIT_TIME: ");
          WAIT_TIME = atoi(token);
          c++;
          Serial.println(WAIT_TIME);
        }
      }
    }else {
//      led_mode = MODE_RAINBOW;
    }
    Serial.print("Setting led_mode: ");
    Serial.println(led_mode);
  }
}
void setup() {
  Serial.begin(115200); // use the same baud-rate as the python side
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  handleSerialInput();
   
  switch (led_mode)
  {
  case MODE_RAINBOW:
    rainbow(WAIT_TIME);
    break;
    
  case MODE_RAINBOW_CYCLE:
    rainbowCycle(WAIT_TIME);
    break;

  case MODE_RAINBOW_THEATRE:
     theaterChaseRainbow(WAIT_TIME);
     break;

  case MODE_THEATRE_WHITE:
    theaterChase(strip.Color(127, 127, 127), WAIT_TIME);
    break;
  
  case MODE_THEATRE_RED:
    theaterChase(strip.Color(127,   0,   0), WAIT_TIME);
    break;

  case MODE_THEATRE_GREEN:
    theaterChase(strip.Color(0,   127,   0), WAIT_TIME);
    break;

  case MODE_THEATRE_BLUE:
    theaterChase(strip.Color(  0,   0, 127), WAIT_TIME);
    break;

  case MODE_RED:
    colorWipe(strip.Color(255, 0, 0), WAIT_TIME);
    break;

  case MODE_GREEN:
    colorWipe(strip.Color(0, 255, 0), WAIT_TIME);
    break;

  case MODE_BLUE:
    colorWipe(strip.Color(0, 0, 255), WAIT_TIME);
    break;

  case MODE_CUSTOM:
    colorWipe(strip.Color(r, g, b), WAIT_TIME);
    break;
  default:
    rainbow(20);
    break;
  }
//  colorWipe(strip.Color(2, 14, 74), 50);
  
  // Some example procedures showing how to display to the pixels:
//  colorWipe(strip.Color(255, 0, 0), 50); // Red
//  colorWipe(strip.Color(0, 255, 0), 50); // Green
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//
//  // Send a theater pixel chase in...
//  theaterChase(strip.Color(127, 127, 127), 50); // White
//  theaterChase(strip.Color(127,   0,   0), 50); // Red
//  theaterChase(strip.Color(0,   127,   0), 50); // Green
//  theaterChase(strip.Color(  0,   0, 127), 50); // Blue
//
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
    Serial.println("Starting colorWipe");

  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  Serial.println("Starting rainbow");
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  Serial.println("Starting rainbowCycle");
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
    Serial.println("Starting theaterChase");
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
      Serial.println("Starting theaterChaseRainbow");

  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();

        delay(wait);

        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
