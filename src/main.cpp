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
#include <housekeepingFunctions.h>
#include <stepFadeFunctions.h>
#include <primaryFunctions.h>

void setup()
{
  Serial.begin(115200);
  
  // Inputs
  // Booleans
  pinMode(p_onOff, INPUT);
  pinMode(p_reset, INPUT);
  pinMode(p_hueButton, );
  pinMode(p_brightnessButton, INPUT);
  pinMode(p_saturationButton, INPUT);

  // Encoders
  pinMode(p_bgHue, INPUT);
  pinMode(p_keyHue, INPUT);
  pinMode(p_bgBrightness, INPUT);
  pinMode(p_keyBrightness, INPUT);
  pinMode(p_bgSaturation, INPUT);
  pinMode(p_keySaturation, INPUT);

  // Outputs
  pinMode(LED_PIN, OUTPUT);

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

  // Booleans
  onOff = true;
  reset = false;
  hueButton = false;
  brightnessButton = false;
  saturationButton = false;

  // Encoders
  bgHue = 0;
  keyHue = 0;
  bgBrightness = 0;
  keyBrightness = 0;
  bgSaturation = 0;
  keySaturation = 0;
  
  setDefaultData();
  if (Usb.Init() == -1) 
  {
    while (1); //halt
  }
  delay(200);
  initializeStrip();
}

void loop()
{
  //Read Inputs
  readInputs();

  // Initialize USB.
  Usb.Task();
  if ( Usb.getUsbTaskState() == USB_STATE_RUNNING ) 
  {

    // Listen for Midi.
    MIDI_poll();

    //  Light the keys.
    keyStrikes(key);

    // Debounce the event.
    if(event != 0) 
    {
     event = 0;
    }

    // Do the big fade.
    theBigFade();
  }
}
