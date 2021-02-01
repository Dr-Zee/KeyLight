// Primary key data
keyState  keyBuffer[88];

// Active Color Values
uint32_t keyColor, 
         bgColor;
         
uint32_t prevKeyColor[88];
uint32_t prevBgColor[88];

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

// EEPROM size in bytes
#define EEPROM_SIZE 90

//Encoder Counts
uint16_t count1, oldCount1, count4, oldCount4;
uint8_t  count2, count3, oldCount2, oldCount3;

// Encoder Button and program booleans.
bool    btn1_down = false;
bool    btn2_down = false;
bool    btn3_down = false;
bool    btn4_down = false;

bool dataSaved = true;

// Programs
// DEFAULT - 0 - BG Color Selection
bool    prg[8] = {true, false, false, false, false, false, false, false};

// Store time since last input update
uint32_t lastInputChange;