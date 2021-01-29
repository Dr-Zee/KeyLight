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
#define p_hueButton 26
#define p_brightnessButton 32
#define p_saturationButton 15
#define p_durationButton 13

// Define global input variables
boolean hueButton, 
        brightnessButton, 
        saturationButton,
        durationButton = false;

// Toggle Buttons
boolean readHueButton, 
        readSaturationButton, 
        readBrightnessButton = true;

// Program select
boolean hueSelect, 
        saturationSelect, 
        brightnessSelect, 
        fadeSpeedSelect = false;

//Encoder values
uint16_t bgHue, 
        keyHue, 
        bgBrightness, 
        keyBrightness, 
        bgSaturation, 
        keySaturation = 0;

// Reset encoders
int32_t huePosition, 
        brightnessPosition, 
        saturationPosition = -999;

// SSD 1306 OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Demo Encoder
ESP32Encoder encoder1;
ESP32Encoder encoder2;
ESP32Encoder encoder3;
ESP32Encoder encoder4;

uint16_t count1,
         count2,
         count3,
         count4,
         oldCount1,
         oldCount2,
         oldCount3,
         oldCount4 = 0;

uint16_t oldCount = 0;
uint32_t lastChange = 0;