void initializeEncoders() 
{

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    sys.encoder[0].attachFullQuad(39, 36);
    sys.encoder[1].attachHalfQuad(35, 34);
    sys.encoder[2].attachHalfQuad(14, 27);
    sys.encoder[3].attachHalfQuad(25, 33);

    // Get the active program and set the encoders using that data
    for (int i = 0; i < 4; i++) {
        sys.encoder[i].setCount(program[sys.active].val[i]);
        program[sys.active].oldVal[i] = program[sys.active].val[i];
    }
}

void countChangeActions(int counter) 
{
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

    // Execute actions based on the time since last input change.
    if ((sys.logo == false) && (timeKeeper(sys.lastInputChange) > sys.logoDelay) && (timeKeeper(sys.lastInputChange) < sys.sleepDelay))
    {
 
        sys.logo = true;
    }
    if ((timeKeeper(sys.lastInputChange) > sys.sleepDelay) && (sys.logo == true)) 
    {
        //clearDisplay();
        sys.logo = false;
    }
}

void encoderProgram() 
{

    int active = sys.active;
    if (programChanged == true) {
        for (int i = 0; i < 4; i++) {

            // Exempt program dumps from being converted.
            if ((active == 0) || (active == 1)) {
                sys.encoder[i].setCount(program[active].val[i]);
                program[active].oldVal[i] = program[active].val[i];
            }
        }
        programChanged = !programChanged;
    } else {
        for (int i = 0; i < 4; i++) {
            program[sys.active].val[i] = encoderConvert(sys.encoder[i].getCount(), i);
        }
    }

    bool button[4] = {digitalRead(e_button1), digitalRead(e_button2), digitalRead(e_button3), digitalRead(e_button4)};

    for (int i = 0; i < 4; i++) {
        // Monitor the buttons
        if (button[i] != 1) {

            //  if any of the buttons go low, switch the program
            programSwitcher(button[i], i);

            //  Do a program thing
            programAction();
             // Reset Change Timer
            sys.lastInputChange = esp_timer_get_time();
            sys.logo = false;
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

             // Reset Change Timer
            sys.lastInputChange = esp_timer_get_time();
            sys.logo = false;
        }
        // Monitoring any changes
        if ((program[sys.active].val[i] != program[sys.active].oldVal[i]) || (button[i] != 1)) {

        
        }
    }
}
