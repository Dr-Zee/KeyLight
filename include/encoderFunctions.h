//get rotary encoder speed and control steps based on rotation speed
//step = 1 << (int(hue.speed / encoderSpeedDivisor));

// Encoders

void initializeEncoders() {

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    encoder1.attachFullQuad(39, 36);
    encoder2.attachHalfQuad(35, 34);
    encoder3.attachHalfQuad(14, 27);
    encoder4.attachHalfQuad(25, 33);

    encoder1.setCount(6336);
    encoder2.setCount(380);
    encoder3.setCount(170);
    encoder4.setCount(200);

    count1 = oldCount1 = encoder1.getCount();
    count2 = oldCount2 = encoder2.getCount();
    count3 = oldCount3 = encoder3.getCount();
    count4 = oldCount4 = encoder4.getCount();
}


void encoderProgram() {

    count1 = (encoder1.getCount() / 2) * 200;
    count2 = (encoder2.getCount() / 2) * 5;
    count3 = (encoder3.getCount() / 2) * 5;
    count4 = (encoder4.getCount() / 2) * .1;

    bool button1 = digitalRead(e_button1);
    bool button2 = digitalRead(e_button2);
    bool button3 = digitalRead(e_button3);
    bool button4 = digitalRead(e_button4);

    // If there is any input change
    if ((count1 != oldCount1) || (count2 != oldCount2) || (count3 != oldCount3) || (count4 != oldCount4) || (button1 != 1) || (button2 != 1) || (button3 != 1) || (button4 != 1)) {

        // Prepare the display.
        display.clearDisplay();
        display.setCursor(0,0);
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(1);

        // Find the change
        if (count1 != oldCount1) {
            oldCount1 = count1;
            
            display.println("Background Hue");
            display.println("");
            display.setTextSize(2);
            display.println(count1);
        }
        if (count2 != oldCount2) {
            oldCount2 = count2;

            display.println("Background Saturation");
            display.println("");
            display.setTextSize(2);
            display.println(count2);
        }
        if (count3 != oldCount3) {
            oldCount3 = count3;

            display.println("Background Brightness");
            display.println("");   
            display.setTextSize(2);
            display.println(count3);
        }
        if (count4 != oldCount4) {

            display.println("Fade Duration");
            display.println("");
            display.setTextSize(2);
            display.print(count4);
            display.setTextSize(.5);
            display.println(" seconds");

            if (count4 > 10) {
                encoder4.setCount(0);
            }
            if (count4 < 0) {
                encoder4.setCount(200);
            }
            oldCount4 = count4;
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

        display.display();
        lastInputChange = millis();

            uint32_t returned_color = programstrip.gamma32(programstrip.ColorHSV(count1, count2, count3));

                for (byte i = 0; i < programstrip.numPixels(); i++) {

            uint8_t r = Red(returned_color);
            uint8_t g = Green(returned_color);
            uint8_t b = Blue(returned_color);
            uint8_t w = 0;




            //color sharing
            //By a series of devlish challenges, determine the smallest color value.
            int smallest = 0;
            if(r < g && r < b) {smallest = r;} else if (g < r && g < b)  {smallest = g;} else if (b < r && b < g) {smallest = b;}

            //Take the group's lowest common denomenator and remove it.
            r = r - smallest;
            g = g - smallest;
            b = b - smallest;
            w = smallest;

            //Check for negatives.
            if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}





            programstrip.setPixelColor(i, programstrip.Color(r, g, b, w)); 

      
        programstrip.show();
        strip.show();
    }
    if (millis() - lastInputChange > 5000) {
        // If it's been a while since the last input change,
        // Write values to EEPROM and sleep
        showLogo();
    }
    if (millis() - lastInputChange > 10000) {
        clearDisplay();
        // If it's been a while since the last input change,
        // Write values to EEPROM and sleep
        //clearDisplay();
        //showLogo();
    }
}
