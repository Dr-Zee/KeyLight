void initializeEncoders() 
{

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    count[0].encoder.attachFullQuad(39, 36);
    count[1].encoder.attachHalfQuad(35, 34);
    count[2].encoder.attachHalfQuad(14, 27);
    count[3].encoder.attachHalfQuad(25, 33);

    // Get the active program and set the encoders using that data
    int program = getActiveProgram();
    for (int i = 0; i < 4; i++) {
        count[i].encoder.setCount(programs[program].val[i]);
        count[i].oldCount = count[i].count = programs[program].val[i];
    }
}


void countChangeActions(int counter) 
{
    int program = getActiveProgram();

    count[counter].oldCount = count[counter].count;
    programs[program].val[counter] = count[counter].count;
    setMessage(count[counter].count, counter);
}


void buttonChangeManager(bool button, int number) 
{
    // A button change means a program change
    // If the button is not marked down, but it's down.

    if((btnDown[number] == false) && (button == false)) {
        btnDown[number] = !btnDown[number];
        setActiveProgram(number);
    }
        // If the button is marked down, but it's up.
    if ((btnDown[number] == true) && (button == true)) 
    {
        btnDown[number] = !btnDown[number]; 
    }
}



void displayRest() 
{

    // Execute actions based on the time since last input change.
    if ((logoDisplayed == false) && (timeKeeper(lastInputChange) > LOGO_DELAY))
    {
        showLogo();
    }
    if (timeKeeper(lastInputChange) > SLEEP_DELAY) 
    {

        clearDisplay();
    }
}

void encoderProgram() 
{

    for (int i = 0; i < 4; i++) {
        count[i].count = encoderConvert(count[i].encoder.getCount(), i);
    }

    bool button[4] = {digitalRead(e_button1), digitalRead(e_button2), digitalRead(e_button3), digitalRead(e_button4)};

    for (int i = 0; i < 4; i++) {
        if (button[i] != 1) {

            // if any of the buttons go low
            buttonChangeManager(button[i], i);
        }

        if (count[i].count != count[i].oldCount) {

            // If the encoder values change
            countChangeActions(i);

            // Update Strips
            updateColors(count[0].count, count[1].count, count[2].count);
        }
        if ((count[i].count != count[i].oldCount) || (button[i] != 1)) {

            // If there is any change
            // Reset Change Timer
            lastInputChange = esp_timer_get_time();
        }
        // Rest
        displayRest();
    }
}
