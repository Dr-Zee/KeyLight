//Program Strings
char bh[] = "Background Hue";
char bs[] = "Background Saturation";
char bl[] = "Background Luminance";
char kh[] = "Key Hue";
char ks[] = "Key Saturation";
char kl[] = "Key Luminance";
char fdel[] = "Fade Duration";
char fdur[] = "Fade Delay";
char bg[] = "Backround Color";
char ky[] = "Key Color";
char kskp[] = "Key Skips";

void programDisplay() {
  //program1.message1 = bh;
}

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

void setMessage(uint16_t data, char * message) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(message);
  display.println("");
  display.setTextSize(2);
  display.println(data);
  display.display();
}
void setSplash(char * message) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println("");
  display.println(message);
  display.setTextSize(3);
  display.println("");
  display.display();
}

void clearDisplay() {
  display.clearDisplay();
  display.display();
}

void buttonDisplayController() {
  // Set splash messages on program select
  // Not really working.
  if (btnDown[0] == true) {
    if (program1.active == true) {
      setSplash(program1.splash);
    }
    if (program2.active == true) {
      setSplash(program2.splash);
    }
  }
  if (btnDown[1] == true) {
    if (program3.active == true) {
      setSplash(program3.splash);
    }
  }
}