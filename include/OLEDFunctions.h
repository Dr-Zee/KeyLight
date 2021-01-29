void showLogo() {
  display.clearDisplay();
  display.setRotation(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(150,0);

  display.setTextSize(1);
  display.println("");

  display.setTextSize(2);
  display.println("keyLight");

 // display.display();
}

void displayController(void) {
  if(count1 != oldCount1) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    
    display.setTextSize(1);
    display.println("Background Color");
  
    display.println("");
    
    display.setTextSize(2);
    display.println(count1);
    
    display.display();

    oldCount1 = count1;
    //lastChange = millis();
  }
  // TODO update the variables below.
  //After timeout period, show logo.
  //then after another timeout period, deactivate screen.
  //if (millis() - lastChange > logoDelay) {
  //  showLogo();
 //}
}