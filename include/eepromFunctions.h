void retrieveMemory() 
{
    programs[0].hue = EEPROM.readUShort(address[0]);
    Serial.print(EEPROM.readUShort(address[0]));
    Serial.println(" ");
    programs[0].saturation = EEPROM.readByte(address[1]);
    Serial.print(EEPROM.readByte(address[1]));
    Serial.println(" ");
    programs[0].luminance = EEPROM.readByte(address[2]);
    Serial.print(EEPROM.readByte(address[2]));
    Serial.println(" ");
    programs[0].duration = EEPROM.readUShort(address[3]);
    Serial.print(EEPROM.readUShort(address[3]));
    Serial.println(" ");
    programs[0].active = EEPROM.readBool(address[4]);
    Serial.print(EEPROM.readBool(address[4]));
    Serial.println(" ");
    programs[1].hue = EEPROM.readUShort(address[5]);
    Serial.print(EEPROM.readUShort(address[5]));
    Serial.println(" ");
    programs[1].saturation = EEPROM.readByte(address[6]);
    Serial.print(EEPROM.readByte(address[6]));
    Serial.println(" ");
    programs[1].luminance = EEPROM.readByte(address[7]);
    Serial.print(EEPROM.readByte(address[7]));
    Serial.println(" ");
    programs[1].duration = EEPROM.readUShort(address[8]);
    Serial.print(EEPROM.readUShort(address[8]));
    Serial.println(" ");
    programs[1].active = EEPROM.readBool(address[9]);
    Serial.print(EEPROM.readBool(address[9]));
    Serial.println(" ");
}

void setMemory() 
{
    // Program 1
    if (programs[0].hue != EEPROM.readUShort(address[0])) 
    {
        EEPROM.put(address[0], programs[0].hue);
    }
    if (programs[0].saturation != EEPROM.readByte(address[1])) 
    {
        EEPROM.put(address[1], programs[0].saturation);
    }
    if (programs[0].luminance != EEPROM.readByte(address[2])) 
    {
        EEPROM.put(address[2], programs[0].luminance);
    }
    if (programs[0].duration != EEPROM.readUShort(address[3])) 
    {
        EEPROM.put(address[3], 1500);
    }
    if (programs[0].active != EEPROM.readBool(address[4])) 
    {
        EEPROM.put(address[4], 1);
    }
    // Program 2
    if (programs[1].hue != EEPROM.readUShort(address[5])) 
    {
        EEPROM.put(address[5], programs[1].hue);
    }
    if (programs[1].saturation != EEPROM.readByte(address[6])) 
    {
        EEPROM.put(address[6], programs[1].saturation);
    }
    if (programs[1].luminance != EEPROM.readByte(address[7])) 
    {
        EEPROM.put(address[7], programs[1].luminance);
    }
    if (programs[1].duration != EEPROM.readUShort(address[8])) 
    {
        EEPROM.put(address[8], 1500);
    }
    if (programs[1].active != EEPROM.readBool(address[9])) 
    { 
        EEPROM.put(address[9], 0);
    }
    EEPROM.commit();
}