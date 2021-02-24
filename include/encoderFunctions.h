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

void buttonChangeManager(bool isLow, int index) 
{
    // A button change means a program change
    // If the button is not marked down, but it's down.

    if((systemData.btnDown[index] == false) && (isLow == false)) {

        // Handle the default 0 program nonsense.
        if ((systemData.activeProgram == 0) && (index == 0)) {
            systemData.activeProgram = 1;
        }
        if ((systemData.activeProgram != 0) && (index == 0)) {
            systemData.activeProgram = 0;
        }
        if (index == 1) {
            systemData.activeProgram = 2;
        }
        if (index == 2) {
            systemData.activeProgram = 3;
        }

        systemData.btnDown[index] = !systemData.btnDown[index];
        setSplash();
    }
        // If the button is marked down, but it's up.
    if ((systemData.btnDown[index] == true) && (isLow == true)) 
    {
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

            // if any of the buttons go low
            buttonChangeManager(button[i], i);
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
