// Set default key data.
void setDefaultData() {
  for (int i = 1; i < 88; i++) {
    //the 88th key only has one LED... intentionally.
    if(i == 88) {
      keyBuffer[i].keyLight[0] = keyBuffer[i].keyLight[1] = 176;
    }
    keyBuffer[i].keyLight[0] = (i * 2) - 2;
    keyBuffer[i].keyLight[1] = keyBuffer[i].keyLight[0] + 1;
    keyBuffer[i].isDown = keyBuffer[i].recentlyReleased = keyBuffer[i].runOnce = false;
    prevBgColor[i].r = bgColor.r; prevBgColor[i].g = bgColor.g; prevBgColor[i].b = bgColor.b; prevBgColor[i].w = bgColor.w;
  }
}

void stripOn(uint32_t color) {
  for(int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(bgColor.r, bgColor.g, bgColor.b, bgColor.w));
  }
  strip.show();
}

// Initialize light strip.
void initializeStrip() {
  strip.begin();
  stripOn(strip.Color(bgColor.r, bgColor.g, bgColor.b, bgColor.w));
  strip.show();
}

// Set event properties
void setEventProperties(byte key, byte event) {
  if (event == 9) {
    keyBuffer[key].isDown = true;
    keyBuffer[key].recentlyReleased = keyBuffer[key].runOnce = false;
  }
  if (event == 8) {
    keyBuffer[key].runOnce = keyBuffer[key].recentlyReleased = true;
    keyBuffer[key].isDown = false;
    keyBuffer[key].lastReleased = millis();
  }
}

// Midi Listener.
void MIDI_poll() {
  uint8_t bufMidi[64];
  uint16_t  rcvd;
  if ((Midi.vid != vid) | (Midi.pid != pid)) {
    vid = Midi.vid;
    pid = Midi.pid;
  }
  if (Midi.RecvData( &rcvd,  bufMidi) == 0 ) {
    event = bufMidi[0];
    //channel = bufMidi[1];
    //velocity = bufMidi[3];
    if ((event == 8) | (event == 9)) {
      key = bufMidi[2] - 20;
      setEventProperties(key, event);
    }
  }
}

// Push a color to the keys only once.
void keyStrikes(byte key) {
  if((keyBuffer[key].isDown == true) & (keyBuffer[key].runOnce == false)) {
    for(int i = 0; i < 2; i++) {
      strip.setPixelColor(keyBuffer[key].keyLight[i], strip.Color(keyColor.r, keyColor.g, keyColor.b, keyColor.w));

      // Set this as the previous pixel color for use in the fade.
      prevKeyColor[i].r = keyColor.r; prevKeyColor[i].g = keyColor.g; prevKeyColor[i].b = keyColor.b; prevKeyColor[i].w = keyColor.w;
    }
    strip.show();

    // Do Housekeeping
    keyOnHousekeeping(key);
  }
}

// Fade out loop for non-blocking transitions out
void theBigFade() {
  for (int i = 1; i < 88; i++) {
    if(keyBuffer[i].recentlyReleased == true) {
      
      // Time since keyUp
      uint32_t elapsed = millis() - keyBuffer[i].lastReleased;

      if((elapsed >= fadeDelay) & (elapsed < fadeDelay + fadeDuration)) {

        // Run the fade
        colorFade(fadeDuration, fadeDelay, i);
      }
    }
  }
}

void colorDefinitions() {
  // (colorDefs[x].r, colorDefs[x].g, colorDefs[x].b, colorDefs[x].w)
  // 0 = Color Corrected Warm White
  // 1 = RGBW Cool White
  colorDefs[0].r = 255; colorDefs[0].g = 140; colorDefs[0].b = 100; colorDefs[0].w = 0;
  colorDefs[1].r = 0; colorDefs[1].g = 0; colorDefs[1].b = 70; colorDefs[1].w = 255;
}

void colorFucker(byte r, byte g, byte b, byte w) {
  //Run all the values through the white balancer and round them.
  r = round(whiteBalance[WHITE_BALANCE].r * r);
  g = round(whiteBalance[WHITE_BALANCE].g * g);
  b = round(whiteBalance[WHITE_BALANCE].b * b);
  w = round(whiteBalance[WHITE_BALANCE].w * w);

  //Make sure there are no negative numbers.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}

  //Gamma Correct the resulting values.
  r = pgm_read_byte(&gamma8[r]);
  g = pgm_read_byte(&gamma8[g]);
  b = pgm_read_byte(&gamma8[b]);

  //color sharing

  //By a series of devlish challenges, determine the smallest color value.
  int smallest;
  if(r < g && r < b && r < w) {smallest = r;} else if (g < r && g < b && g < w)  {smallest = g;} else if (b < r && b < g && b < w) {smallest = b;} else {smallest = w;}

  //Take the group's lowest common denomenator and remove it.
  r = r - smallest;
  g = g - smallest;
  b = b - smallest;
  w = w - smallest;

  //Or this I guess https://stackoverflow.com/questions/21117842/converting-an-rgbw-color-to-a-standard-rgb-hsb-representation
  //M = max(Ri,Gi,Bi)
  //m = min(Ri,Gi,Bi)

  //Wo = if (m/M < 0.5) use ( (m*M) / (M-m) ) else M
  //Q = 255
  //K = (Wo + M) / m
  //Ro = floor( [ ( K * Ri ) - Wo ] / Q )
  //Go = floor( [ ( K * Gi ) - Wo ] / Q )
  //Bo = floor( [ ( K * Bi ) - Wo ] / Q )


  //Check for negatives.
  if(r < 0) {r = 0;} if (g < 0) {g = 0;} if (b < 0) {b = 0;} if (w < 0) {w = 0;}

  return;

}