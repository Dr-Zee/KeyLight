int64_t timeKeeper(int64_t timer) {
    return esp_timer_get_time() - timer;
}



uint16_t encoderConvert(uint16_t encoderCount, int i) {
    if (i == 0) {

        //  Hue Multiplier
        encoderCount = (encoderCount / 2) * 60;
    }
    if ((i == 1) || (i == 2)) {
        //  Byte clamp.
        //  Clamp the 16 bit value to 8 bits to remove inappropriate data input.
        //  16 bit value is used for consistency and code simplicity across all encoders.
        
        //  check above 255 in case the encoder rolls past due to a multiplier
        if ((encoderCount > 255) && (encoderCount < 2000)) {
            
            encoderCount = 0;
            sys.encoder[i].setCount(0);
        }

        if ((encoderCount > 2000)) {
 
            encoderCount = 255;
            sys.encoder[i].setCount(255);
        }
    } 
    if (i == 3) {

        // Duration multiplier
        encoderCount = (encoderCount / 2) * 200;
    }

    return encoderCount;
}

void programAction() {
    //  If the program is Save, run the save command then switch back to the default program.
    if (sys.active == 0)  {
        setSplash();
    }
    if (sys.active == 1)  {
        setSplash();
    }
    if (sys.active == 2) {
        setMemory();
        //  Show the Saved splash
        setSplash();
        //  Back to default
        sys.active = 0;
        setSplash();
    }
}