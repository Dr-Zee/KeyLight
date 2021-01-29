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

void valueWheels() {
    // Smooth Saturation wheel
    if ((count2 > 255) && (count2 <= 510 )) {

        // Get the extra number
        uint8_t countWheel2 = count2 - 255;

        //remove that from the total
        uint8_t adjustedCount2 = 255 - countWheel2;

    } else if (count2 > 510) {
        count2 = 0;
    }

    // Smooth Value Wheel
    if ((count3 > 255) && (count3 <= 510 )) {

        // Get the extra number
        uint8_t countWheel3 = count3 - 255;

        //remove that from the total
        uint8_t adjustedCount3 = 255 - countWheel3;

    } else if (count3 > 510) {
        count3 = 0;
    }
}


void encoderProgram() {

    count1 = encoder1.getCount() * 100;
    count2 = encoder2.getCount();
    count3 = encoder3.getCount();
    count4 = encoder4.getCount() * 1000;

    bool button1 = digitalRead(e_button1);
    bool button2 = digitalRead(e_button2);
    bool button3 = digitalRead(e_button3);
    bool button4 = digitalRead(e_button4);

    // If there is any input change
    if ((count1 != oldCount1) || (count2 != oldCount2) || (count3 != oldCount3) || (count4 != oldCount4) || (button1 != 1) || (button2 != 1) || (button3 != 1) || (button4 != 1)) {

        // Find the change
        if (count1 != oldCount1) {
            oldCount1 = count1;

            display.clearDisplay();
            display.setCursor(0,0);
            display.setTextColor(SSD1306_WHITE);
            
            display.setTextSize(1);
            display.println("Background Hue");
        
            display.println("");
            
            display.setTextSize(2);
            display.println(count1);
            
            display.display();
        }
        if (count2 != oldCount2) {
            oldCount2 = count2;
            display.clearDisplay();
            display.setCursor(0,0);
            display.setTextColor(SSD1306_WHITE);
            
            display.setTextSize(1);
            display.println("Background Saturation");
        
            display.println("");
            
            display.setTextSize(2);
            display.println(count2);
            
            display.display();

        }
        if (count3 != oldCount3) {
            oldCount3 = count3;
            display.clearDisplay();
            display.setCursor(0,0);
            display.setTextColor(SSD1306_WHITE);
            
            display.setTextSize(1);
            display.println("Background Brightness");
        
            display.println("");
            
            display.setTextSize(2);
            display.println(count3);
            
            display.display();
        }
        if (count4 != oldCount4) {
            oldCount4 = count4;
            display.clearDisplay();
            display.setCursor(0,0);
            display.setTextColor(SSD1306_WHITE);
            
            display.setTextSize(1);
            display.println("Duration");
        
            display.println("");
            
            display.setTextSize(4);
            display.println(count1);
            
            display.display();
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
        programstrip.setPixelColor(1, programstrip.gamma32(programstrip.ColorHSV(count1, count2, count3)));

        //hue = hue value
        //value = proportionally scale until any RGB  value hits 255
        //saturation = scale up white independently of rgb until it hits 255, then scale down rgb proportionally

        lastInputChange = 0;
    }
    if (millis() - lastInputChange > 40000) {
        // If it's been a while since the last input change,
        // Write values to EEPROM and sleep
    }
}