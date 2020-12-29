// Adjustable variables

// LEDs
#define LED_PIN 8
#define LED_COUNT  175
#define BRIGHTNESS 10

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Set length of delay before fade and length of fade.
uint32_t fadeDelay = 900;
uint32_t fadeDuration = 900;

// Choose a white balance profile.
// 0 = Cool Blue
// 1 - Hot & Heavy
byte WHITE_BALANCE = 0;

// When the encoder toggle is clicked, the program will wait this many 
// milliseconds before registering another click.
uint16_t toggleButtonTimeout = 500;

// Sets number of skip keys for multicolor patterns (Not yet implemented.)
byte colorSkips = 1;

// Define a set of custom colors (not yet implemented.)
void colorDefinitions() 
{
  // (colorDefs[x].r, colorDefs[x].g, colorDefs[x].b, colorDefs[x].w)
  // 0 = Color Corrected Warm White
  // 1 = RGBW Cool White
  colorDefs[0].r = 255; colorDefs[0].g = 140; colorDefs[0].b = 100; colorDefs[0].w = 0;
  colorDefs[1].r = 0; colorDefs[1].g = 0; colorDefs[1].b = 70; colorDefs[1].w = 255;
}

// Sets logarithmic divisor for rotary encoders. (not yet implemented)
byte encoderSpeedDivisor = 10;