//  Arduino Compatibility in PlatformIO
#include <Arduino.h>
//  SSD1306 OLED I2C
#include <Wire.h>
//  USB Host shield 2.0 SPI
#include <SPI.h>
//  Flash Memory access
#include <EEPROM.h>
unsigned long tempTimer = 0;

//  Libraries
#include <usbhub.h>
#include <usbh_midi.h>
#include <ESP32Encoder.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

// Datastructure
#include <dataStructure.h>
#include <declarations.h>

// Functions
#include <colorFunctions.h>
#include <eepromFunctions.h>
#include <OLEDFunctions.h>
#include <helperFunctions.h>
#include <stepFadeFunctions.h>
#include <systemFunctions.h>
#include <encoderFunctions.h>


//  Fade Manager - Runs on Core 0
void LEDThreadTask( void* ){
  //  Create an infinite loop
  for(;;) {

    //  Do the big fade.
    theBigFade();

    //  Delay keeps watchdog from calling the task idle and rebooting.
    vTaskDelay(10);
  }
}

//  Initialize
void setup() 
{
  Serial.begin(115200);

  EEPROM.begin(EEPROM_SIZE);
  if (!EEPROM.begin(1000)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }

  //  Inputs
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

  //  Outputs
  pinMode(LED_PIN, OUTPUT);
  pinMode(PROGRAM_LED_PIN, OUTPUT);

  bFirst = true;
  vid = pid = 0;

  //  Set default Data.
  setDefaultData();

  //  Initialize Encoders.
  initializeEncoders();

  //  Make sure the display is working.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  //  Initialize lighting task for core 0
  xTaskCreatePinnedToCore(LEDThreadTask, "The Big Fade", 1000, NULL, 1, NULL, 0);

  //  Initialize Display.
  showLogo();

  //  Initialize USB
  if (Usb.Init() == -1) 
  {
    while (1); //halt
  }
  delay(200);
  
  //  Initialize lights
  initializeProgramStrip();
  initializeKeyStrip();
}

//  Input/Program Manager - Runs on Core 1
//  Monitors all Inputs, sets global values, controls OLED.
void loop()
{
  // Check Inputs.
  encoderProgram();

  // Run USB.
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
  }

  // Rest
  displayRest();
}