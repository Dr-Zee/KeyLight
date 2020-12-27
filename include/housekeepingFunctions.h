// Functions broken out for correct execution order.
// keyOn and keyOff housekeeping tasks.
void keyOnHousekeeping(int key) {
  if(colorSkips > 5) {
    colorSkips = 0;
  }
  colorSkips++;
  keyBuffer[key].runOnce = true;
}
void keyOffHousekeeping(int i) {
  keyBuffer[i].recentlyReleased = false;
  keyBuffer[i].lastReleased = 0;
}