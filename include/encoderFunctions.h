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

void countChangeListener() {

    // Mark new Data
    dataSaved = !dataSaved;

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

void buttonChangeListener(bool button1, bool button2, bool button3, bool button4) {

    if ((btn1_down == false) && (button1 == LOW)) {
        btn1_down = !btn1_down;

        // toggle the program.
        prg[0] = !prg[0];
        prg[1] = !prg[1];
    }
    if ((btn1_down == true) && (button1 == HIGH)) {
        btn1_down = !btn1_down;
    }
    if ((btn2_down == false) && (button2 == LOW)) {
        btn2_down = !btn2_down;

        // toggle the program.
        prg[3] = !prg[3];
        prg[2] = !prg[2];
    } 
    if ((btn2_down == true) && (button2 == HIGH)) {
        btn2_down = !btn2_down;
    }
    if ((btn3_down == false) && (button3 == LOW)) {
        btn3_down = !btn3_down;

        // toggle the program.
        prg[5] = !prg[5];
        prg[4] = !prg[4];
    }
    if ((btn3_down == true) && (button3 == HIGH)) {
        btn3_down = !btn3_down;
    }
    if ((btn4_down == false) && (button4 == LOW)) {
        btn4_down = !btn4_down;

        // toggle the program.
        prg[7] = !prg[7];
        prg[6] = !prg[6];
    }
    if ((btn4_down == true) && (button4 == HIGH)) {
        btn4_down = !btn4_down;
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

    if ((count1 != oldCount1) || (count2 != oldCount2) || (count3 != oldCount3) || (count4 != oldCount4) || (button1 != 1) || (button2 != 1) || (button3 != 1) || (button4 != 1)) {
        countChangeListener();
        buttonChangeListener(button1, button2, button3, button4);
        displayRest();
        lastInputChange = millis();
    }
}
