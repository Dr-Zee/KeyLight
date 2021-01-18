void showLogo() {
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setCursor(150,0);

  display.setTextSize(1);
  display.println("");

  display.setTextSize(2);
  display.println("keyLight");
  
  display.display();
}

void displayController(void) {
  count = encoder.getCount();
  if(count != oldCount) {
    
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    
    display.setTextSize(1);
    display.println("Background Color");
  
    display.println("");
    
    display.setTextSize(2);
    display.println(count);
    
    display.display();
    
    oldCount = count;
    lastChange = millis();
  }
  if (millis() - lastChange > logoDelay) {
    showLogo();
  }
}