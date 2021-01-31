void showLogo() {
  display.clearDisplay();
  display.setRotation(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(150,0);

  display.setTextSize(1);
  display.println("");

  display.setTextSize(2);
  display.println("keyLight");

  display.display();
}

void clearDisplay() {
  display.clearDisplay();
  display.display();
}
