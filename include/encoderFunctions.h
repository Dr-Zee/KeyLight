void initializeEncoders() 
{

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    count[0].encoder.attachFullQuad(39, 36);
    count[1].encoder.attachFullQuad(35, 34);
    count[2].encoder.attachFullQuad(14, 27);
    count[3].encoder.attachFullQuad(25, 33);

    // Get the active program and set the encoders using that data
    for (int i = 0; i < 4; i++) {
        count[i].count = count[i].encoder.getCount();
        count[i].oldCount = count[i].count;
    }
}
void byteClamp(uint16_t count, int i) 
{
    if ((i == 1) || (i == 2)) {
         //  Then, clamp the value to 8 bits
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

void countChangeActions(int i) 
{

    if (i == 0) {

        if (count[i].count > count[i].oldCount) {
            program[sys.active].val[i] = program[sys.active].val[i] + 100;
        }
        if (count[i].count < count[i].oldCount) {
            program[sys.active].val[i] = program[sys.active].val[i] - 100;
        }
        byteClamp(program[sys.active].val[i], i);
    }
    if ((i == 1) || (i == 2)) {

        if (count[i].count > count[i].oldCount) {
            program[sys.active].val[i] = program[sys.active].val[i] + 1;
        }
        else if (count[i].count < count[i].oldCount) {
            program[sys.active].val[i] = program[sys.active].val[i] - 1 ;
        }
        byteClamp(program[sys.active].val[i], i);
    }
    if (i == 3) {

        if (count[i].count > count[i].oldCount) {
            program[sys.active].val[i] = program[sys.active].val[i] + 50;
        }
        if (count[i].count < count[i].oldCount) {
            program[sys.active].val[i] = program[sys.active].val[i] - 50;
        }
        byteClamp(program[sys.active].val[i], i);
    }

    // Update the old count
    count[i].oldCount = count[i].count;
    setMessage(program[sys.active].val[i], i);
}


void programSwitcher(bool isLow, int index) 
{
    //  A button change means a program change
    //  If the button is not marked up, but it's down.
    if((sys.btnDown[index] == false) && (isLow == false)) {

        //  Toggle the button down state
        sys.btnDown[index] = !sys.btnDown[index];

        if (index == 0) {
            if (sys.active != 0) { sys.active = 0;}
            else { sys.active = 1;}
        }
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

void encoderProgram() 
{
    for (int i = 0; i < 4; i++) {
        count[i].count = count[i].encoder.getCount();
    }

    bool button[4] = {digitalRead(e_button1), digitalRead(e_button2), digitalRead(e_button3), digitalRead(e_button4)};

    for (int i = 0; i < 4; i++) {
        // Monitor the buttons
        if (button[i] != 1) {

            //  if any of the buttons go low, switch the program
            programSwitcher(button[i], i);

            //  Do a program thing
            programAction();
        }
        if ((sys.btnDown[i] == true) && (button[i] == 1)) {
            sys.btnDown[i] = !sys.btnDown[i];
        }
        // Monitor the Encoders
        if (count[i].count != count[i].oldCount) {

            // If the encoder values change
            countChangeActions(i);

            // Update Strips
            updateColors(program[sys.active].val[0], program[sys.active].val[1], program[sys.active].val[2]);
        }
        // Monitoring any changes
        if ((count[i].count != count[i].oldCount) || (button[i] != 1)) {

             // Reset Change Timer
            sys.lastInputChange = esp_timer_get_time();
            sys.logo = false;
        }
    }
}


