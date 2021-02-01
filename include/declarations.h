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

// Store time since last input update
uint32_t lastInputChange;

//Program Strings
char bh[] = "Background Hue";
char bs[] = "Background Saturation";
char bl[] = "Background Luminance";
char kh[] = "Key Hue";
char ks[] = "Key Saturation";
char kl[] = "Key Luminance";
char fdel[] = "Fade Duration";
char fdur[] = "Fade Delay";
char bg[] = "Backround Color";
char ky[] = "Key Color";
char kskp[] = "Key Skips";