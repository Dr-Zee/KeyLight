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

// USB
USB Usb;
USBH_MIDI  Midi(&Usb);
boolean bFirst;
uint16_t pid, vid;

// Variables
byte event;
byte key;

// Store time since last toggle press
uint32_t hueButtonTimer;
uint32_t saturationButtonTimer;
uint32_t brightnessButtonTimer;


// Buttons
#define p_onOff 17
#define p_reset 3
#define p_hueButton 18
#define p_brightnessButton 21
#define p_saturationButton 24

// Encoders
MD_REncoder hue = MD_REncoder(21, 22);
MD_REncoder brightness = MD_REncoder(25, 26);
MD_REncoder saturation = MD_REncoder(32, 33);

// Define global input variables
boolean onOff = true;
boolean reset = false;
boolean hueButton = false;
boolean brightnessButton = false;
boolean saturationButton = false;

// Toggle Buttons
boolean readHueButton = true;
boolean readSaturationButton = true;
boolean readBrightnessButton = true;

// Program select
boolean hueSelect = false;
boolean saturationSelect = false;
boolean brightnessSelect = false;

//Encoder values
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