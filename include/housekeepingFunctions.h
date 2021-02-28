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
}
void keyOffHousekeeping(int i) 
{
  fadeStage[i] = prevKeyColor[i];
  keyBuffer[i].recentlyReleased = false;
  keyBuffer[i].lastReleased = 0;
  for (int j = 0; j < 4; j++) {
    pixelTimers[i].t[j] = 0;
    rgbwSteps[i].t[j] = 0;
  }
}