int64_t timeKeeper(int64_t timer) {
    return esp_timer_get_time() - timer;
}

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
        else if (count < 1) {
            program[sys.active].val[i] = 10000;
        }
    }
}

void programAction() {
    //  If the program is Save, run the save command then switch back to the default program.
    if (sys.active == 0)  {
        setSplash();
    }
    if (sys.active == 1)  {
        setSplash();
    }
    if (sys.active == 2) {
        setMemory();
        //  Show the Saved splash
        setSplash();
        //  Back to default
        sys.active = 0;
        setSplash();
    }
}

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
        programChanged = !programChanged;
    } 
}

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
