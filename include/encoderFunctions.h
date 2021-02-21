void initializeEncoders() 
{

    ESP32Encoder::useInternalWeakPullResistors=UP;

    // Define encoders.
    encoder1.attachFullQuad(39, 36);
    encoder2.attachHalfQuad(35, 34);
    encoder3.attachHalfQuad(14, 27);
    encoder4.attachHalfQuad(25, 33);

    // Set the encoders to their previous program states.
    if(programs[0].active == true) 
    {
        encoder1.setCount(programs[0].hue);
        encoder2.setCount(programs[0].saturation);
        encoder3.setCount(programs[0].luminance);
        encoder4.setCount(programs[0].duration);
    }
    if(programs[1].active == true) 
    {
        encoder1.setCount(programs[1].hue);
        encoder2.setCount(programs[1].saturation);
        encoder3.setCount(programs[1].luminance);
        encoder4.setCount(programs[1].duration);
    }

    // Set the comparators to the newly set values.
    count1 = oldCount1 = encoder1.getCount();
    count2 = oldCount2 = encoder2.getCount();
    count3 = oldCount3 = encoder3.getCount();
    count4 = oldCount4 = encoder4.getCount();
}

void countChangeActions() 
{
    // Mark new Data
    dataSaved = !dataSaved;

    // Find the change.
    if (count1 != oldCount1) 
    {
        oldCount1 = count1;
        if (programs[0].active == true) 
        {
            programs[0].hue = count1;
            setMessage(count1, bh);
        }
        if (programs[1].active == true) 
        {
            programs[1].hue = count1;
            setMessage(count1, kh);
        }
    }
    if (count2 != oldCount2) 
    {
        oldCount2 = count2;
        if (programs[0].active == true) 
        {
            programs[0].saturation = count2;
            setMessage(count2, bs);
        }
        if (programs[1].active == true) 
        {
            programs[1].saturation = count2;
            setMessage(count2, ks);
        }
    }
    if (count3 != oldCount3) 
    {
        oldCount3 = count3;
        if (programs[0].active == true) 
        {
            programs[0].luminance = count3;
            setMessage(count3, bl);
        }
        if (programs[1].active == true) 
        {
            programs[1].luminance = count3;
            setMessage(count3, kl);
        }
    }
    if (count4 != oldCount4) 
    {
        oldCount4 = count4;
        if (programs[0].active == true) 
        {
            programs[0].duration = count4;
            setMessage(count4, fdur);
        }
        if (programs[1].active == true) 
        {
            programs[1].duration = count4;
            setMessage(count4, fdel);
        }
    }
}

void buttonChangeActions(bool button1, bool button2, bool button3, bool button4) 
{

    // A button change means a program change
    // Put Buttons in an array
    bool btn[4] = {button1, button2, button3, button4};

    for (int i = 0; i < 4; i++) 
    {
        programs[i].active = false;
    }
    // If the button is not marked down, but it's down.
    for (int i = 0; i < 4; i++) {
        if((btnDown[i] == false) && (btn[i] == false)) {
            btnDown[i] = !btnDown[i];
            programs[i].active = true;
        }
         // If the button is marked down, but it's up.
        if ((btnDown[i] == true) && (btn[i] == true)) 
        {
            btnDown[i] = !btnDown[i]; 
        }
    }


    // Depending on the active program, reset the encoder counts
    if (programs[0].active == true) 
    {
        encoder1.setCount(programs[0].hue);
        encoder2.setCount(programs[0].saturation);
        encoder3.setCount(programs[0].luminance);
        encoder4.setCount(programs[0].duration);
        setSplash(bg);
    }
    if (programs[1].active == true) 
    {
        encoder1.setCount(programs[1].hue);
        encoder2.setCount(programs[1].saturation);
        encoder3.setCount(programs[1].luminance);
        encoder4.setCount(programs[1].duration);
        setSplash(ky);
    }
    if (programs[3].active == true) 
    {
        setSplash(save);
        setMemory();
        dataSaved = !dataSaved;
        programs[3].active = false;
        programs[0].active = true;
    }
}

void displayRest() 
{

    // Execute actions based on the time since last input change.
    if (esp_timer_get_time() - lastInputChange > LOGO_DELAY)
    {
        showLogo();
    }
    if (esp_timer_get_time() - lastInputChange > SLEEP_DELAY) 
    {

        // If it's been a while since the last input change
        // Turn off display to avoid burn-in.
        clearDisplay();
    }
}

void encoderProgram() 
{
    count1 = encoder1.getCount();
    count2 = encoder2.getCount();
    count3 = encoder3.getCount();
    count4 = encoder4.getCount();

    bool button1 = digitalRead(e_button1);
    bool button2 = digitalRead(e_button2);
    bool button3 = digitalRead(e_button3);
    bool button4 = digitalRead(e_button4);

    // Button changes
    if ((button1 != 1) || (button2 != 1) || (button3 != 1) || (button4 != 1)) 
    {
        // Manage Buttons
        buttonChangeActions(button1, button2, button3, button4);

        // Rest
        displayRest();

         // Reset Change Timer
        lastInputChange = esp_timer_get_time();

        // Mark new data
        dataSaved = !dataSaved;
    }
    // Watch for encoder changes
    if ((count1 != oldCount1) || (count2 != oldCount2) || (count3 != oldCount3) || (count4 != oldCount4)) 
    {
        // Manage Encoders
        countChangeActions();

        // Update Strips
        updateColors(count1, count2, count3);

        // Rest
        displayRest();

        // Mark new data
        dataSaved = !dataSaved;

        // Reset Change Timer
        lastInputChange = esp_timer_get_time();
    }
}
