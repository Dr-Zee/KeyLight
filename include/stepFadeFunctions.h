void colorFade(byte i) 
{
  uint16_t fdur = program[0].val[3];

  //  The reference color we're transitioning to.
  c[0].b[0] = Red(prevBgColor[i]);
  c[0].b[1] = Green(prevBgColor[i]);
  c[0].b[2] = Blue(prevBgColor[i]);
  c[0].b[3] = White(prevBgColor[i]);

  //  The color of the current fade step
  c[1].b[0] = Red(fadeStage[i]);
  c[1].b[1] = Green(fadeStage[i]);
  c[1].b[2] = Blue(fadeStage[i]);
  c[1].b[3] = White(fadeStage[i]);
  
  for(int j = 0; j < 3; j++) {
     //  De-RGBW-ify the values
     c[0].b[j] = c[0].b[j] + c[0].b[3];
     c[1].b[j] = c[1].b[j] + c[1].b[3];
  }

  //  Check for overflow
  for(int k = 0; k < 2; k++) {
    if (c[ik].b[0] > 255) { c[k].b[0] = 255; } if (c[k].b[1] > 255) { c[k].b[1] = 255; } if (c[k].b[2] > 255) { c[k].b[2] = 255; }
  }

  //Get the number of steps needed for each pixel transition then divide the fade duration to get step duration.
  if ((rgbwSteps[i].t[0] == 0) && (rgbwSteps[i].t[1] == 0) && (rgbwSteps[i].t[2] == 0)) {
    for(int l = 0; l < 3; l++) {
      if (c[0].b[l] > c[1].b[l]) rgbwSteps[l].t[0] = fdur / (c[0].b[l] - c[1].b[l]); else rgbwSteps[l].t[l] = fdur / (c[1].b[l] - c[0].b[l]);
    }
  }


  for (int j = 0; j < 3; j++) {

    if(c[1].b[j] != c[0].b[j]) {

      if (timeKeeper(pixelTimers[i].t[j]) >= rgbwSteps[i].t[j]) 
      {
        // Get the number of fade steps that may have been missed due to CPU slowdown
        int rf = round(((timeKeeper(pixelTimers[i].t[j]) - rgbwSteps[i].t[j]) / rgbwSteps[i].t[j]));

        //  If the step duration was missed, get the overflow and skip that many steps to get back up to speed.
        if (rf > 0) {
          //  if the value is low, increment.
          if (c[1].b[j] < c[0].b[j]) {
            //  Make sure not to overshoot the target.
            if (c[1].b[j] + rf > c[0].b[j]) {
              c[1].b[j] = c[0].b[j];
            } else {
              c[1].b[j] = (c[1].b[j] + rf);
            }
            //  if the value is high, decrement
          } else if (c[1].b[j] > c[0].b[j])  {
            if (c[1].b[j] - rf < c[0].b[j]) {
              c[1].b[j] = c[0].b[j];
            } else {
              c[1].b[j] = (c[1].b[j] - rf);
            }
          }
          // Increment normally
        } else {
          if (c[1].b[j] < c[0].b[j]) c[1].b[j]++; else if (c[1].b[j] > c[0].b[j]) c[1].b[j]--;
        }
        //and reset the pixel timer
        pixelTimers[i].t[j] = millis();
      }
    }
  }
  //  Convert back to RGBW
  fadeStage[i] = rgbwConvert(c[1].b[0], c[1].b[1], c[1].b[2], c[1].b[3]);

  for (int j = 0; j < 2; j++) {
    strip.setPixelColor(keyBuffer[i].keyLight[j], fadeStage[i]);
  }
  strip.show();
  
  //if all the values match
  if ((c[1].b[0] == c[0].b[0]) && (c[1].b[1] == c[0].b[1]) && (c[1].b[2] == c[0].b[2]) && (c[1].b[3] == c[0].b[3])) 
  {
    keyOffHousekeeping(i);
  }
}
