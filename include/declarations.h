// Primary key data
keyState  keyBuffer[88];

uint32_t prevKeyColor[88];
uint32_t prevBgColor[88];

// For tracking fade steps
timers  pixelTimers[88];
timers  rgbwSteps[88];

// White Balance Profiles
byte WHITE_BALANCE = 0;
whiteBalances whiteBalance[5] {

    // Cool Ranch
    whiteBalance[0].r = 0,
    whiteBalance[0].g = 20,
    whiteBalance[0].b = 20,
    whiteBalance[0].w = 0,

    // Hot & Heavy
    whiteBalance[1].r = 10,
    whiteBalance[1].g = 0,
    whiteBalance[1].b = 30,
    whiteBalance[1].w = 0
};

// LEDs
#define LED_PIN 4
#define LED_COUNT  176

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Program LEDs
#define PROGRAM_LED_PIN 2
#define PROGRAM_LED_COUNT 4

Adafruit_NeoPixel programstrip(PROGRAM_LED_COUNT, PROGRAM_LED_PIN, NEO_GRBW + NEO_KHZ800);

// USB
USB Usb;
USBH_MIDI  Midi(&Usb);
boolean bFirst;
uint16_t pid, vid;

// MIDI event booleans.
byte event, key;

// SSD 1306 OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
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
#define e_button3 26
#define e_button4 32

// EEPROM size in bytes
#define EEPROM_SIZE 1024

//Encoder Counts
uint16_t count1, oldCount1, count4, oldCount4;
uint8_t  count2, count3, oldCount2, oldCount3;

program programs[4] {
    programs[0].active = true, 
    programs[1].active = false, 
    programs[2].active = false, 
    programs[3].active = false
    };

// EEPROM Addresses. Ordered p1: hslda, p2: hslda p3: hslda
uint8_t address[15] = {8, 10, 11, 12, 14, 15, 17, 18, 19, 21, 22, 24, 25, 26};

// Encoder Button and program booleans.
bool    btnDown[4] = {false};
bool    dataSaved = true;

// Store time since last input update
int64_t lastInputChange;

// DEPRECATED
// Set length of delay before fade and length of fade.
int64_t fadeDelay = 900;
int64_t fadeDuration = 900;

// Amount of time before the display returns to the logo.
int64_t LOGO_DELAY = 1200;
int64_t SLEEP_DELAY = 12000;