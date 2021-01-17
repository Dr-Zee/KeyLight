#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <ESP32Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Libraries
#include <usbhub.h>
#include <usbh_midi.h>
#include <MD_REncoder.h>
#include <Adafruit_NeoPixel.h>

// Datastructure
#include <dataStructure.h>
#include <declarations.h>
#include <adjustableVariables.h>

// Functions
#include <housekeepingFunctions.h>
#include <colorFunctions.h>
#include <stepFadeFunctions.h>
#include <primaryFunctions.h>
#include <OLEDFunctions.h>

void setup() 
{
  Serial.begin(115200);

  // Inputs
  // Booleans
  pinMode(p_onOff, INPUT);
  pinMode(p_reset, INPUT);
  pinMode(p_hueButton, INPUT);
  pinMode(p_brightnessButton, INPUT);
  pinMode(p_saturationButton, INPUT);

  // Encoders
  pinMode(21, INPUT);
  pinMode(22, INPUT);
  pinMode(25, INPUT);
  pinMode(26, INPUT);
  pinMode(32, INPUT);
  pinMode(33, INPUT);

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

  // Initialize Encoder.
  ESP32Encoder::useInternalWeakPullResistors=UP;
  encoder.attachHalfQuad(25, 26);
  encoder.setCount(0);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  //Initialize Display
  showLogo();

  // Set default Data
  setDefaultData();

  //Get USB Data
  if (Usb.Init() == -1) 
  {
      while (1); //halt
  }

  delay(200);
  
  // Initialize lights
  initializeStrip();
}

void loop()
{
  //Read Inputs
  readInputs();
  programstrip.show();

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
    displayController();
  }
}
