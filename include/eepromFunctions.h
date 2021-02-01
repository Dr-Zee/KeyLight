void readMemory(uint16_t count1, uint8_t count2, uint8_t count3, uint16_t count4) {
    if (prg[0] == true) {
        count1 = EEPROM.readUShort(8);
        count2 = EEPROM.readByte(10);
        count3 = EEPROM.readByte(11);
        count4 = EEPROM.readUShort(12);
    }
    if (prg[1] == true) {
        count1 = EEPROM.readUShort(14);
        count2 = EEPROM.readByte(16);
        count3 = EEPROM.readByte(17);
        count4 = EEPROM.readUShort(18);
    }
}

void setMemory() {
    uint16_t e1 = 0;
    uint8_t e2 = 0;
    uint8_t e3 = 0;
    uint16_t e4 = 0;

    readMemory(e1, e2, e3, e4);

    if (e1 != count1) {
        if (prg[0] == true) {
            EEPROM.put(8, count1);
        }
        else if (prg[1] == true) {
            EEPROM.put(14, count1);
        }
    }
    if (e2 != count2) {
        if (prg[0] == true) {
            EEPROM.put(10, count2);
        }
        if (prg[1] == true) {
            EEPROM.put(16, count2);
        }
    }
    if (e3 != count3) {
        if (prg[0] == true) {
            EEPROM.put(12, count3);
        }
        if (prg[1] == true) {
            EEPROM.put(17, count3);
        }
    }
    if (e4 != count4) {
        if (prg[0] == true) {
            EEPROM.put(12, count4);
        }
        if (prg[1] == true) {
            EEPROM.put(18, count4);
        }
    }
    EEPROM.commit();
}