void initializeEncoders() 
{

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    count[0].encoder.attachFullQuad(39, 36);
    count[1].encoder.attachHalfQuad(35, 34);
    count[2].encoder.attachHalfQuad(14, 27);
    count[3].encoder.attachHalfQuad(25, 33);

    // Get the active program and set the encoders using that data
    for (int i = 0; i < 4; i++) {
        count[i].encoder.setCount(program[systemData.activeProgram].val[i]);
        count[i].oldCount = count[i].count = program[systemData.activeProgram].val[i];
    }
}

void countChangeActions(int counter) 
{
    // Update the old count
    count[counter].oldCount = count[counter].count;

    // Set the new value in the program
    program[systemData.activeProgram].val[counter] = count[counter].count;

    setMessage(count[counter].count, counter);
}

void programSwitcher(bool isLow, int index) 
{
    //  A button change means a program change
    //  If the button is not marked up, but it's down.
    if((systemData.btnDown[index] == false) && (isLow == false)) {
        
        //  Toggle the button down state
        systemData.btnDown[index] = !systemData.btnDown[index];

        //  If the program is 0 and button 0 is pressed, switch to program 1
        //  If the program is not 0 and button 0 is pressed, switch to program 0
        if ((systemData.activeProgram == 0) && (index == 0)) { systemData.activeProgram = 1; }
        else if ((systemData.activeProgram != 0) && (index == 0)) { systemData.activeProgram = 0; }

        //  If button 1 is pressed and program 2 is not active, switch to program 2
        //  If button 1 is pressed and program 2 is active, switch to program 0
        if ((systemData.activeProgram != 2) && (index == 1)) { systemData.activeProgram = 2; }
        else if ((systemData.activeProgram == 2) && (index == 1)) { systemData.activeProgram = 0; }

        //  If button 2 is pressed and program 3 is not active, switch to program 3
        //  If button 2 is pressed and program 3 is active, switch to program 0
        if ((systemData.activeProgram != 3) && (index == 2)) { systemData.activeProgram = 3; }
        else if ((systemData.activeProgram == 3) && (index == 2)) { systemData.activeProgram = 0; }

        //  If button 3 is pressed and program 4 is not active, switch to program 4
        //  If button 3 is pressed and program 4 is active, switch to program 0
        if ((systemData.activeProgram != 4) && (index == 3)) { systemData.activeProgram = 4; }
        else if ((systemData.activeProgram == 4) && (index == 3)) { systemData.activeProgram = 0; }
    }
        // If the button is marked down, but it's up.
    if ((systemData.btnDown[index] == true) && (isLow == true)) 
    {
        //  Toggle the button down state
        systemData.btnDown[index] = !systemData.btnDown[index]; 
    }
}

void displayRest() 
{

    // Execute actions based on the time since last input change.
    if ((systemData.logoDisplayed == false) && ((timeKeeper(systemData.lastInputChange) > systemData.logoDelay) && (timeKeeper(systemData.lastInputChange) < systemData.sleepDelay)))
    {
        showLogo();
        systemData.logoDisplayed = true;
    }
    if ((timeKeeper(systemData.lastInputChange) > systemData.sleepDelay) && (systemData.logoDisplayed == true)) 
    {
        clearDisplay();
        systemData.logoDisplayed = false;
    }
}

void encoderProgram() 
{

    for (int i = 0; i < 4; i++) {
        count[i].count = encoderConvert(count[i].encoder.getCount(), i);
    }

    bool button[4] = {digitalRead(e_button1), digitalRead(e_button2), digitalRead(e_button3), digitalRead(e_button4)};

    for (int i = 0; i < 4; i++) {
        // Monitor the buttons
        if (button[i] != 1) {

            //  if any of the buttons go low, switch the program
            programSwitcher(button[i], i);

            //  Do a program thing
            programAction();

            //  Set the splash screen
            setSplash();
        }
        // Monitor the Encoders
        if (count[i].count != count[i].oldCount) {

            // If the encoder values change
            countChangeActions(i);

            // Update Strips
            updateColors(count[0].count, count[1].count, count[2].count);
        }
        // Monitoring any changes
        if ((count[i].count != count[i].oldCount) || (button[i] != 1)) {

            // Reset Change Timer
            systemData.lastInputChange = esp_timer_get_time();
            systemData.logoDisplayed = false;
        }
        // Rest
        displayRest();
    }
}

void programAction() {
    //  If the program is Save, run the save command then switch back to the default program.
    if (systemData.activeProgram == 2) {
        setMemory();
        //  Show the Saved splash
        setSplash();
        //  Back to default
        systemData.activeProgram == 0;
    }
}