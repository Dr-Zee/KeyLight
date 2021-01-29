//get rotary encoder speed and control steps based on rotation speed
//step = 1 << (int(hue.speed / encoderSpeedDivisor));

// Encoders

// Encoders from MD_REncoder library
// Capable of getting a speed reading.
// MD_REncoder hue = MD_REncoder(21, 22);
// MD_REncoder brightness = MD_REncoder(25, 26);
// MD_REncoder saturation = MD_REncoder(32, 33);
// MD_REncoder timing = MD_REncoder(12, 13);

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

    bool hue = digitalRead(p_hueButton);
    bool brightness = digitalRead(p_brightnessButton);
    bool saturation = digitalRead(p_saturationButton);
    bool duration = digitalRead(p_durationButton);

    if (count1 != oldCount1) {
        programstrip.setPixelColor(1, programstrip.gamma32(programstrip.ColorHSV(count1)));
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

    if (hue == 0) {
        Serial.print("hue button: ");
        Serial.print(hue);
        Serial.println(" ");
    }
    if (brightness == 0) {
        Serial.print("brightness button: ");
        Serial.print(brightness);
        Serial.println(" ");
    }
    if (saturation == 0) {
        Serial.print("saturation button: ");
        Serial.print(saturation);
        Serial.println(" ");
    }
    if (duration == 0) {
        Serial.print("duration button: ");
        Serial.print(duration);
        Serial.println(" ");
    }

}


void readInputs()
{
  // Booleans
  hueButton =         digitalRead(p_hueButton);
  brightnessButton =  digitalRead(p_brightnessButton);
  saturationButton =  digitalRead(p_saturationButton);
  durationButton =  digitalRead(p_durationButton);

  // First attempt at a non-blocking toggle button.
  // Debounce by accepting the first HIGH signal and not reading again for 500 milliseconds. 
  // Then, reset the button timer and read the button.
  if(readHueButton == true) {
    if(digitalRead(p_hueButton) == HIGH)
    {
      hueSelect = !hueSelect;
      readHueButton = false;
      hueButtonTimer = millis();
    }
  }
  if(millis() - hueButtonTimer >= toggleButtonTimeout) 
  {
    readHueButton = true;
    hueButtonTimer = 0;
  }
}