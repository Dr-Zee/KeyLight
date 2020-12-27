void colorFade(byte r, byte g, byte b, byte w, uint32_t d, byte key) {
  
  //convert seconds to milliseconds
  d = d * 1000;
  for(int i = 1; i < 88; ++i) {
   
    //Get the number of steps needed for each pixel transition then divide the fade duration to get step length.
    if (r > prevKeyColor[i].r)rgbSteps.rfunc = d / (r - prevKeyColor[i].r); else rgbSteps.rfunc = d / (prevKeyColor[i].r - r);
    if (g > prevKeyColor[i].g)rgbSteps.gfunc = d / (g - prevKeyColor[i].g); else rgbSteps.gfunc = d / (prevKeyColor[i].g - g);
    if (b > prevKeyColor[i].b)rgbSteps.bfunc = d / (b - prevKeyColor[i].b); else rgbSteps.bfunc = d / (prevKeyColor[i].b - b);
    if (w > prevKeyColor[i].w)rgbSteps.wfunc = d / (w - prevKeyColor[i].w); else rgbSteps.wfunc = d / (prevKeyColor[i].w - w);
  
    //if the old and new values are different  
    if((prevKeyColor[i].r != r) || (prevKeyColor[i].g != g) || (prevKeyColor[i].b != b) || (prevKeyColor[i].w != w)) {
      
      //if the elapsed time is greater than the step duration
      if (millis() - pixelTimers.rfunc >= rgbSteps.rfunc) {
        
        //increment or decrement the pixel value
        if (prevKeyColor[i].r < r) prevKeyColor[i].r++; else if (prevKeyColor[i].r > r) prevKeyColor[i].r--;
          //and reset the pixel timer
          pixelTimers.rfunc = millis();
        }
        if (millis() - pixelTimers.gfunc >= rgbSteps.gfunc) {
          if (prevKeyColor[i].g < g) prevKeyColor[i].g++; else if (prevKeyColor[i].g > g) prevKeyColor[i].g--;
          pixelTimers.gfunc = millis();
        }
        if (millis() - pixelTimers.bfunc >= rgbSteps.bfunc) {
          if (prevKeyColor[i].b < b) prevKeyColor[i].b++; else if (prevKeyColor[i].b > b) prevKeyColor[i].b--;
          pixelTimers.bfunc = millis();
        }
        if (millis() - pixelTimers.wfunc >= rgbSteps.wfunc) {
          if (prevKeyColor[i].w < w) prevKeyColor[i].w++; else if (prevKeyColor[i].w > w) prevKeyColor[i].w--;
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
    if ((prevKeyColor[i].r == r) && (prevKeyColor[i].g == g) && (prevKeyColor[i].b == b) && (prevKeyColor[i].w == w)) {
      
      Serial.print("Rub one out.");
      Serial.println("");
      Serial.println("");
      
    }
  }
}
