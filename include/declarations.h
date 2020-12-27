// LEDs
#define LED_PIN     8
#define LED_COUNT  175
#define BRIGHTNESS 10
#define TRANSITION_TIME 900

//Choose a white balance profile.
//0 = Cool Blue
//1 - Hot & Heavy
#define WHITE_BALANCE 0

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

// USB
USB Usb;
USBH_MIDI  Midi(&Usb);
void MIDI_poll();
boolean bFirst;
uint16_t pid, vid;

// Variables
byte event;
byte key;
byte colorSteps = 1;