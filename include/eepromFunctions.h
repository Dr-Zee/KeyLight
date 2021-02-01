void readMemory(uint16_t count1, uint8_t count2, uint8_t count3, uint16_t count4) {
    if (program1.active == true) {
        count1 = EEPROM.readUShort(8);
        count2 = EEPROM.readByte(10);
        count3 = EEPROM.readByte(11);
        count4 = EEPROM.readUShort(12);
    }
    if (program2.active == true) {
        count1 = EEPROM.readUShort(14);
        count2 = EEPROM.readByte(16);
        count3 = EEPROM.readByte(17);
        count4 = EEPROM.readUShort(18);
    }
}

void retrieveSettings() {
    program1.hue = EEPROM.readUShort(8);
    program1.saturation = EEPROM.readUInt(10);
    program1.luminance = EEPROM.readUInt(11);
    program1.duration = EEPROM.readUShort(13);
    program1.active = EEPROM.readBool(19);

    program2.hue = EEPROM.readUShort(14);
    program2.saturation = EEPROM.readUInt(16);
    program2.luminance = EEPROM.readUInt(17);
    program2.duration = EEPROM.readUShort(18);
    program2.active = EEPROM.readBool(20);
}

void setMemory() {
    uint16_t e1 = 0;
    uint8_t e2 = 0;
    uint8_t e3 = 0;
    uint16_t e4 = 0;

    readMemory(e1, e2, e3, e4);

    if (program1.active == true) {
            EEPROM.put(20, true);
        }

    if (e1 != count1) {
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