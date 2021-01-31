
// Get the RGB values from a packed 32bit value.
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


void colorProcessor(uint16_t hue, uint8_t sat, uint8_t val) 
{

  // Get the Gamma corrected, RGB converted, 32bit packed color value from the encoder values
  uint32_t processedRGB = strip.gamma32(strip.ColorHSV(hue, sat, val));

  // Isolate the RGB values
  uint8_t r = Red(processedRGB);
  uint8_t g = Green(processedRGB);
  uint8_t b = Blue(processedRGB);
  uint8_t w = 0;

  // Get the lowest common denemenator and assign that value to white.
  int smallest = 0;
  if(r <= g && r <= b) {smallest = r;} else if (g <= r && g <= b)  {smallest = g;} else if (b <= r && b <= g) {smallest = b;}

  //Take the group's lowest common denomenator and remove it.
  r = r - smallest;
  g = g - smallest;
  b = b - smallest;
  w = smallest;
  Serial.print("r: ");
  Serial.print(r);
  Serial.print(" g: ");
  Serial.print(g);
  Serial.print(" b: ");
  Serial.print(b);
  Serial.print(" w: ");
  Serial.print(w);

  // White balance the result
  //r = round(whiteBalance[WHITE_BALANCE].r * r);
  //g = round(whiteBalance[WHITE_BALANCE].g * g);
  //b = round(whiteBalance[WHITE_BALANCE].b * b);
  //w = round(whiteBalance[WHITE_BALANCE].w * w);

  //Check for negatives.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}
  return (r, g, b, w);
}