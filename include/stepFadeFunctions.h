void colorFade(uint32_t pk, uint32_t pb, uint16_t fdur, uint16_t fdel, byte i) 
{

  // BG Colors
  uint8_t r1 = Red(pb);
  uint8_t g1 = Green(pb);
  uint8_t b1 = Blue(pb);
  uint8_t w1 = White(pb);

  // Key Colors
  uint8_t r2 = Red(pk);
  uint8_t g2 = Green(pk);
  uint8_t b2 = Blue(pk);
  uint8_t w2 = White(pk);
  
  //convert seconds to milliseconds
  fdur = fdur * 1000;
  fdel = fdel * 1000;

  //Get the number of steps needed for each pixel transition then divide the fade duration to get step duration.
  if (r1 > r2) rgbwSteps[i].t[0] = fdur / (r1 - r2); else rgbwSteps[i].t[0] = fdur / (r2 - r1);
  if (g1 > g2) rgbwSteps[i].t[1] = fdur / (g1 - g2); else rgbwSteps[i].t[1] = fdur / (g2 - g1);
  if (b1 > b2) rgbwSteps[i].t[2] = fdur / (b1 - b2); else rgbwSteps[i].t[2] = fdur / (b2 - b1);
  if (w1 > w2) rgbwSteps[i].t[3] = fdur / (w1 - w2); else rgbwSteps[i].t[3] = fdur / (w2 - w1);

  //if the old and new values are different  
  if((r2 != r1) || (g2 != g1) || (b2 != b1) || (w2 != w1)) 
  {
    
    //if the elapsed time is greater than the step duration
    if (timeKeeper(pixelTimers[i].t[0]) >= rgbwSteps[i].t[0]) 
    {
      //increment or decrement the pixel value
      if (r2 < r1) r2++; else if (r2 > r1) r2--;
      //and reset the pixel timer
      pixelTimers[i].t[0] = esp_timer_get_time();
    }
    if (timeKeeper(pixelTimers[i].t[1]) >= rgbwSteps[i].t[1]) 
    {
      if (g2 < g1) g2++; else if (g2 > g1) g2--;
      pixelTimers[i].t[1] = esp_timer_get_time();
    }
    if (timeKeeper(pixelTimers[i].t[2]) >= rgbwSteps[i].t[2]) 
    {
      if (b2 < b1) b2++; else if (b2 > b1) b2--;
      pixelTimers[i].t[2] = esp_timer_get_time();
    }
    if (timeKeeper(pixelTimers[i].t[3]) >= rgbwSteps[i].t[3]) 
    {
      if (w2 < w1) w2++; else if (w2 > w1) w2--;
      pixelTimers[i].t[3] = esp_timer_get_time();
    }
    
    //Write to the strip
    int index = i;
  
    strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(r2, g2, b2, w2));

    // Save the new transition value
    prevKeyColor[i] = strip.Color(r2, g2, b2, w2);
    
    strip.show();
  }
  
  //if all the values match
  if ((r2 == r1) && (g2 == g1) && (b2 == b1) && (w2 == w1)) 
  {
    Serial.print("Fade complete");
    Serial.println("");
    Serial.println("");
    keyOffHousekeeping(i);
    prevKeyColor[i] = colorProcessor(program[1].val[0], program[1].val[1], program[1].val[2]);
  }
}
