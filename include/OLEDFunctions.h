void setMessages() {
  program[0].splash = "Background";
  program[1].splash = "Keys";
  program[2].splash = "Saved";
  program[3].splash = "Key Skips";
  program[3].splash = "Background Skips";

  program[0].message[0] = "Background Hue";
  program[0].message[1] = "Background Saturation";
  program[0].message[2] = "Background Luminance";
  program[0].message[3] = "Fade Duration";

  program[1].message[0] = "Key Hue";
  program[1].message[1] = "Key Saturation";
  program[1].message[2] = "Key Luminance";
  program[1].message[3] = "Fade Delay";

  program[2].message[0] = "Background Skips Hue";
  program[2].message[1] = "Background skips Saturation";
  program[2].message[2] = "Background Skips Luminance";
  program[2].message[3] = "Background Skips";

  program[3].message[0] = "Key Skip Hue";
  program[3].message[1] = "Key Skip Saturation";
  program[3].message[2] = "Key Skip Luminance";
  program[3].message[3] = "Key Skips";
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
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(program[sys.active].message[message]);
  display.println("");
  display.setTextSize(2);
  display.println(data);
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

void clearDisplay() 
{
  display.clearDisplay();
  display.display();
}