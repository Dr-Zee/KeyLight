// Set default key data.
void setDefaultData() 
{
  // Get EEPROM values
  retrieveMemory();

  // Set the OLED program messages in memory
  setMessages();

  for (int i = 0; i < 88; i++) 
  {
    //set each key's LED light numbers
    keyBuffer[i].keyLight[0] = (i * 2) - 2;
    keyBuffer[i].keyLight[1] = keyBuffer[i].keyLight[0] + 1;
    //Initialize all key settings to off
    keyBuffer[i].isDown = keyBuffer[i].recentlyReleased = keyBuffer[i].runOnce = false;

    // set the previous colors from memory
    prevKeyColor[i]  = colorProcessor(program[1].val[0], program[1].val[1], program[1].val[2]);
    prevBgColor[i]   = colorProcessor(program[0].val[0], program[0].val[1], program[0].val[2]);
  }
}

// Initialize light strip.
void initializeKeyStrip() 
{
  strip.begin();
  for(int i = 0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, prevBgColor[1]);
  }
  strip.show();
}

void initializeProgramStrip() 
{

  // Initialize Program Strip
  programstrip.begin();

  // Set BG and Key colors
  for(int i = 0; i < 4; i++) {
    if (i < 2) {
      programstrip.setPixelColor(i, prevBgColor[1]);
    } else {
      programstrip.setPixelColor(i, prevKeyColor[1]);
    }
  }
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
    keyBuffer[key].isDown = false;
    keyBuffer[key].recentlyReleased = keyBuffer[key].runOnce = true;
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

// Color values and LED colors.
// Kept in the input loop so it will only fire if there is a change.
void updateValues() 
{
  uint32_t  color = colorProcessor(program[sys.active].val[0], program[sys.active].val[1], program[sys.active].val[2]);
  if (sys.active == 0) 
  {
     // Set Key Program LED indicators
    for (int i = 0; i < 2; i++) {
      programstrip.setPixelColor(i, colorProcessor(program[sys.active].val[0], program[sys.active].val[1], program[sys.active].val[2]));
    }
    programstrip.show();

    //  Set the new BG Color
    for (int i = 0; i < strip.numPixels(); i++) 
    {
      prevBgColor[i] = color;
      strip.setPixelColor(i, color);
    }
    strip.show();
  }
  if (sys.active == 1) 
  {
    // Set Key Program LED indicators
    for (int i = 2; i < 4; i++) {
      programstrip.setPixelColor(i, colorProcessor(program[sys.active].val[0], program[sys.active].val[1], program[sys.active].val[2]));
    }
    programstrip.show();

    //  Set the new Key Color
    for (int i = 0; i < strip.numPixels(); i++) 
    {
      prevKeyColor[i] = color;
    }
  }
}

// Push a color to the keys only once.
void keyStrikes(int key) 
{

  if((keyBuffer[key].isDown == true) & (keyBuffer[key].runOnce == false)) 
  {
    for(int i = 0; i < 2; i++) 
    {
      strip.setPixelColor(keyBuffer[key].keyLight[i], prevKeyColor[key]);
    }
    strip.show();
  }
  keyOnHousekeeping(key);
}

// Fade out loop for non-blocking transitions out.
void theBigFade() 
{
  for (int i = 0; i < 88; i++) 
  {
    if(keyBuffer[i].recentlyReleased == true) 
    {
      for (int j = 0; j < 2; j++) {
        strip.setPixelColor(keyBuffer[i].keyLight[j], prevBgColor[i]);
      }
      strip.show();
      // Time since keyUp
      if(timeKeeper(keyBuffer[i].lastReleased) >= program[1].val[3] * 1000) 
      {
        // Run the fade.
        //colorFade(prevKeyColor[i], prevBgColor[i], program[0].val[3], program[1].val[3], i);
        //strip.setPixelColor(keyBuffer[i].keyLight[i], prevKeyColor[1]);
      }
    }
  }
}