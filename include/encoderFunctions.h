void initializeEncoders() 
{

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    count[0].encoder.attachSingleEdge(39, 36);
    count[1].encoder.attachSingleEdge(35, 34);
    count[2].encoder.attachSingleEdge(14, 27);
    count[3].encoder.attachSingleEdge(25, 33);

    // Get the active program and set the encoders using that data
    for (int i = 0; i < 4; i++) {
        count[i].count = count[i].encoder.getCount();
        count[i].oldCount = count[i].count;
    }
}

//  If there is a count change
void countChangeActions(int i) 
{   
    //  Set a count multiplier based on which encoder.
    uint16_t multiplier = 1;

    if (i == 0) {
        multiplier = 100;
    }
    if ((i == 1) || (i == 2)) {
        multiplier = 5;
    }
    if (i == 3) {
        multiplier = 80;
        if ((sys.active == 3) || (sys.active == 4)) {
            multiplier = 5;
        }
    }
    
    //  Increment or decrement the program.val[], which are abstractions of the real encoder count.
    if (count[i].count > count[i].oldCount) {
        program[sys.active].val[i] = program[sys.active].val[i] + multiplier;
    }
    if (count[i].count < count[i].oldCount) {
        program[sys.active].val[i] = program[sys.active].val[i] - multiplier;
    }

    //  Clamp the values to specific ranges.
    byteClamp(program[sys.active].val[i], i);
    
    //  Update the old count
    count[i].oldCount = count[i].count;

    //  Update the OLED
    setMessage(program[sys.active].val[i], i);
}

void encoderProgram() 
{

    bool button[4] = {digitalRead(e_button1), digitalRead(e_button2), digitalRead(e_button3), digitalRead(e_button4)};

    for (int i = 0; i < 4; i++) {

        //  Watch the encoders
        count[i].count = count[i].encoder.getCount();

        //  Monitor the buttons
        if (button[i] != 1) {

            //  if any of the buttons go low, switch the program
            programSwitcher(button[i], i);

            //  Do a program thing
            programAction();
        }

        //  If the button is marked down, but it's up, toggle it
        if ((sys.btnDown[i] == true) && (button[i] == 1)) {
            sys.btnDown[i] = !sys.btnDown[i];
        }

        //  If the encoder values change
        if (count[i].count != count[i].oldCount) {

            countChangeActions(i);

            //  Update Color Values
            updateProgramLEDs();
            updateStrip();
        }

        //  Monitoring any changes
        if ((count[i].count != count[i].oldCount) || (button[i] != 1)) {

            // Reset Change Timer (sets OLED timeout)
            sys.lastInputChange = millis();
            sys.logo = false;
        }
    }
}


