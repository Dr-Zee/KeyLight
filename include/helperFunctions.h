int64_t timeKeeper(int64_t timer) {
    return esp_timer_get_time() - timer;
}

uint16_t encoderConvert(uint16_t encoderCount, int i) {
    if (i == 0) {
        encoderCount = (encoderCount / 2) * 200;
    }
    if ((i == 1) || (i == 2)) {

        // Saturation/Luminance multiplier
        encoderCount = (encoderCount / 2) * 5;

        //  Byte clamp.
        //  Clamp the 16 bit value to 8 bits to remove inappropriate data input.
        //  16 bit value is used for consistency and code simplicity across all encoders.
        
        //  check above 255 in case the encoder rolls past due to a multiplier
        if ((encoderCount > 255) && (encoderCount < 300)) {
            count[i].encoder.setCount(0);
            count[i].count = 0;
            encoderCount = 0;
        }

        // uint16_t rolls over from 0 to 65535
        // look for any number higher than the 255-300 range to catch if we've passed below 0
        if ((encoderCount > 300)) {
            count[i].encoder.setCount(255);
            count[i].count = 255;
            encoderCount = 255;
        }
    } 
    if (i == 3) {
        // Duration multiplier
        encoderCount = (encoderCount / 2) * 200;
    }

    return encoderCount;
}