// Adjustable variables

// LEDs
#define LED_PIN 4
#define LED_COUNT  176

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// Program LEDs
#define PROGRAM_LED_PIN 2
#define PROGRAM_LED_COUNT 4

Adafruit_NeoPixel programstrip(PROGRAM_LED_COUNT, PROGRAM_LED_PIN, NEO_GRBW + NEO_KHZ800);

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

// Amount of time before the display returns to the logo.
uint16_t logoDelay = 4000;