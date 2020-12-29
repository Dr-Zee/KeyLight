// Set default key data.
void setDefaultData() 
{
  for (int i = 1; i < 88; i++) 
  {

    //the 88th key only has one LED... intentionally.
    if(i == 88) 
    {
      keyBuffer[i].keyLight[0] = keyBuffer[i].keyLight[1] = 176;
    }
    keyBuffer[i].keyLight[0] = (i * 2) - 2;
    keyBuffer[i].keyLight[1] = keyBuffer[i].keyLight[0] + 1;
    keyBuffer[i].isDown = keyBuffer[i].recentlyReleased = keyBuffer[i].runOnce = false;

    // Set previous bg color as current bg color, mainly for future proofing
    prevBgColor[i].r = bgColor.r; prevBgColor[i].g = bgColor.g; prevBgColor[i].b = bgColor.b; prevBgColor[i].w = bgColor.w;
  }
}

// Initialize light strip.
void initializeStrip() 
{
  strip.begin();
  for(int i=0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, strip.Color(bgColor.r, bgColor.g, bgColor.b, bgColor.w));
  }
  strip.show();
}

// Set event properties.
void setEventProperties(byte key, byte event) 
{
  if (event == 9) 
  {
    keyBuffer[key].isDown = true;
    keyBuffer[key].recentlyReleased = keyBuffer[key].runOnce = false;
  }
  if (event == 8) 
  {
    keyBuffer[key].runOnce = keyBuffer[key].recentlyReleased = true;
    keyBuffer[key].isDown = false;
    keyBuffer[key].lastReleased = millis();
  }
}

void readInputs()
{
  // Booleans
  onOff =             digitalRead(p_onOff);
  reset =             digitalRead(p_reset);
  hueButton =         digitalRead(p_hueButton);
  brightnessButton =  digitalRead(p_brightnessButton);
  saturationButton =  digitalRead(p_saturationButton);

  // First attempt at a non-blocking toggle button.
  // Debounce by accepting the first HIGH signal and not reading again for 500 milliseconds. 
  // Then, reset the button timer and read the button.
  if(readHueButton == true) {
    if(digitalRead(p_hueButton) == HIGH)
    {
      hueSelect = !hueSelect;
      readHueButton = false;
      hueButtonTimer = millis();
    }
  }
  if(millis() - hueButtonTimer >= toggleButtonTimeout) 
  {
    readHueButton = true;
    hueButtonTimer = 0;
  }

  int32_t newHuePosition = 0;
  int32_t newBrightnessPosition = 0;
  int32_t newSaturationPosition = 0;

  if(newHuePosition != huePosition) 
  {
    huePosition = newHuePosition;
    Serial.print("New hue position: ");
    Serial.print(newHuePosition);
    Serial.println("");
  }
  if(newBrightnessPosition != brightnessPosition) 
  {
    brightnessPosition = newBrightnessPosition;
    Serial.print("New brightness position: ");
    Serial.print(newBrightnessPosition);
    Serial.println("");
  }
  if(newSaturationPosition != saturationPosition) 
  {
    saturationPosition = newSaturationPosition;
    Serial.print("New saturation position: ");
    Serial.print(newSaturationPosition);
    Serial.println("");
  }
}

// Midi Listener.
void MIDI_poll() 
{
  uint8_t bufMidi[64];
  uint16_t  rcvd;
  if ((Midi.vid != vid) | (Midi.pid != pid)) 
  {
    vid = Midi.vid;
    pid = Midi.pid;
  }
  if (Midi.RecvData( &rcvd,  bufMidi) == 0 ) 
  {
    event = bufMidi[0];

    // Unused but useful.
    // Channel = bufMidi[1];
    // Velocity = bufMidi[3];
    if ((event == 8) | (event == 9)) 
    {
      key = bufMidi[2] - 20;
      setEventProperties(key, event);
    }
  }
}

// Push a color to the keys only once.
void keyStrikes(byte key) 
{
  if((keyBuffer[key].isDown == true) & (keyBuffer[key].runOnce == false)) 
  {
    for(int i = 0; i < 2; i++) 
    {
      strip.setPixelColor(keyBuffer[key].keyLight[i], strip.Color(keyColor.r, keyColor.g, keyColor.b, keyColor.w));

      // Set this as the previous pixel color for use in the fade.
      prevKeyColor[i].r = keyColor.r; prevKeyColor[i].g = keyColor.g; prevKeyColor[i].b = keyColor.b; prevKeyColor[i].w = keyColor.w;
    }
    strip.show();

    // Do Housekeeping.
    keyOnHousekeeping(key);
  }
}

// Fade out loop for non-blocking transitions out.
void theBigFade() 
{
  for (int i = 1; i < 88; i++) 
  {
    if(keyBuffer[i].recentlyReleased == true) 
    {
      
      // Time since keyUp
      uint32_t elapsed = millis() - keyBuffer[i].lastReleased;

      if((elapsed >= fadeDelay)) 
      {

        // Run the fade.
        colorFade(fadeDuration, fadeDelay, i);
      }
    }
  }
}

void colorDefinitions() 
{

  // (colorDefs[x].r, colorDefs[x].g, colorDefs[x].b, colorDefs[x].w)
  // 0 = Color Corrected Warm White
  // 1 = RGBW Cool White
  colorDefs[0].r = 255; colorDefs[0].g = 140; colorDefs[0].b = 100; colorDefs[0].w = 0;
  colorDefs[1].r = 0; colorDefs[1].g = 0; colorDefs[1].b = 70; colorDefs[1].w = 255;
}

// void HSBtoRGB() 
// {
//   float fract(float x) 
//   {
//     return x - int(x);
//   }

//   float mix(float a, float b, float t) 
//   {
//     return a + (b - a) * t; 
//   }

//   float step(float e, float x) 
//   {
//     return x < e ? 0.0 : 1.0; 
//   }

//   float* hsv2rgb(float h, float s, float b, float* rgb) 
//   {
//     rgb[0] = b * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
//     rgb[1] = b * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
//     rgb[2] = b * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
//     return rgb;
//   }
// }

void colorFucker(byte r, byte g, byte b, byte w) 
{

  //Run all the values through the white balancer and round them.
  r = round(whiteBalance[WHITE_BALANCE].r * r);
  g = round(whiteBalance[WHITE_BALANCE].g * g);
  b = round(whiteBalance[WHITE_BALANCE].b * b);
  w = round(whiteBalance[WHITE_BALANCE].w * w);

  //Make sure there are no negative numbers.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}

  //Gamma Correct the resulting values.
  r = pgm_read_byte(&gamma8[r]);
  g = pgm_read_byte(&gamma8[g]);
  b = pgm_read_byte(&gamma8[b]);

  //color sharing
  //By a series of devlish challenges, determine the smallest color value.
  int smallest;
  if(r < g && r < b && r < w) {smallest = r;} else if (g < r && g < b && g < w)  {smallest = g;} else if (b < r && b < g && b < w) {smallest = b;} else {smallest = w;}

  //Take the group's lowest common denomenator and remove it.
  r = r - smallest;
  g = g - smallest;
  b = b - smallest;
  w = w - smallest;

  //Or this I guess https://stackoverflow.com/questions/21117842/converting-an-rgbw-color-to-a-standard-rgb-hsb-representation
  //M = max(Ri,Gi,Bi)
  //m = min(Ri,Gi,Bi)

  //Wo = if (m/M < 0.5) use ( (m*M) / (M-m) ) else M
  //Q = 255
  //K = (Wo + M) / m
  //Ro = floor( [ ( K * Ri ) - Wo ] / Q )
  //Go = floor( [ ( K * Gi ) - Wo ] / Q )
  //Bo = floor( [ ( K * Bi ) - Wo ] / Q )


  //Check for negatives.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}
}