//Program Strings
char bh[] = "Background Hue";
char bs[] = "Background Saturation";
char bl[] = "Background Luminance";
char kh[] = "Key Hue";
char ks[] = "Key Saturation";
char kl[] = "Key Luminance";
char fdel[] = "Fade Duration";
char fdur[] = "Fade Delay";
char bg[] = "Backround";
char ky[] = "Keys";
char kskp[] = "Key Skips";
char save[] = "Saved";

char *messages[12] = {bg, ky, save, kskp, ks, kl, fdel, fdur, bg, ky, kskp, save};


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
  display.println(message);
  display.println("");
  display.setTextSize(2);
  display.println(data);
  display.display();
}

void setSplash(char * message) 
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println("");
  display.setTextSize(2);
  display.println(message);
  display.display();
  delay(800);
}

void clearDisplay() 
{
  display.clearDisplay();
  display.display();
}
