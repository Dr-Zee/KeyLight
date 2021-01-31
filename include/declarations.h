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

// Buttons
#define p_reset -1
#define e_button1 15
#define e_button2 13
#define e_button3 32
#define e_button4 26

//Encoder Counts
uint16_t count1;
uint8_t count2;
uint8_t count3;
float count4;
uint16_t oldCount1;
uint8_t oldCount2;
uint8_t oldCount3;
float oldCount4;

// Encoder Button and program booleans.
bool    btn1_down = false;
bool    btn2_down = false;
bool    btn3_down = false;
bool    btn4_down = false;

// Programs
// Key 1
// DEFAULT - BG Color Selection
bool    btn1_prg1 = true;
// Key Color Selection
bool    btn1_prg2 = false;

// Key 2
bool    btn2_prg1 = false;
bool    btn2_prg2 = false;

// Key 3
bool    btn3_prg1 = false;
bool    btn3_prg2 = false;

//Key 4
// Fade duration
bool    btn4_prg1 = false;
// Fade Delay
bool    btn4_prg2 = false;

// Store time since last toggle press
uint32_t btn1_timer, btn2_timer, btn3_timer, btn4_timer;


// Encoder Button Toggles
bool    button1State = 1;
bool    button2State = 1;
bool    button3State = 1;
bool    button4State = 1;

// Store time since last input update
uint32_t lastInputChange;