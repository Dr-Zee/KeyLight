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
  
  for(int h = 0; h < 3; h++) {

    //  De-RGBW-ify the values
    c[1].b[h] = c[1].b[h] + c[1].b[3];
    c[0].b[h] = c[0].b[h] + c[0].b[3];

    // Check for overflow
    if (c[1].b[h] > 255) {
      c[1].b[h] = 255;
    }
    if (c[0].b[h] > 255) {
      c[0].b[h] = 255;
    }
  }

  //Get the number of steps needed for each pixel transition then divide the fade duration to get step duration. check for 0 to prevent divide by zero errors.
  if ((rgbwSteps[i].t[0] == 0) && (rgbwSteps[i].t[1] == 0) && (rgbwSteps[i].t[2] == 0)) {
    for (int k = 0; k < 3; k++) {
      if ((c[0].b[k] > c[1].b[k]) && (c[0].b[k] - c[1].b[k] != 0)) rgbwSteps[i].t[k] = fdur / (c[0].b[k] - c[1].b[k]); else if (c[1].b[k] - c[0].b[k] != 0) rgbwSteps[i].t[k] = fdur / (c[1].b[k] - c[0].b[k]);
    }

  }

  for (int j = 0; j < 3; j++) {
    if(c[1].b[j] != c[0].b[j]) {

      if (timeKeeper(pixelTimers[i].t[j]) >= rgbwSteps[i].t[j]) 
      {
        int f = 0;
        if (rgbwSteps[i].t[j] != 0) {
          
          // Get the number of fade steps that may have been missed due to CPU slowdown
          f = round(((timeKeeper(pixelTimers[i].t[j]) - rgbwSteps[i].t[j]) / rgbwSteps[i].t[j]));
        }

        //  If the step duration was missed, get the overflow and skip that many steps to get back up to speed.
        if (f > 0) {

          //  if the value is low, increment.
          if (c[1].b[j] < c[0].b[j]) {

            //  Don't overshoot the target.
            if (c[1].b[j] + f > c[0].b[j]) {
              c[1].b[j] = c[0].b[j];
            } else {
              c[1].b[j] = (c[1].b[j] + f);
            }

            //  if the value is high, decrement
          } else if (c[1].b[j] > c[0].b[j])  {

            //  Don't undershoot the target.
            if (c[1].b[j] - f < c[0].b[j]) {
              c[1].b[j] = c[0].b[j];
            } else {
              c[1].b[j] = (c[1].b[j] - f);
            }
          }

        // If there's no overflow, Increment normally
        } else {
          if (c[1].b[j] < c[0].b[j]) c[1].b[j]++; else if (c[1].b[j] > c[0].b[j]) c[1].b[j]--;
        }

        //  Reset the pixel timer
        pixelTimers[i].t[j] = millis();
      }
    }

    //  Convert back to RGBW
    fadeStage[i] = rgbwConvert(c[1].b[0], c[1].b[1], c[1].b[2], c[1].b[3]);

    for (int l = 0; l < 2; l++) {
      strip.setPixelColor(keyBuffer[i].keyLight[l], fadeStage[i]);
    }
    strip.show();
  }

  //if all the values match
  if ((c[1].b[0] == c[0].b[0]) && (c[1].b[1] == c[0].b[1]) && (c[1].b[2] == c[0].b[2]) && (c[1].b[3] == c[1].b[3])) 
  {
    Serial.print("Fade complete");
    Serial.println("");
    Serial.println("");
    keyOffHousekeeping(i);
  }
}
