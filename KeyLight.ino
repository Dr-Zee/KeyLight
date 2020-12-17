#include "dataStructure.h"
//#include "Neopixelfunctions.h"
//#include "stepFade.h"

// Libraries
#include <usbhub.h>
#include <usbh_midi.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>

// LEDs
#define LED_PIN     8
#define LED_COUNT  175
#define BRIGHTNESS 10
#define TRANSITION_TIME 900

//Choose a white balance profile.
//0 = Cool Blue
//1 - Hot & Heavy
#define WHITE_BALANCE 0

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// USB 
USB Usb;
USBH_MIDI  Midi(&Usb);
void MIDI_poll();
boolean bFirst;
uint16_t pid, vid;

// Variables
byte event;
byte key;
byte colorSteps = 1;


void setup()
{
  Serial.begin(115200);
  bFirst = true;
  vid = pid = 0;
  setDefaultData();
  if (Usb.Init() == -1) {
    while (1); //halt
  }
  delay(200);
  initializeStrip();        
}

void loop()
{
  // Initialize USB.
  Usb.Task();
  if ( Usb.getUsbTaskState() == USB_STATE_RUNNING ) {
    
    // Listen for Midi.
    MIDI_poll();
    
    //  Light the keys
    keyStrikes(key);
    
    // Debounce the event.
    if(event != 0) {
     event = 0;
    }
    
    // Do the big fade.
    theBigFade();
  }
}

// Set default key data.
void setDefaultData() {
  for (int i = 1; i < 88; i++) {
    //the 88th key only has one LED... intentionally.
    if(i == 88) {
      keyBuffer[i].keyLight[0] = keyBuffer[i].keyLight[1] = 176;
    }
    keyBuffer[i].keyLight[0] = (i * 2) - 2;
    keyBuffer[i].keyLight[1] = keyBuffer[i].keyLight[0] + 1;
    keyBuffer[i].isDown = keyBuffer[i].recentlyReleased = keyBuffer[i].runOnce = false;
  }
}

// Initialize light strip.
void initializeStrip() {
  strip.begin();
  stripOn(strip.Color(90, 30, 0, 5));
  strip.show();       
}

// Midi Listener.
void MIDI_poll() {
  char buf[20];
  uint8_t bufMidi[64];
  uint16_t  rcvd;
  if (Midi.vid != vid | Midi.pid != pid) {
    vid = Midi.vid;
    pid = Midi.pid;
  }
  if (Midi.RecvData( &rcvd,  bufMidi) == 0 ) {
    event = bufMidi[0];
    //channel = bufMidi[1];
    //velocity = bufMidi[3];
    if (event == 8 | event == 9) {
      key = bufMidi[2] - 20;
      setEventProperties(key, event);
    }
  }
}

// Set event properties
void setEventProperties(byte key, byte event) {    
  if (event == 9) {
    keyBuffer[key].isDown = true;
    keyBuffer[key].recentlyReleased = keyBuffer[key].runOnce = false;
  }
  if (event == 8) {
    keyBuffer[key].runOnce = keyBuffer[key].recentlyReleased = true;
    keyBuffer[key].isDown = false;
    keyBuffer[key].lastReleased = millis();
  }
}

// push a color to the keys only once.
void keyStrikes(byte key) {
  if(keyBuffer[key].isDown == true & keyBuffer[key].runOnce == false) {
    for(int i = 0; i < 2; i++) {
      strip.setPixelColor(keyBuffer[key].keyLight[i], strip.Color( 255, 0, 0, 0));
    }
    strip.show();
    
    // Do Housekeeping
    keyOnHousekeeping(key);
  }
}

// Fade out loop for non-blocking transitions out
void theBigFade() {
  for (int i = 1; i < 88; i++) {
    if(keyBuffer[i].recentlyReleased == true) {
      
      uint32_t elapsed = millis() - keyBuffer[i].lastReleased;
      
      // Transition Steps. Soon to be replaced. 
       if(elapsed > TRANSITION_TIME * .95 & elapsed < TRANSITION_TIME * .96) {
        int index = i;
          for(int i = 0; i < 2; i++) {
            strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(222, 6, 0, 1));
          }
        strip.show();
        }
        else if(elapsed > TRANSITION_TIME * .96 & elapsed < TRANSITION_TIME * .97) {
         int index = i;
           for(int i = 0; i < 2; i++) {
            strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(189, 12, 0, 2));
           }
          strip.show();
        }
        else if(elapsed > TRANSITION_TIME *.97 & elapsed < TRANSITION_TIME * .98) {
         int index = i;
           for(int i = 0; i < 2; i++) {
            strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(156, 18, 0, 3));
           }
          strip.show();
        }
        else if(elapsed > TRANSITION_TIME *.98 & elapsed < TRANSITION_TIME *.99) {
         int index = i;
           for(int i = 0; i < 2; i++) {
            strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(123, 24, 0, 4));
           }
          strip.show();
        }

      //End of the line
      if(elapsed > TRANSITION_TIME) {
        int index = i;
        for(int i = 0; i < 2; i++) {
          strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(90, 30, 0, 5));
        }
        strip.show();

        // Do Housekeeping.
        keyOffHousekeeping(i);
      }
    }
  }
}

// keyOn and keyOff housekeeping tasks.
void keyOnHousekeeping(int key) {
  if(colorSteps > 5) {
    colorSteps = 0;
  }
  colorSteps++;
  keyBuffer[key].runOnce = true;
}
void keyOffHousekeeping(int i) {
  keyBuffer[i].recentlyReleased = false;
  keyBuffer[i].lastReleased = 0;
 // currKeyColor[i].r = currKeyColor[i].g = currKeyColor[i].b = CurrKeyColor[i].w = 0;
}

void stripOn(uint32_t color) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();  
}

void colorDefinitions() {
  // (colorDefs[x].r, colorDefs[x].g, colorDefs[x].b, colorDefs[x].w)
  // 0 = Color Corrected Warm White
  // 1 = RGBW Cool White
  colorDefs[0].r = 255; colorDefs[0].g = 140; colorDefs[0].b = 100; colorDefs[0].w = 0;
  colorDefs[1].r = 0; colorDefs[1].g = 0; colorDefs[1].b = 70; colorDefs[1].w = 255;
}

void colorFucker(byte r, byte g, byte b, byte w) {
  //Run all the values through the white balancer and round them.
  r = round(whiteBalance[WHITE_BALANCE].r * r);
  g = round(whiteBalance[WHITE_BALANCE].g * g);
  b = round(whiteBalance[WHITE_BALANCE].b * b);
  w = round(whiteBalance[WHITE_BALANCE].w * w);
  
  //Make sure there are no negative numbers.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}

  //Gamma Correct the resulting values.
  r = pgm_read_byte(&gamma8[r]);
  g = pgm_read_byte(&gamma8[g]);
  b = pgm_read_byte(&gamma8[b]);

  //color sharing
  //Theoretically you can use pure white to make up for this value, making clearer colors and reducing energy use.
  //By a series of devlish challenges, determine the smallest color value.
  int smallest;
  if(r < g && r < b && r < w) {smallest = r;} else if (g < r && g < b && g < w)  {smallest = g;} else if (b < r && b < g && b < w) {smallest = b;} else {smallest = w;}

  //Take the group's lowest common denomenator and remove it.
  r = r - smallest;
  g = g - smallest;
  b = b - smallest;
  w = w - smallest;

  //Or this I guess https://stackoverflow.com/questions/21117842/converting-an-rgbw-color-to-a-standard-rgb-hsb-representation
  //M = max(Ri,Gi,Bi)
  //m = min(Ri,Gi,Bi)
  
  //Wo = if (m/M < 0.5) use ( (m*M) / (M-m) ) else M 
  //Q = 255
  //K = (Wo + M) / m
  //Ro = floor( [ ( K * Ri ) - Wo ] / Q )
  //Go = floor( [ ( K * Gi ) - Wo ] / Q )
  //Bo = floor( [ ( K * Bi ) - Wo ] / Q )
  
  
  //Check for negatives.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}
  
  return;
  
}
