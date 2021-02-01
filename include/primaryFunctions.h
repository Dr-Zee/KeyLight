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
  }
}

// Initialize light strip.
void initializeStrip() 
{
  strip.begin();
  programstrip.begin();
  for(int i=0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, colorProcessor(count1, count2, count3));
  }
  for(int i=0; i < programstrip.numPixels(); i++) 
  {
    programstrip.setPixelColor(i, colorProcessor(count1, count2, count3));
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

    // Unused
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
      strip.setPixelColor(keyBuffer[key].keyLight[i], keyColor);
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
        colorFade(prevBgColor[i], prevKeyColor[i], fadeDuration, fadeDelay, i);
      }
    }
  }
}