void retrieveMemory() 
{
    // Program 1 values
    programs[0].val[0] = EEPROM.readUShort(address[0]);
    programs[0].val[1] = EEPROM.readUShort(address[1]);
    programs[0].val[2] = EEPROM.readUShort(address[2]);
    programs[0].val[3] = EEPROM.readUShort(address[3]);
    programs[0].active = EEPROM.readBool(address[4]);

    //Program 2 values
    programs[1].val[0] = EEPROM.readUShort(address[5]);
    programs[1].val[1] = EEPROM.readUShort(address[6]);
    programs[1].val[2] = EEPROM.readUShort(address[7]);
    programs[1].val[3] = EEPROM.readUShort(address[8]);
    programs[1].active = EEPROM.readBool(address[9]);
}

void setMemory() 
{
    // If the saved and current values are different, save the new value.

    // Program 1
    if (programs[0].val[0] != EEPROM.readUShort(address[0]))  { EEPROM.put(address[0], programs[0].val[0]); }
    if (programs[0].val[1] != EEPROM.readUShort(address[1]))  { EEPROM.put(address[1], programs[0].val[1]); }
    if (programs[0].val[2] != EEPROM.readUShort(address[2]))  { EEPROM.put(address[2], programs[0].val[2]); }
    if (programs[0].val[3] != EEPROM.readUShort(address[3]))  { EEPROM.put(address[3], programs[0].val[3]); }
    if (programs[0].active != EEPROM.readBool(address[4]))    { EEPROM.put(address[4], programs[0].active); }

    // Program 2
    if (programs[1].val[0] != EEPROM.readUShort(address[5]))  { EEPROM.put(address[5], programs[1].val[0]); }
    if (programs[1].val[1] != EEPROM.readUShort(address[6]))  { EEPROM.put(address[6], programs[1].val[1]); }
    if (programs[1].val[2] != EEPROM.readUShort(address[7]))  { EEPROM.put(address[7], programs[1].val[2]); }
    if (programs[1].val[3] != EEPROM.readUShort(address[8]))  { EEPROM.put(address[8], programs[1].val[3]); }
    if (programs[1].active != EEPROM.readBool(address[9]))    { EEPROM.put(address[9], programs[1].active); }
    EEPROM.commit();
}