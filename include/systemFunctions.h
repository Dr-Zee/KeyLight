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
    prevBgColor[i]   = colorProcessor(program[0].val[0], program[0].val[1], program[0].val[2]);
    fadeStage[i] = prevKeyColor[i]  = colorProcessor(program[1].val[0], program[1].val[1], program[1].val[2]);
    ks  = colorProcessor(program[3].val[0], program[3].val[1], program[3].val[2]);
    bgs = colorProcessor(program[4].val[0], program[4].val[1], program[4].val[2]);
  }
}

// Initialize Key strip.
void initializeKeyStrip() 
{
  strip.begin();
  for(int i = 0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, prevBgColor[1]);
  }
  strip.show();
}

// Initialize Program Strip
void initializeProgramStrip() 
{
  programstrip.begin();

  //  Set all indicators
  if (colorskips == true) {
    programstrip.setPixelColor(1, prevBgColor[1]);
    programstrip.setPixelColor(2, prevKeyColor[1]);
    programstrip.setPixelColor(3, bgs);
    programstrip.setPixelColor(0, ks);
  } else {
    // Set BG and Key colors
    for(int i = 0; i < 4; i++) {
      if (i < 2) {
        programstrip.setPixelColor(i, prevBgColor[1]);
      } else {
        programstrip.setPixelColor(i, prevKeyColor[1]);
      }
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
    keyBuffer[key].lastReleased = millis();
    for (int i = 0; i < 4; i++) {
      pixelTimers[key].t[i] = millis() + program[1].val[3];
    }
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

// On keydown, Push a color to the keys only once.
void keyStrikes(int key) 
{
  if((keyBuffer[key].isDown == true) && (keyBuffer[key].runOnce == false)) 
  {
    for(int i = 0; i < 2; i++) 
    {
      strip.setPixelColor(keyBuffer[key].keyLight[i], prevKeyColor[key]);
    }
    strip.show();
    keyOnHousekeeping(key);
  }
}

// Fade out loop for non-blocking transitions out.
void theBigFade() 
{
  for (int i = 0; i < 88; i++) 
  {
    if(keyBuffer[i].recentlyReleased == true) 
    {  
      // Time since keyUp
      if(timeKeeper(keyBuffer[i].lastReleased) >= program[1].val[3]) 
      {
        if (program[0].val[3] < 100) {
          for (int j = 0; j < 2; j++) {
            strip.setPixelColor(keyBuffer[i].keyLight[j], prevBgColor[i]);
          }
          keyOffHousekeeping(i);
          strip.show();
        } else {
          colorFade(i);
        }
      }
    }
  }
}