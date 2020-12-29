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