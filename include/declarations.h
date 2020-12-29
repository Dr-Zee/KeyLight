//Primary key data
keyState  keyBuffer[88];

//Active Color Values
colorDef keyColor, 
         bgColor;

//Saved color values for fade reference.
colorDef prevKeyColor[88], 
         prevBgColor[88];

//Define a set of custom colors
colorDef colorDefs[20];

//White Balance Profiles
whiteBalances whiteBalance[5];

//For tracking fade steps
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
boolean reset, 
        hueButton, 
        brightnessButton, 
        saturationButton = false;

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