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
    if (prg[0] == true) {
      setSplash(bg);
    }
    if (prg[1] == true) {
      setSplash(ky);
    }
  }
  if (btnDown[1] == true) {
    if (prg[2] == true) {
      
    }
    if (prg[3] == true) {
      
    }
  }
  if (btnDown[2] == true) {
    if (prg[4] == true) {
      
    }
    if (prg[5] == true) {
      
    }
  }
  if (btnDown[3] == true) {
    if (prg[6] == true) {
      //setSplash(fdur);
    }
    if (prg[7] == true) {
      //setSplash(fdel);
    }
  }
}