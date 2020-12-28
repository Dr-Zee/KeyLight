void colorFade(uint32_t fadeDuration, uint32_t fadeDelay, byte i) 
{
  
  //convert seconds to milliseconds
  fadeDuration = fadeDuration * 1000;

  if(millis() - keyBuffer[i].lastReleased >= fadeDelay) 
  {
    //Get the number of steps needed for each pixel transition then divide the fade duration to get step length.
    if (prevBgColor[i].r > prevKeyColor[i].r)rgbwSteps.rfunc = fadeDuration / (prevBgColor[i].r - prevKeyColor[i].r); else rgbwSteps.rfunc = fadeDuration / (prevKeyColor[i].r -prevBgColor[i].r);
    if (prevBgColor[i].g > prevKeyColor[i].g)rgbwSteps.gfunc = fadeDuration / (prevBgColor[i].g - prevKeyColor[i].g); else rgbwSteps.gfunc = fadeDuration / (prevKeyColor[i].g -prevBgColor[i].g);
    if (prevBgColor[i].b > prevKeyColor[i].b)rgbwSteps.bfunc = fadeDuration / (prevBgColor[i].b - prevKeyColor[i].b); else rgbwSteps.bfunc = fadeDuration / (prevKeyColor[i].b -prevBgColor[i].b);
    if (prevBgColor[i].w > prevKeyColor[i].w)rgbwSteps.wfunc = fadeDuration / (prevBgColor[i].w - prevKeyColor[i].w); else rgbwSteps.wfunc = fadeDuration / (prevKeyColor[i].w -prevBgColor[i].w);
  
    //if the old and new values are different  
    if((prevKeyColor[i].r != prevBgColor[i].r) || (prevKeyColor[i].g != prevBgColor[i].g) || (prevKeyColor[i].b != prevBgColor[i].b) || (prevKeyColor[i].w != prevBgColor[i].w)) 
    {
      
      //if the elapsed time is greater than the step duration
      if (millis() - pixelTimers.rfunc >= rgbwSteps.rfunc) 
      {
        
        //increment or decrement the pixel value
        if (prevKeyColor[i].r < prevBgColor[i].r) prevKeyColor[i].r++; else if (prevKeyColor[i].r > prevBgColor[i].r) prevKeyColor[i].r--;
          //and reset the pixel timer
          pixelTimers.rfunc = millis();
        }
        if (millis() - pixelTimers.gfunc >= rgbwSteps.gfunc) 
        {
          if (prevKeyColor[i].g < prevBgColor[i].g) prevKeyColor[i].g++; else if (prevKeyColor[i].g > prevBgColor[i].g) prevKeyColor[i].g--;
          pixelTimers.gfunc = millis();
        }
        if (millis() - pixelTimers.bfunc >= rgbwSteps.bfunc) 
        {
          if (prevKeyColor[i].b < prevBgColor[i].b) prevKeyColor[i].b++; else if (prevKeyColor[i].b > prevBgColor[i].b) prevKeyColor[i].b--;
          pixelTimers.bfunc = millis();
        }
        if (millis() - pixelTimers.wfunc >= rgbwSteps.wfunc) 
        {
          if (prevKeyColor[i].w < prevBgColor[i].w) prevKeyColor[i].w++; else if (prevKeyColor[i].w > prevBgColor[i].w) prevKeyColor[i].w--;
          pixelTimers.wfunc = millis();
        }
      
      //Write to the strip
      int index = i;
      for(int i=0; i < 2; i++) 
      {
        strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(strip.gamma8(prevKeyColor[index].r), strip.gamma8(prevKeyColor[index].g), strip.gamma8(prevKeyColor[index].b), strip.gamma8(prevKeyColor[index].w)));
      }
      strip.show();
    }
    
    //if all the values match
    if ((prevKeyColor[i].r == prevBgColor[i].r) && (prevKeyColor[i].g == prevBgColor[i].g) && (prevKeyColor[i].b == prevBgColor[i].b) && (prevKeyColor[i].w == prevBgColor[i].w)) 
    {
      Serial.print("Fade complete");
      Serial.println("");
      Serial.println("");
      keyOffHousekeeping(i);
    }
  }
}
