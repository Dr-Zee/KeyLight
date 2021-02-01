void initializeEncoders() {

    ESP32Encoder::useInternalWeakPullResistors=UP;

    uint16_t e1 = EEPROM.readUShort(8);
    uint8_t e2 = EEPROM.readUInt(10);
    uint8_t e3 = EEPROM.readUInt(11);
    uint16_t e4 = EEPROM.readUShort(13);

    // Define encoders.
    encoder1.attachFullQuad(39, 36);
    encoder1.setCount(e1);
    encoder2.attachHalfQuad(35, 34);
    encoder2.setCount(e2);
    encoder3.attachHalfQuad(14, 27);
    encoder3.setCount(e3);
    encoder4.attachHalfQuad(25, 33);
    encoder4.setCount(e4);

    count1 = oldCount1 = e1;
    count2 = oldCount2 = e2;
    count3 = oldCount3 = e3;
    count4 = oldCount4 = e4;
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
        }
    }

    // Loop through the 8 bit types
    for (int i = 0; i < 2; i++) {
        if(cur8[i] != old8[i]) {
            old8[i] = cur8[i];
        }
    }


    // Find the change
    if (count1 != oldCount1) {
        oldCount1 = count1;
        if (prg[0] == true) {
            setMessage(count1, bh);
        }
        if (prg[1] == true) {
            setMessage(count1, kh);
        }
    }
    if (count2 != oldCount2) {
        oldCount2 = count2;
        if (prg[2] == true) {
            setMessage(count2, bs);
        }
        if (prg[3] == true) {
            setMessage(count2, ks);
        }
    }
    if (count3 != oldCount3) {
        oldCount3 = count3;
        if (prg[0] == true) {
            setMessage(count3, bl);
        }
        if (prg[1] == true) {
            setMessage(count3, kl);
        }
    }
    if (count4 != oldCount4) {
        oldCount4 = count4;
        if (prg[0] == true) {
            setMessage(count4, fdur);
        }
        if (prg[1] == true) {
            setMessage(count4, fdel);
        }
        if (prg[6] == true) {
            setMessage(count4, fdur);
        }
        if (prg[7] == true) {
            setMessage(count4, fdel);
        }
    }
}

void buttonChangeActions(bool button1, bool button2, bool button3, bool button4) {
    bool btn[4] = {button1, button2, button3, button4};
    for (int i = 0; i < 4; i++) {
        if ((btnDown[i]) && (btn[i] == LOW)) {
            btnDown[i] = !btnDown[i];

            if(btnDown[i] == btnDown[0]) {
                prg[0] = !prg[0];
                prg[1] = !prg[1];
            }
            if(btnDown[i] == btnDown[1]) {
                prg[2] = !prg[2];
                prg[3] = !prg[3];
            }
            if(btnDown[i] == btnDown[2]) {
                prg[4] = !prg[4];
                prg[5] = !prg[5];
            }
            if(btnDown[i] == btnDown[3]) {
                prg[6] = !prg[6];
                prg[7] = !prg[7];
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
