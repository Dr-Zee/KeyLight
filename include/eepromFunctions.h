void retrieveMemory() 
{
    programs[0].hue = EEPROM.readUShort(address[0]);
    programs[0].saturation = EEPROM.readUInt(address[1]);
    programs[0].luminance = EEPROM.readUInt(address[2]);
    programs[0].duration = EEPROM.readUShort(address[3]);
    programs[0].active = EEPROM.readBool(address[4]);
    programs[1].hue = EEPROM.readUShort(address[5]);
    programs[1].saturation = EEPROM.readUInt(address[6]);
    programs[1].luminance = EEPROM.readUInt(address[7]);
    programs[1].duration = EEPROM.readUShort(address[8]);
    programs[1].active = EEPROM.readBool(address[9]);
}

void setMemory() 
{
    // Program 1
    if (programs[0].hue != EEPROM.readUShort(address[0])) 
    {
        EEPROM.put(address[0], programs[0].hue);
    }
    if (programs[0].saturation != EEPROM.readUInt(address[1])) 
    {
        EEPROM.put(address[1], programs[0].saturation);
    }
    if (programs[0].luminance != EEPROM.readUInt(address[2])) 
    {
        EEPROM.put(address[2], programs[0].luminance);
    }
    if (programs[0].duration != EEPROM.readUShort(address[3])) 
    {
        EEPROM.put(address[3], programs[0].duration);
    }
    if (programs[0].active != EEPROM.readBool(address[4])) 
    {
        EEPROM.put(address[4], programs[0].active);
    }
    // Program 2
    if (programs[1].hue != EEPROM.readUShort(address[5])) 
    {
        EEPROM.put(address[5], programs[1].hue);
    }
    if (programs[1].saturation != EEPROM.readUInt(address[6])) 
    {
        EEPROM.put(address[6], programs[1].saturation);
    }
    if (programs[1].luminance != EEPROM.readUInt(address[7])) 
    {
        EEPROM.put(address[7], programs[1].luminance);
    }
    if (programs[1].duration != EEPROM.readUShort(address[8])) 
    {
        EEPROM.put(address[8], programs[1].duration);
    }
    if (programs[1].active != EEPROM.readBool(address[9])) 
    {
        EEPROM.put(address[9], programs[1].active);
    }
    EEPROM.commit();
}