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
}
void keyOffHousekeeping(int i) 
{
  rgbwSteps[i].rfunc = 0;
  rgbwSteps[i].gfunc = 0;
  rgbwSteps[i].bfunc = 0;
  rgbwSteps[i].wfunc = 0;
  pixelTimers[i].rfunc = 0;
  pixelTimers[i].gfunc = 0;
  pixelTimers[i].bfunc = 0;
  pixelTimers[i].wfunc = 0;
  keyBuffer[i].recentlyReleased = false;
  keyBuffer[i].lastReleased = 0;
}