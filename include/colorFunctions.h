// Get the RGBW values from a packed 32bit value.
uint8_t White(uint32_t color)
{
  return (color >> 24) & 0xFF;
}
uint8_t Red(uint32_t color)
{
  return (color >> 16) & 0xFF;
}
uint8_t Green(uint32_t color)
{
  return (color >> 8) & 0xFF;
}
uint8_t Blue(uint32_t color)
{
  return color & 0xFF;
}

uint32_t colorProcessor(uint16_t hue, uint8_t sat, uint8_t val) 
{

  // Get the Gamma corrected, RGB converted, 32bit packed color value from the encoder values
  uint32_t RGB = strip.gamma32(strip.ColorHSV(hue, sat, val));

  // Isolate the RGB values
  uint8_t r = Red(RGB);
  uint8_t g = Green(RGB);
  uint8_t b = Blue(RGB);
  uint8_t w = 0;

  // Get the lowest common denemenator and assign that value to white.
  int smallest = 0;
  if(r <= g && r <= b) {smallest = r;} else if (g <= r && g <= b)  {smallest = g;} else if (b <= r && b <= g) {smallest = b;}

  //Take the group's lowest common denomenator and remove it.
  r = r - smallest;
  g = g - smallest;
  b = b - smallest;
  w = smallest;

  // White balance the result
  //r = whiteBalance[0].r + r; g = whiteBalance[0].g + g; b = whiteBalance[0].b + b; w = whiteBalance[0].w + w;

  //Check for negatives.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}

  // Pack and return the result.
  return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

