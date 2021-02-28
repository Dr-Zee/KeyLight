void colorFade(byte i) 
{

  uint32_t bg =   prevBgColor[i];
  uint32_t key =   fadeStage[i];

  uint16_t fdur = program[0].val[3];

  // BG Colors
  uint8_t r1 = Red(bg);
  uint8_t g1 = Green(bg);
  uint8_t b1 = Blue(bg);
  uint8_t w1 = White(bg);

  uint8_t r2 = Red(key);
  uint8_t g2 = Green(key);
  uint8_t b2 = Blue(key);
  uint8_t w2 = White(key);

  //  De-RGBW-ify the values
  r1 = r1 + w1;
  g1 = g1 + w1;
  b1 = b1 + w1;

  r2 = r2 + w2;
  g2 = g2 + w2;
  b2 = b2 + w2;

  if (r1 > 255) { r1 = 255; } if (g1 > 255) { g1 = 255; } if (b1 > 255) { b1 = 255; }
  if (r2 > 255) { r2 = 255; } if (g2 > 255) { g2 = 255; } if (b2 > 255) { b2 = 255; }

  //Get the number of steps needed for each pixel transition then divide the fade duration to get step duration.
  if ((rgbwSteps[i].t[0] == 0) && (rgbwSteps[i].t[1] == 0) && (rgbwSteps[i].t[2] == 0)) {
    if (r1 > r2) rgbwSteps[i].t[0] = fdur / (r1 - r2); else rgbwSteps[i].t[0] = fdur / (r2 - r1);
    if (g1 > g2) rgbwSteps[i].t[1] = fdur / (g1 - g2); else rgbwSteps[i].t[1] = fdur / (g2 - g1);
    if (b1 > b2) rgbwSteps[i].t[2] = fdur / (b1 - b2); else rgbwSteps[i].t[2] = fdur / (b2 - b1);
  }

  //if the old and new values are different  
  if((r2 != r1) || (g2 != g1) || (b2 != b1)) 
  {
    
    //if the elapsed time is greater than the step duration
    if (timeKeeper(pixelTimers[i].t[0]) >= rgbwSteps[i].t[0]) 
    {
      //increment or decrement the pixel value
      if (r2 < r1) r2++; else if (r2 > r1) r2--;
      //and reset the pixel timer
      pixelTimers[i].t[0] = millis();
    }
    if (timeKeeper(pixelTimers[i].t[1]) >= rgbwSteps[i].t[1]) 
    {
      if (g2 < g1) g2++; else if (g2 > g1) g2--;
      pixelTimers[i].t[1] = millis();
    }
    if (timeKeeper(pixelTimers[i].t[2]) >= rgbwSteps[i].t[2]) 
    {
      if (b2 < b1) b2++; else if (b2 > b1) b2--;
      pixelTimers[i].t[2] = millis();
    }

    //  Convert back to RGBW
    fadeStage[i] = rgbwConvert(r2, g2, b2, w2);

    for (int j = 0; j < 2; j++) {
      strip.setPixelColor(keyBuffer[i].keyLight[j], fadeStage[i]);
    }
    strip.show();
  }

  //if all the values match
  if ((r2 == r1) && (g2 == g1) && (b2 == b1) && (w2 == w1)) 
  {
    Serial.print("Fade complete");
    Serial.println("");
    Serial.println("");
    keyOffHousekeeping(i);
  }
}
