void initializeEncoders() 
{

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    sys.encoder[0].attachFullQuad(39, 36);
    sys.encoder[1].attachFullQuad(35, 34);
    sys.encoder[2].attachFullQuad(14, 27);
    sys.encoder[3].attachFullQuad(25, 33);

    // Get the active program and set the encoders using that data
    for (int i = 0; i < 4; i++) {
        sys.encoder[i].setCount(program[sys.active].val[i]);
        program[sys.active].oldVal[i] = program[sys.active].val[i];
    }
}

void countChangeActions(int counter) 
{
     if (programChanged == true) {
        for (int i = 0; i < 4; i++) {

            // Exempt program dumps from being converted.
            if ((sys.active == 0) || (sys.active == 1)) {
                sys.encoder[i].setCount(program[sys.active].val[i]);
                program[sys.active].oldVal[i] = program[sys.active].val[i];
            }
        }
        programChanged = !programChanged;
    } else {
        for (int i = 0; i < 4; i++) {
            program[sys.active].val[i] = encoderConvert(sys.encoder[i].getCount(), i);
        }
    }

    // Update the old count
    program[sys.active].oldVal[counter] = program[sys.active].val[counter];

    setMessage(program[sys.active].val[counter], counter);
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
    uint16_t countVal;
        for (int i = 0; i < 4; i++) {
            program[sys.active].val[i] = sys.encoder[i].getCount();
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
        if (program[sys.active].val[i] != program[sys.active].oldVal[i]) {

            // If the encoder values change
            countChangeActions(i);

            // Update Strips
            updateColors(program[sys.active].val[0], program[sys.active].val[1], program[sys.active].val[2]);
        }
        // Monitoring any changes
        if ((program[sys.active].val[i] != program[sys.active].oldVal[i]) || (button[i] != 1)) {

             // Reset Change Timer
            sys.lastInputChange = esp_timer_get_time();
            sys.logo = false;
        }
    }
}

// Here's the idea, use the encoders for raw input, but only use their data to increment variables.
//This way the encoder data will never interfere with the program data, and vice vera.
//Requires a significant rethink.
void encoderConversion() {
    if (program[sys.active].val[i] < program[sys.active].oldVal[i]) {

    }
}