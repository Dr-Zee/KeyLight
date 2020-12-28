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

// Inputs
// Buttons and encoders
#define p_onOff 17
#define p_reset 3

// Hue
#define p_hueButton 18
#define p_bgHue 19
#define p_keyHue 20

// Brightness
#define p_brightnessButton 21
#define p_bgBrightness 22
#define p_keyBrightness 23

// Saturation
#define p_saturationButton 24
#define p_keySaturation 25
#define p_bgSaturation 26

boolean onOff;
boolean reset;
boolean hueButton;
uint16_t bgHue;
uint16_t keyHue;
boolean brightnessButton;
uint16_t bgBrightness;
uint16_t keyBrightness;
boolean saturationButton;
uint16_t bgSaturation;
uint16_t keySaturation;