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
  if (r1 > r2) rgbwSteps[i].rfunc = fdur / (r1 - r2); else rgbwSteps[i].rfunc = fdur / (r2 - r1);
  if (g1 > g2) rgbwSteps[i].gfunc = fdur / (g1 - g2); else rgbwSteps[i].gfunc = fdur / (g2 - g1);
  if (b1 > b2) rgbwSteps[i].bfunc = fdur / (b1 - b2); else rgbwSteps[i].bfunc = fdur / (b2 - b1);
  if (w1 > w2) rgbwSteps[i].wfunc = fdur / (w1 - w2); else rgbwSteps[i].wfunc = fdur / (w2 - w1);

  //if the old and new values are different  
  if((r2 != r1) || (g2 != g1) || (b2 != b1) || (w2 != w1)) 
  {
    
    //if the elapsed time is greater than the step duration
    if (timeKeeper(pixelTimers[i].rfunc) >= rgbwSteps[i].rfunc) 
    {
      //increment or decrement the pixel value
      if (r2 < r1) r2++; else if (r2 > r1) r2--;
      //and reset the pixel timer
      pixelTimers[i].rfunc = esp_timer_get_time();
    }
    if (timeKeeper(pixelTimers[i].gfunc) >= rgbwSteps[i].gfunc) 
    {
      if (g2 < g1) g2++; else if (g2 > g1) g2--;
      pixelTimers[i].gfunc = esp_timer_get_time();
    }
    if (timeKeeper(pixelTimers[i].bfunc) >= rgbwSteps[i].bfunc) 
    {
      if (b2 < b1) b2++; else if (b2 > b1) b2--;
      pixelTimers[i].bfunc = esp_timer_get_time();
    }
    if (timeKeeper(pixelTimers[i].wfunc) >= rgbwSteps[i].wfunc) 
    {
      if (w2 < w1) w2++; else if (w2 > w1) w2--;
      pixelTimers[i].wfunc = esp_timer_get_time();
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
    prevKeyColor[i] = colorProcessor(programs[1].val[0], programs[1].val[1], programs[1].val[2]);
  }
}
