// Primary key data
keyState  keyBuffer[88];

// Active Color Values
colorDef keyColor, 
         bgColor;

// Saved color values for fade reference.
colorDef prevKeyColor[88], 
         prevBgColor[88];

// Define a set of custom colors
colorDef colorDefs[20];

// White Balance Profiles
whiteBalances whiteBalance[5];

// For tracking fade steps
timers  pixelTimers, 
        rgbwSteps;

// USB
USB Usb;
USBH_MIDI  Midi(&Usb);
boolean bFirst;
uint16_t pid, vid;

// Variables
byte event, key;

// Store time since last toggle press
uint32_t hueButtonTimer, saturationButtonTimer, brightnessButtonTimer;

// Buttons
#define p_reset -1
#define e_button1 26
#define e_button2 32
#define e_button3 15
#define e_button4 13

// SSD 1306 OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Encoders
ESP32Encoder encoder1;
ESP32Encoder encoder2;
ESP32Encoder encoder3;
ESP32Encoder encoder4;

//Encoder Counts
uint16_t count1 = 0;
uint16_t count2 = 0;
uint16_t count3 = 0;
uint16_t count4 = 0;
uint16_t oldCount1 = 0;
uint16_t oldCount2 = 0;
uint16_t oldCount3 = 0;
uint16_t oldCount4 = 0;

// Encoder Button Toggles
bool    button1State = 1;
bool    button2State = 1;
bool    button3State = 1;
bool    button4State = 1;

// Store time since last input update
uint32_t lastInputChange;