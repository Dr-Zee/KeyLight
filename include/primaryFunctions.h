// Set default key data.
void setDefaultData() 
{
  // Get EEPROM values
  retrieveMemory();

  // Set the OLED program messages in memory
  setMessages();

  for (int i = 1; i < 88; i++) 
  {
    
    //the 88th key only has one LED... intentionally.
    if(i == 88) 
    {
      keyBuffer[i].keyLight[0] = keyBuffer[i].keyLight[1] = 176;
    }
    //set each key's LED light numbers
    keyBuffer[i].keyLight[0] = (i * 2) - 2;
    keyBuffer[i].keyLight[1] = keyBuffer[i].keyLight[0] + 1;
    //Initialize all key settings to off
    keyBuffer[i].isDown = keyBuffer[i].recentlyReleased = keyBuffer[i].runOnce = false;

    // set the previous colors from memory
    prevKeyColor[i] = colorProcessor(program[1].val[0], program[1].val[1], program[1].val[2]);
    prevBgColor[i] = colorProcessor(program[0].val[0], program[0].val[1], program[0].val[2]);
  }
}

// Initialize light strip.
void initializeKeyStrip() 
{
  strip.begin();
  for(int i=0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, prevBgColor[i]);
  }
  strip.show();
}

void initializeProgramStrip() 
{

  // Initialize Program Strip
  programstrip.begin();

  // Set BG indicators
  programstrip.setPixelColor(0, prevBgColor[1]);
  programstrip.setPixelColor(1, prevBgColor[1]);

  // Set Key indicators
  programstrip.setPixelColor(2, prevKeyColor[1]);
  programstrip.setPixelColor(3, prevKeyColor[1]);
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
    keyBuffer[key].lastReleased = esp_timer_get_time();
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

// Update colors
void updateColors(uint16_t hue, uint16_t saturation, uint16_t luminance) 
{
  if (systemData.activeProgram == 0) 
  {
    for (int i = 1; i < strip.numPixels(); i++) 
    {
      strip.setPixelColor(i, colorProcessor(hue, saturation, luminance));
      prevBgColor[i] = colorProcessor(hue, saturation, luminance);
    }
    strip.show();

    // Set Background Program LEDs indicators
    programstrip.setPixelColor(0, colorProcessor(hue, saturation, luminance));
    programstrip.setPixelColor(1, colorProcessor(hue, saturation, luminance));
    programstrip.show();
  }
  if (systemData.activeProgram == 1) 
  {
    for (int i = 1; i < strip.numPixels(); i++) 
    {
      prevKeyColor[i] = colorProcessor(hue, saturation, luminance);
    }
    // Set Key Program LED indicators
    programstrip.setPixelColor(2, colorProcessor(hue, saturation, luminance));
    programstrip.setPixelColor(3, colorProcessor(hue, saturation, luminance));
    programstrip.show();
  }
}

// Push a color to the keys only once.
void keyStrikes(byte key) 
{
  if((keyBuffer[key].isDown == true) & (keyBuffer[key].runOnce == false)) 
  {
    for(int i = 0; i < 2; i++) 
    {
      strip.setPixelColor(keyBuffer[key].keyLight[i], colorProcessor(program[1].val[0], program[1].val[1], program[1].val[2]));
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
      if((timeKeeper(keyBuffer[i].lastReleased) >= program[1].val[3])) 
      {
        // Run the fade.
        colorFade(prevKeyColor[i], prevBgColor[i], program[0].val[3], program[1].val[3], i);
      }
    }
  }
}