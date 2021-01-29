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
  programstrip.begin();
  for(int i=0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, strip.Color(bgColor.r, bgColor.g, bgColor.b, bgColor.w));
  }
  for(int i=0; i < programstrip.numPixels(); i++) 
  {
    programstrip.setPixelColor(i, programstrip.Color(bgColor.r, bgColor.g, bgColor.b, bgColor.w));
  }
  strip.show();
  programstrip.show();
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

      strip.setPixelColor(keyBuffer[key].keyLight[i], strip.Color(0, 30, 90, 20));

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