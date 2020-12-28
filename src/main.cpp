#include <Arduino.h>
#include <SPI.h>

// Libraries
#include <usbhub.h>
#include <usbh_midi.h>
#include <Adafruit_NeoPixel.h>

// Datastructure
#include <dataStructure.h>
#include <declarations.h>

// Functions
//#include <NeopixelFunctions.h>
#include <housekeepingFunctions.h>
#include <stepFadeFunctions.h>
#include <primaryFunctions.h>

void setup()
{
  Serial.begin(115200);
  bFirst = true;
  vid = pid = 0;

  //Temp Color Values
  bgColor.r = 0;
  bgColor.g = 0;
  bgColor.b = 0;
  bgColor.w = 0;

  keyColor.r = 0;
  keyColor.g = 0;
  keyColor.b = 0;
  keyColor.w = 0;

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

    //  Light the keys.
    keyStrikes(key);

    // Debounce the event.
    if(event != 0) {
     event = 0;
    }

    // Do the big fade.
    theBigFade();
  }
}
