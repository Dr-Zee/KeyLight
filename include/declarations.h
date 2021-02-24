// Global data
master  systemData;

// Encoder Data
counts  count[4];

// Program Data
programs program[5];

// Primary key data
keyState  keyBuffer[88];

// Stored color values
uint32_t prevKeyColor[88];
uint32_t prevBgColor[88];

// Tracking fade steps
timers  pixelTimers[88];
timers  rgbwSteps[88];

// White balance profiles
whiteBalances   whiteBalance[4];

// Key LEDs
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

// Buttons
#define p_reset -1
#define e_button1 15
#define e_button2 13
#define e_button3 26
#define e_button4 32

// EEPROM size in bytes
#define EEPROM_SIZE 1024

// EEPROM Addresses. 
// Ordered activeProgram, P1: hsld (2, 2, 2, 2), p2: hsld  (2, 2, 2, 2) etc.
uint8_t address[10] = {0, 2, 4, 6, 8, 10, 12, 14, 16};

