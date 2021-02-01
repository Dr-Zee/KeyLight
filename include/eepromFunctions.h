void readMemory(uint16_t count1, uint8_t count2, uint8_t count3, uint16_t count4) {
    if (program1.active == true) {
        count1 = EEPROM.readUShort(address[0]);
        count2 = EEPROM.readByte(address[1]);
        count3 = EEPROM.readByte(address[2]);
        count4 = EEPROM.readUShort(address[3]);
    }
    if (program2.active == true) {
        count1 = EEPROM.readUShort(address[4]);
        count2 = EEPROM.readByte(address[5]);
        count3 = EEPROM.readByte(address[6]);
        count4 = EEPROM.readUShort(address[7]);
    }
    if (program2.active == true) {
        count1 = EEPROM.readUShort(address[8]);
        count2 = EEPROM.readByte(address[9]);
        count3 = EEPROM.readByte(address[10]);
        count4 = EEPROM.readUShort(address[11]);
    }

}

void retrieveSettings() {

    program1.hue = EEPROM.readUShort(address[0]);
    program1.saturation = EEPROM.readUInt(address[1]);
    program1.luminance = EEPROM.readUInt(address[2]);
    program1.duration = EEPROM.readUShort(address[3]);
    program1.active = EEPROM.readBool(address[4]);

    program2.hue = EEPROM.readUShort(address[5]);
    program2.saturation = EEPROM.readUInt(address[6]);
    program2.luminance = EEPROM.readUInt(address[7]);
    program2.duration = EEPROM.readUShort(address[8]);
    program2.active = EEPROM.readBool(address[9]);

    program2.hue = EEPROM.readUShort(address[10]);
    program2.saturation = EEPROM.readUInt(address[11]);
    program2.luminance = EEPROM.readUInt(address[12]);
    program2.duration = EEPROM.readUShort(address[13]);
    program2.active = EEPROM.readBool(address[14]);
}

void setMemory() {

    readMemory();

    if (program1.active == true) {
            EEPROM.put(20, true);
        }

    if (program1.hue != count1) {
        if (program1.active == true) {
            EEPROM.put(8, program1.hue);
        }
        else if (program2.active == true) {
            EEPROM.put(14, program2.hue);
        }
    }
    if (e2 != count2) {
        if (program1.active == true) {
            EEPROM.put(10, program1.saturation);
        }
        if (program2.active == true) {
            EEPROM.put(16, count2);
        }
    }
    if (e3 != count3) {
        if (program1.active == true) {
            EEPROM.put(12, count3);
        }
        if (program2.active == true) {
            EEPROM.put(17, count3);
        }
    }
    if (e4 != count4) {
        if (program1.active == true) {
            EEPROM.put(12, count4);
        }
        if (program2.active == true) {
            EEPROM.put(18, count4);
        }
    }
    EEPROM.commit();
}