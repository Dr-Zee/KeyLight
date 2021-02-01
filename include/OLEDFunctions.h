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

void buttonDisplayController() {
  if (btn1_down == true) {
    if (btn1_prg1 == true) {
      setSplash(bg);
    }
    if (btn1_prg2 == true) {
      setSplash(ky);
    }
  }
  if (btn2_down == true) {
    if (btn2_prg1 == true) {
      //setSplash(bg);
    }
    if (btn2_prg2 == true) {
      //setSplash(ky);
    }
  }
  if (btn3_down == true) {
    if (btn3_prg1 == true) {
      //setSplash(bg);
    }
    if (btn3_prg2 == true) {
      //setSplash(ky);
    }
  }
  if (btn4_down == true) {
    if (btn4_prg1 == true) {
      setSplash(fdur);
    }
    if (btn4_prg2 == true) {
      setSplash(fdel);
    }
  }
}