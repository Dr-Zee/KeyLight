// Functions broken out for correct execution order.
// keyOn and keyOff housekeeping tasks.
void keyOnHousekeeping(int key) 
{
  //if(colorSkips > 5) 
  //{
  //  colorSkips = 0;
  //}
  //colorSkips++;
  keyBuffer[key].runOnce = true;

  //  Set a fresh background color reference in case the key was in mid-fade
  fadeStage[key] = prevKeyColor[key];
  for (int j = 0; j < 4; j++) {
    pixelTimers[key].t[j] = 0;
    rgbwSteps[key].t[j] = 0;
  }
  tempTimer = millis();
}
void keyOffHousekeeping(int i) 
{
  Serial.print("temp timer: ");
  Serial.print(tempTimer);
  Serial.println("");
  fadeStage[i] = prevKeyColor[i];
  keyBuffer[i].recentlyReleased = false;
  keyBuffer[i].lastReleased = 0;
  for (int j = 0; j < 4; j++) {
    pixelTimers[i].t[j] = 0;
    rgbwSteps[i].t[j] = 0;
  }
}