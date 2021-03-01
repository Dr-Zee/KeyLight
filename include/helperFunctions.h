//  Returns the duration since a timer began.
unsigned long timeKeeper(unsigned long timer) {
    return millis() - timer;
}

//  Checks for and corrects range overflow. For code simplicity, all encoders are 16bit,
//  But we need different number ranges for different encoders, so we set and manage them
//  manually here.
void byteClamp(uint16_t count, int i) 
{
    if ((i == 1) || (i == 2)) {
         //  Clamp the value to 8 bits
        if ((count > 255) && (count < 2000)) {
            program[sys.active].val[i] = 0;
        }
        else if (count > 2000) {
            program[sys.active].val[i] = 255;
        }
    }
    if (i == 0) {
        //  Then, clamp the value to 16 bits
        if (count > 65535) {
            program[sys.active].val[i] = 0;
        }
        else if (count < 1) {
            program[sys.active].val[i] = 65535;
        }
    }
    if (i == 3) {
        // clamp the fade values to 10 seconds
        if (count > 10000) {
            program[sys.active].val[i] = 0;
        }
    }
}

//  Executes program specific actions.
void programAction() {
    //  BG Program
    if (sys.active == 0)  {
        setSplash();
    }
    //  Key Program
    if (sys.active == 1)  {
        setSplash();
    }
    //  Save Program
    if (sys.active == 2) {
        setMemory();
        //  Show the Saved splash
        setSplash();
        //  Back to default
        sys.active = 0;
        setSplash();
    }
}

//  Program toggle logic
void programSwitcher(bool isLow, int index) 
{
    //  A button change means a program change
    //  If the button is not marked down, but it's down.
    if((sys.btnDown[index] == false) && (isLow == false)) {

        //  Toggle the button down state
        sys.btnDown[index] = !sys.btnDown[index];
        
        //  If toggle button 1
        if (index == 0) {
            if (sys.active != 0) { sys.active = 0;}
            else { sys.active = 1;}
        }
        //  If toggle button 2
        if (index == 1) {
            if (sys.active != 2) { sys.active = 2;}
        }
    } 
}

//  Display Timeout function
void displayRest() 
{
    if ((sys.logo == false) && (timeKeeper(sys.lastInputChange) > sys.logoDelay) && (timeKeeper(sys.lastInputChange) < sys.sleepDelay))
    {
        showLogo();
        sys.logo = true;
    }
    if ((timeKeeper(sys.lastInputChange) > sys.sleepDelay) && (sys.logo == true)) 
    {
        clearDisplay();
        sys.logo = false;
    }
}

// Updates color values and LEDs when there is an encoder change.
// Kept in the input loop so it will only fire if there is a change.
void updateValues() 
{
  uint32_t  color;

  if (sys.active == 0) 
  {
    color = colorProcessor(program[0].val[0], program[0].val[1], program[0].val[2]);
    
    //  Set the new BG Color
    for (int i = 0; i < 88; i++) 
    {
      prevBgColor[i] = color;
    }
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();

    // Set Key Program LED indicators
    for (int i = 0; i < 2; i++) {
      programstrip.setPixelColor(i, color);
    }
    programstrip.show();
  }
  if (sys.active == 1) 
  {
    color = colorProcessor(program[1].val[0], program[1].val[1], program[1].val[2]);
    //  Set the new Key Color
    for (int i = 0; i < 88; i++) 
    {
      fadeStage[i] = prevKeyColor[i] = color;
    }

    // Set Key Program LED indicators
    for (int i = 2; i < 4; i++) {
      programstrip.setPixelColor(i, color);
    }
    programstrip.show();
  }
}

// keyOn and keyOff housekeeping tasks.
void keyOnHousekeeping(int key) 
{
  //if(colorSkips > 5) 
  //{
  //  colorSkips = 0;
  //}
  //colorSkips++;
  
  keyBuffer[key].runOnce = true;

  //  Set a fresh background color reference in case the key was in mid-fade
  fadeStage[key] = prevKeyColor[key];
}

void keyOffHousekeeping(int i) 
{
  fadeStage[i] = prevKeyColor[i];
  keyBuffer[i].recentlyReleased = false;
  keyBuffer[i].lastReleased = 0;

  // Reset the fade timers
  for (int j = 0; j < 4; j++) {
    pixelTimers[i].t[j] = 0;
    rgbwSteps[i].t[j] = 0;
  }
}