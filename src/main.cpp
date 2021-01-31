#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

// Libraries
#include <usbhub.h>
#include <usbh_midi.h>
#include <ESP32Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <MD_REncoder.h>
#include <Adafruit_NeoPixel.h>

// Datastructure
#include <dataStructure.h>
#include <declarations.h>
#include <adjustableVariables.h>

// Functions
#include <housekeepingFunctions.h>
//#include <colorFunctions.h>
#include <stepFadeFunctions.h>
#include <primaryFunctions.h>
#include <OLEDFunctions.h>
#include <encoderFunctions.h>

void setup() 
{
  Serial.begin(115200);

  // Inputs
  // Booleans
  pinMode(e_button1, INPUT);
  pinMode(e_button2, INPUT);
  pinMode(e_button3, INPUT);
  pinMode(e_button4, INPUT);

  pinMode(14, INPUT);
  pinMode(27, INPUT);
  pinMode(25, INPUT);
  pinMode(33, INPUT);
  pinMode(35, INPUT);
  pinMode(34, INPUT);
  pinMode(36, INPUT);
  pinMode(39, INPUT);

  // Outputs
  pinMode(LED_PIN, OUTPUT);
  pinMode(PROGRAM_LED_PIN, OUTPUT);

  bFirst = true;
  vid = pid = 0;

  // Initialize Encoder.
  initializeEncoders();

  // Make sure the display is working.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  // Initialize Display.
  showLogo();

  // Set default Data.
  setDefaultData();

  // Get USB Data
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
encoderProgram();
  // Initialize USB.
  Usb.Task();
  if ( Usb.getUsbTaskState() == USB_STATE_RUNNING ) 
  {

    // Listen for Midi.
    MIDI_poll();

    // Light the keys.
    keyStrikes(key);

    // Debounce the event.
    if(event != 0) 
    {
     event = 0;
    }

    // Do the big fade.
    theBigFade();
    //displayController();
  }
}
