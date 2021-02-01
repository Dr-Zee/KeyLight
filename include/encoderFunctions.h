void initializeEncoders() {

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    encoder1.attachFullQuad(39, 36);
    encoder2.attachHalfQuad(35, 34);
    encoder3.attachHalfQuad(14, 27);
    encoder4.attachHalfQuad(25, 33);

    if(program1.active == true) {
        encoder1.setCount(program1.hue);
        encoder2.setCount(program1.saturation);
        encoder3.setCount(program1.luminance);
        encoder4.setCount(program1.duration);
    }
    if(program2.active == true) {
        encoder1.setCount(program2.hue);
        encoder2.setCount(program2.saturation);
        encoder3.setCount(program2.luminance);
        encoder4.setCount(program2.duration);
    }
    if(program3.active == true) {
        encoder1.setCount(program3.hue);
        encoder2.setCount(program3.saturation);
        encoder3.setCount(program3.luminance);
        encoder4.setCount(program3.duration);
    }

    count1 = oldCount1 = encoder1.getCount();
    count2 = oldCount2 = encoder2.getCount();
    count3 = oldCount3 = encoder3.getCount();
    count4 = oldCount4 = encoder4.getCount();
}

void countChangeActions() {

    // Mark new Data
    dataSaved = !dataSaved;

    // 4 arrays since we have multiple datatypes
    uint8_t old8[4] = {oldCount2, oldCount3};
    uint8_t cur8[4] = {oldCount2, oldCount3};

    uint16_t old16[4] = {oldCount1, oldCount4};
    uint16_t cur16[4] = {oldCount1, oldCount4};

    // Loop through the 16 bit types
    for (int i = 0; i < 2; i++) {
        if(cur16[i] != old16[i]) {
            old16[i] = cur16[i];
            if (program1.active == true) {
                setMessage(cur8[i], bh);
            }
            if (program2.active == true) {
                setMessage(cur8[i], kh);
            }
        }
    }

    // Loop through the 8 bit types
    for (int i = 0; i < 2; i++) {
        if(cur8[i] != old8[i]) {
            old8[i] = cur8[i];
            if (program1.active == true) {
                setMessage(cur8[i], bh);
            }
            if (program1.active == true) {
                setMessage(cur8[i], kh);
            }
        }
    }


    // Find the change
    if (count1 != oldCount1) {
        oldCount1 = count1;
        if (program1.active == true) {
            setMessage(count1, bh);
        }
        if (program2.active == true) {
            setMessage(count1, kh);
        }
        if (program3.active == true) {

        }
    }
    if (count2 != oldCount2) {
        oldCount2 = count2;
        if (program1.active == true) {
            setMessage(count2, bs);
        }
        if (program2.active == true) {
            setMessage(count2, ks);
        }
        if (program3.active == true) {

        }
    }
    if (count3 != oldCount3) {
        oldCount3 = count3;
        if (program1.active == true) {
            setMessage(count3, bl);
        }
        if (program2.active == true) {
            setMessage(count3, kl);
        }
        if (program3.active == true) {
        }
    }
    if (count4 != oldCount4) {
        oldCount4 = count4;
        if (program1.active == true) {
            setMessage(count4, fdur);
        }
        if (program2.active == true) {
            setMessage(count4, fdel);
        }
        if (program3.active == true) {

        }
    }
}

void buttonChangeActions(bool button1, bool button2, bool button3, bool button4) {
    bool btn[4] = {button1, button2, button3, button4};
    for (int i = 0; i < 2; i++) {
        if ((btnDown[i]) && (btn[i] == LOW)) {
            btnDown[i] = !btnDown[i];

            if(btnDown[i] == btnDown[0]) {
                program1.active = !program1.active;
                program2.active = !program2.active;
            }
            if(btnDown[i] == btnDown[1]) {
                program1.active = !program1.active;
                program1.active = !program1.active;
            }
        }
        if ((btnDown[i] == false) && (btn[i] == HIGH)) {
            btnDown[i] = !btnDown[i];
        }
    }
}

void displayRest() {

    // Execute actions based on the time since last input change.
    if ((millis() - lastInputChange > 5000) && (dataSaved == false)) {

        // If it's been a while since the last input change,
        // Write values to EEPROM and sleep
        showLogo();
        setMemory();
        dataSaved = !dataSaved;
    }
    if ((millis() - lastInputChange > 10000) && (dataSaved == true)) {

        // If it's been a while since the last input change
        // Turn off display to avoid burn-in.
        clearDisplay();
    }
}

void encoderProgram() {

    count1 = encoder1.getCount();
    count2 = encoder2.getCount();
    count3 = encoder3.getCount();
    count4 = encoder4.getCount();

    bool button1 = digitalRead(e_button1);
    bool button2 = digitalRead(e_button2);
    bool button3 = digitalRead(e_button3);
    bool button4 = digitalRead(e_button4);

    //Watch for changes
    if ((count1 != oldCount1) || (count2 != oldCount2) || (count3 != oldCount3) || (count4 != oldCount4) || (button1 != 1) || (button2 != 1) || (button3 != 1) || (button4 != 1)) {
        
        // Manage Encoders
        countChangeActions();

        // Manage Buttons
        buttonChangeActions(button1, button2, button3, button4);

        // Reset Change Timer
        lastInputChange = millis();

        // Rest
        displayRest();
    }
}
