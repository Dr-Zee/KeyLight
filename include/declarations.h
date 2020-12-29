//Primary key data
keyState  keyBuffer[88];

//Active Color Values
colorDef keyColor;
colorDef bgColor;

//Saved color values for fade reference.
colorDef prevKeyColor[88];
colorDef prevBgColor[88];

//Define a set of custom colors
colorDef colorDefs[20];

//White Balance Profiles
whiteBalances whiteBalance[5];

//For tracking fade steps
timers pixelTimers;
timers rgbwSteps;

// LEDs
#define LED_PIN 8
#define LED_COUNT  175
#define BRIGHTNESS 10
#define TRANSITION_TIME 900

//Choose a white balance profile.
//0 = Cool Blue
//1 - Hot & Heavy
byte WHITE_BALANCE = 0;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// USB
USB Usb;
USBH_MIDI  Midi(&Usb);
boolean bFirst;
uint16_t pid, vid;

// Variables
byte event;
byte key;

// Sets number of skip keys for multicolor patterns
byte colorSkips = 1;

// Delay variables
uint32_t fadeDelay;
uint32_t fadeDuration;

// Buttons
#define p_onOff 17
#define p_reset 3
#define p_hueButton 18
#define p_brightnessButton 21
#define p_saturationButton 24

// Define global input variables
boolean onOff = true;
boolean reset = false;
boolean hueButton = false;
boolean brightnessButton = false;
boolean saturationButton = false;
uint16_t bgHue = 0;
uint16_t keyHue = 0;
uint16_t bgBrightness = 0;
uint16_t keyBrightness = 0;
uint16_t bgSaturation = 0;
uint16_t keySaturation = 0;

// Reset encoders
int32_t huePosition = -999;
int32_t brightnessPosition = -999;
int32_t saturationPosition = -999;

MD_REncoder hue = MD_REncoder(21, 22);
MD_REncoder brightness = MD_REncoder(25, 26);
MD_REncoder saturation = MD_REncoder(32, 33);