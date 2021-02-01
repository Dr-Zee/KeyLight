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


void encoderProgram() {

    count1 = encoder1.getCount();
    count2 = encoder2.getCount();
    count3 = encoder3.getCount();
    count4 = encoder4.getCount();

    bool button1 = digitalRead(e_button1);
    bool button2 = digitalRead(e_button2);
    bool button3 = digitalRead(e_button3);
    bool button4 = digitalRead(e_button4);

    // If there is any input change
    if ((count1 != oldCount1) || (count2 != oldCount2) || (count3 != oldCount3) || (count4 != oldCount4) || (button1 != 1) || (button2 != 1) || (button3 != 1) || (button4 != 1)) {
        dataSaved = !dataSaved;

        // Find the change
        if (count1 != oldCount1) {
            oldCount1 = count1;
            if (btn1_prg1 == true) {
                setMessage(count1, bh);
            }
            if (btn1_prg2 == true) {
                 setMessage(count1, kh);
            }
        }
        if (count2 != oldCount2) {
            oldCount2 = count2;
            if (btn1_prg1 == true) {
                setMessage(count2, bs);
            }
            if (btn1_prg2 == true) {
                setMessage(count2, ks);
            }
        }
        if (count3 != oldCount3) {
            oldCount3 = count3;
            if (btn1_prg1 == true) {
                setMessage(count3, bl);
            }
            if (btn1_prg2 == true) {
                setMessage(count3, kl);
            }
        }
        if (count4 != oldCount4) {
            oldCount4 = count4;
            if (btn1_prg1 == true) {
                setMessage(count4, fdur);
            }
            if (btn1_prg2 == true) {
               setMessage(count4, fdel);
            }
            if (btn4_prg1 == true) {
                setMessage(count4, fdur);
            }
            if (btn4_prg2 == true) {
                setMessage(count4, fdel);
            }
            setMessage(count2, fdur);
        }
        
        if ((btn1_down == false) && (button1 == LOW)) {
            btn1_down = !btn1_down;

            // toggle the program.
            btn1_prg2 = !btn1_prg2;
            btn1_prg1 = !btn1_prg1;
        }
        if ((btn1_down == true) && (button1 == HIGH)) {
            btn1_down = !btn1_down;
        }
        if ((btn2_down == false) && (button2 == LOW)) {
            btn2_down = !btn2_down;

            // toggle the program.
            btn2_prg2 = !btn2_prg2;
            btn2_prg1 = !btn2_prg1;
        } 
        if ((btn2_down == true) && (button2 == HIGH)) {
            btn2_down = !btn2_down;
        }
        if ((btn3_down == false) && (button3 == LOW)) {
            btn3_down = !btn3_down;

            // toggle the program.
            btn3_prg2 = !btn3_prg2;
            btn3_prg1 = !btn3_prg1;
        }
        if ((btn3_down == true) && (button3 == HIGH)) {
            btn3_down = !btn3_down;
        }
        if ((btn4_down == false) && (button4 == LOW)) {
            btn4_down = !btn4_down;

            // toggle the program.
            btn4_prg2 = !btn4_prg2;
            btn4_prg1 = !btn4_prg1;
        }
        if ((btn4_down == true) && (button4 == HIGH)) {
            btn4_down = !btn4_down;
        }

        //Set button splash screens
        //buttonDisplayController();

        // Start the timer
        lastInputChange = millis();
    }
    if ((millis() - lastInputChange > 5000) && (dataSaved == false)) {
        // If it's been a while since the last input change,
        // Write values to EEPROM and sleep
        showLogo();
        setMemory();
        dataSaved = !dataSaved;
    }
    if ((millis() - lastInputChange > 10000) && (dataSaved == true)) {
        //clearDisplay();
        // If it's been a while since the last input change,
        // Write values to EEPROM and sleep
        clearDisplay();
    }
}
