void colorFade(uint32_t d, byte key) {
  
  //convert seconds to milliseconds
  d = d * 1000;
  for(int i = 1; i < 88; ++i) {
    if(fadeDelay >= keyBuffer[i].lastReleased) {
      //Get the number of steps needed for each pixel transition then divide the fade duration to get step length.
      if (prevBgColor[i].r > prevKeyColor[i].r)rgbwSteps.rfunc = d / (prevBgColor[i].r - prevKeyColor[i].r); else rgbwSteps.rfunc = d / (prevKeyColor[i].r -prevBgColor[i].r);
      if (prevBgColor[i].g > prevKeyColor[i].g)rgbwSteps.gfunc = d / (prevBgColor[i].g - prevKeyColor[i].g); else rgbwSteps.gfunc = d / (prevKeyColor[i].g -prevBgColor[i].g);
      if (prevBgColor[i].b > prevKeyColor[i].b)rgbwSteps.bfunc = d / (prevBgColor[i].b - prevKeyColor[i].b); else rgbwSteps.bfunc = d / (prevKeyColor[i].b -prevBgColor[i].b);
      if (prevBgColor[i].w > prevKeyColor[i].w)rgbwSteps.wfunc = d / (prevBgColor[i].w - prevKeyColor[i].w); else rgbwSteps.wfunc = d / (prevKeyColor[i].w -prevBgColor[i].w);
    
      //if the old and new values are different  
      if((prevKeyColor[i].r != prevBgColor[i].r) || (prevKeyColor[i].g != prevBgColor[i].g) || (prevKeyColor[i].b != prevBgColor[i].b) || (prevKeyColor[i].w != prevBgColor[i].w)) {
        
        //if the elapsed time is greater than the step duration
        if (millis() - pixelTimers.rfunc >= rgbwSteps.rfunc) {
          
          //increment or decrement the pixel value
          if (prevKeyColor[i].r < prevBgColor[i].r) prevKeyColor[i].r++; else if (prevKeyColor[i].r > prevBgColor[i].r) prevKeyColor[i].r--;
            //and reset the pixel timer
            pixelTimers.rfunc = millis();
          }
          if (millis() - pixelTimers.gfunc >= rgbwSteps.gfunc) {
            if (prevKeyColor[i].g < prevBgColor[i].g) prevKeyColor[i].g++; else if (prevKeyColor[i].g > prevBgColor[i].g) prevKeyColor[i].g--;
            pixelTimers.gfunc = millis();
          }
          if (millis() - pixelTimers.bfunc >= rgbwSteps.bfunc) {
            if (prevKeyColor[i].b < prevBgColor[i].b) prevKeyColor[i].b++; else if (prevKeyColor[i].b > prevBgColor[i].b) prevKeyColor[i].b--;
            pixelTimers.bfunc = millis();
          }
          if (millis() - pixelTimers.wfunc >= rgbwSteps.wfunc) {
            if (prevKeyColor[i].w < prevBgColor[i].w) prevKeyColor[i].w++; else if (prevKeyColor[i].w > prevBgColor[i].w) prevKeyColor[i].w--;
            pixelTimers.wfunc = millis();
          }
        
        //Write to the strip
        int index = i;
        for(int i=0; i < 2; i++) {
          strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(strip.gamma8(prevKeyColor[index].r), strip.gamma8(prevKeyColor[index].g), strip.gamma8(prevKeyColor[index].b), strip.gamma8(prevKeyColor[index].w)));
        }
        strip.show();
      }
      
      //if all the values match
      if ((prevKeyColor[i].r == prevBgColor[i].r) && (prevKeyColor[i].g == prevBgColor[i].g) && (prevKeyColor[i].b == prevBgColor[i].b) && (prevKeyColor[i].w == prevBgColor[i].w)) {
        
        Serial.print("Rub one out.");
        Serial.println("");
        Serial.println("");
        
      }
    }
  }
}
