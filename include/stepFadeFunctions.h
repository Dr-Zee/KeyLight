void colorFade(uint32_t pk, uint32_t pb, uint32_t fdur, uint32_t fdel, byte i) 
{

  uint8_t BGR = Red(pb);
  uint8_t BGG = Green(pb);
  uint8_t BGB = Blue(pb);
  uint8_t BGW = White(pb);

  uint8_t KR = Red(pk);
  uint8_t KG = Green(pk);
  uint8_t KB = Blue(pk);
  uint8_t KW = White(pk);
  
  //convert seconds to milliseconds
  fadeDuration = fadeDuration * 1000;

  if(millis() - keyBuffer[i].lastReleased >= fadeDelay) 
  {
    //Get the number of steps needed for each pixel transition then divide the fade duration to get step length.
    if (BGR > KR)rgbwSteps.rfunc = fdur / (BGR - KR); else rgbwSteps.rfunc = fdur / (KR -BGR);
    if (BGG > KG)rgbwSteps.gfunc = fdur / (BGG - KG); else rgbwSteps.gfunc = fdur / (KG -BGG);
    if (BGB > KB)rgbwSteps.bfunc = fdur / (BGB - KB); else rgbwSteps.bfunc = fdur / (KB -BGB);
    if (BGW > KW)rgbwSteps.wfunc = fdur / (BGW - KW); else rgbwSteps.wfunc = fdur / (KW -BGW);
  
    //if the old and new values are different  
    if((KR != BGR) || (KG != BGG) || (KB != BGB) || (KW != BGW)) 
    {
      
      //if the elapsed time is greater than the step duration
      if (millis() - pixelTimers.rfunc >= rgbwSteps.rfunc) 
      {
        
        //increment or decrement the pixel value
        if (KR < BGR) KR++; else if (KR > BGR) KR--;
          //and reset the pixel timer
          pixelTimers.rfunc = millis();
        }
        if (millis() - pixelTimers.gfunc >= rgbwSteps.gfunc) 
        {
          if (KG < BGG) KG++; else if (KG > BGG) KG--;
          pixelTimers.gfunc = millis();
        }
        if (millis() - pixelTimers.bfunc >= rgbwSteps.bfunc) 
        {
          if (KB < BGB) KB++; else if (KB > BGB) KB--;
          pixelTimers.bfunc = millis();
        }
        if (millis() - pixelTimers.wfunc >= rgbwSteps.wfunc) 
        {
          if (KW < BGW) KW++; else if (KW > BGW) KW--;
          pixelTimers.wfunc = millis();
        }
      
      //Write to the strip
      int index = i;
      for(int i=0; i < 2; i++) 
      {
        strip.setPixelColor(keyBuffer[index].keyLight[i], strip.Color(strip.gamma8(KR), strip.gamma8(KG), strip.gamma8(KB), strip.gamma8(KW)));
      }
      strip.show();
    }
    
    //if all the values match
    if ((KR == BGR) && (KG == BGG) && (KB == BGB) && (KW == BGW)) 
    {
      Serial.print("Fade complete");
      Serial.println("");
      Serial.println("");
      keyOffHousekeeping(i);
    }
  }
}
