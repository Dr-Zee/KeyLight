void readMemory() {
    if (programs[0].active == true) {
        count1 = EEPROM.readUShort(address[0]);
        count2 = EEPROM.readByte(address[1]);
        count3 = EEPROM.readByte(address[2]);
        count4 = EEPROM.readUShort(address[3]);
    }
    if (programs[1].active == true) {
        count1 = EEPROM.readUShort(address[4]);
        count2 = EEPROM.readByte(address[5]);
        count3 = EEPROM.readByte(address[6]);
        count4 = EEPROM.readUShort(address[7]);
    }
    if (programs[2].active == true) {
        count1 = EEPROM.readUShort(address[8]);
        count2 = EEPROM.readByte(address[9]);
        count3 = EEPROM.readByte(address[10]);
        count4 = EEPROM.readUShort(address[11]);
    }
}

void retrieveSettings() {
    for(int i = 0; i < 15; i++) {
        int program = 1;
        if ((i > 4) && i < 9) {program = 2;} else if (i > 9) {program = 3;}
        programs[program].hue = EEPROM.read(address[i]);
        programs[program].saturation = EEPROM.readUInt(address[i]);
        programs[program].luminance = EEPROM.readUInt(address[i]);
        programs[program].duration = EEPROM.readUShort(address[i]);
        programs[program].active = EEPROM.readBool(address[i]);
    }
}

void setMemory() {

    readMemory();

    if (programs[0].active == true) {
            EEPROM.put(20, true);
        }

    if (programs[0].hue != count1) {
        if (programs[0].active == true) {
            EEPROM.put(8, programs[0].hue);
        }
        else if (programs[1].active == true) {
            EEPROM.put(14, programs[1].hue);
        }
    }
    if (programs[0].saturation != count2) {
        if (programs[0].active == true) {
            EEPROM.put(10, programs[0].saturation);
        }
        if (programs[1].active == true) {
            EEPROM.put(16, count2);
        }
    }
    if (programs[0].luminance != count3) {
        if (programs[0].active == true) {
            EEPROM.put(12, count3);
        }
        if (programs[1].active == true) {
            EEPROM.put(17, count3);
        }
    }
    if (programs[0].duration != count4) {
        if (programs[0].active == true) {
            EEPROM.put(12, count4);
        }
        if (programs[1].active == true) {
            EEPROM.put(18, count4);
        }
    }
    EEPROM.commit();
}