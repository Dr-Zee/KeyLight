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

void countChangeActions(int i) 
{   
    byte multiplier;

    if (i == 0) {
        multiplier = 100;
    }
    if ((i == 1) || (i == 2)) {
        multiplier = 1;
    }
    if (i == 3) {
        multiplier = 50;
    }

    if (count[i].count > count[i].oldCount) {
        program[sys.active].val[i] = program[sys.active].val[i] + multiplier;
    }
    if (count[i].count < count[i].oldCount) {
        program[sys.active].val[i] = program[sys.active].val[i] - multiplier;
    }
    byteClamp(program[sys.active].val[i], i);
    
    // Update the old count
    count[i].oldCount = count[i].count;
    setMessage(program[sys.active].val[i], i);
}

void encoderProgram() 
{
    //  Watch the encoders
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
        }
        // Monitoring any changes
        if ((count[i].count != count[i].oldCount) || (button[i] != 1)) {

             // Reset Change Timer
            sys.lastInputChange = esp_timer_get_time();
            sys.logo = false;
        }
    }
}


