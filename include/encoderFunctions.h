//get rotary encoder speed and control steps based on rotation speed
//step = 1 << (int(hue.speed / encoderSpeedDivisor));

// Encoders

void initializeEncoders() {

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    encoder1.attachHalfQuad(39, 36);
    encoder2.attachHalfQuad(35, 34);
    encoder3.attachHalfQuad(14, 27);
    encoder4.attachHalfQuad(25, 33);

    encoder1.setCount(0);
    encoder2.setCount(0);
    encoder3.setCount(0);
    encoder4.setCount(0);
  
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

        // Find the change
        if (count1 != oldCount1) {
            programstrip.setPixelColor(1, programstrip.gamma32(programstrip.ColorHSV(52536)));
            programstrip.show();
            oldCount1 = count1;
            Serial.print("encoder 1: ");
            Serial.print(count1);
            Serial.println(" ");
        }
        if (count2 != oldCount2) {
            programstrip.setPixelColor(0, programstrip.gamma32(programstrip.ColorHSV(count2)));
            programstrip.show();
            oldCount2 = count2;
            Serial.print("encoder 2: ");
            Serial.print(count2);
            Serial.println(" ");

        }
        if (count3 != oldCount3) {
            programstrip.setPixelColor(2, programstrip.gamma32(programstrip.ColorHSV(count3)));
            programstrip.show();
            oldCount3 = count3;
            Serial.print("encoder 3: ");
            Serial.print(count3);
            Serial.println(" ");
        }
        if (count4 != oldCount4) {
            programstrip.setPixelColor(3, programstrip.gamma32(programstrip.ColorHSV(count4)));
            programstrip.show();
            oldCount4 = count4;
            Serial.print("encoder 4: ");
            Serial.print(count4);
            Serial.println(" ");
        }

        if (button1 == 0) {
            Serial.print("hue button: ");
            Serial.print(button1);
            Serial.println(" ");
        }
        if (button2 == 0) {
            Serial.print("brightness button: ");
            Serial.print(button2);
            Serial.println(" ");
        }
        if (button3 == 0) {
            Serial.print("saturation button: ");
            Serial.print(button3);
            Serial.println(" ");
        }
        if (button4 == 0) {
            Serial.print("duration button: ");
            Serial.print(button4);
            Serial.println(" ");
        }
        lastInputChange = 0;
    }
    if (millis() - lastInputChange > 40000) {
        // If it's been a while since the last input change,
        // Write values to EEPROM and sleep
    }
}