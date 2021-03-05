void setMessages() {
  program[0].splash = "Background";
  program[1].splash = "Keys";
  program[2].splash = "Saved";
  program[3].splash = "BG Skips";
  program[4].splash = "Key Skips";

  program[0].message[0] = "Background Hue";
  program[0].message[1] = "Background Saturation";
  program[0].message[2] = "Background Luminance";
  program[0].message[3] = "Fade Duration";

  program[1].message[0] = "Key Hue";
  program[1].message[1] = "Key Saturation";
  program[1].message[2] = "Key Luminance";
  program[1].message[3] = "Fade Delay";

  program[3].message[0] = "Bg Skip Hue";
  program[3].message[1] = "Bg Skip Saturation";
  program[3].message[2] = "Bg Skip Luminance";
  program[3].message[3] = "Chance of BG Skips";

  program[4].message[0] = "Key Skip Hue";
  program[4].message[1] = "Key Skip Saturation";
  program[4].message[2] = "Key Skip Luminance";
  program[4].message[3] = "Chance of Key Skips";
}

void showLogo() 
{
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

void setMessage(uint16_t data, int message) 
{
  float duration;

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(program[sys.active].message[message]);
  display.println("");
  display.setTextSize(2);

  //  convert duration count to float
  if (((sys.active == 0) || (sys.active == 1)) && (message == 3)) {
    duration = (float) data / 1000.0;
    display.print(duration, 1);
    display.setTextSize(1);
    display.println(" seconds");
  }
  //  display keyskip percentages
  else if (((sys.active == 3) || (sys.active == 4)) && (message == 3)) {
    display.print(data);
    display.print("%");
    display.setTextSize(1);
    display.println(" chance");
  }
  else {
    display.print(data);
  }
  display.display();
}

void setSplash() 
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println("");
  display.setTextSize(2);
  display.println(program[sys.active].splash);
  display.display();
  delay(1000);
}

void colorSkipSplash() 
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1.5);
  display.println("Colorskips");
  display.setTextSize(1.5);
  if (colorskips == true) {
    display.println("On");
  } else {
    display.println("Off");
  }
  display.display();
  delay(1000);
}

void clearDisplay() 
{
  display.clearDisplay();
  display.display();
}