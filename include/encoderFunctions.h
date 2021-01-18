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
    hue.attachHalfQuad(25, 26);
    brightness.attachHalfQuad(28, 29);
    saturation.attachHalfQuad(23, 24);
    duration.attachHalfQuad(30, 31);

    for(int i = 0; i >= 3; i++) {
      
    }

  }