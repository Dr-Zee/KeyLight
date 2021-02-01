void setMemory() {
    uint16_t e1 = 0;
    uint16_t e2 = 0;
    uint16_t e3 = 0;
    uint16_t e4 = 0;

    if (prg[0] == true) {
        e1 = EEPROM.readUShort(8);
        e2 = EEPROM.readByte(10);
        e3 = EEPROM.readByte(11);
        e4 = EEPROM.readUShort(12);
    }
    if(prg[1] == true) {
        e1 = EEPROM.readUShort(14);
        e2 = EEPROM.readByte(16);
        e3 = EEPROM.readByte(17);
        e4 = EEPROM.readUShort(18);
    }

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
        if (prg[2] == true) {
            //EEPROM.put(10, count2);
        }
        else if (prg[3] == true) {
            //EEPROM.put(16, count2);
        }
    }
    if (e3 != count3) {
        if (prg[0] == true) {
            EEPROM.put(12, count4);
        }
        if (prg[1] == true) {
            EEPROM.put(17, count3);
        }
        if (prg[4] == true) {
           // EEPROM.put(11, count3);
        }
        else if (prg[5] == true) {
            // EEPROM.put(17, count3);
        }
    }
    if (e4 != count4) {
        if (prg[0] == true) {
            EEPROM.put(12, count4);
        }
        if (prg[6] == true) {
            EEPROM.put(12, count4);
        }
        else if (prg[7] == true) {
            EEPROM.put(18, count4);
        }
    }
    EEPROM.commit();
}

void readMemory() {
    if (prg[0] == true) {
        bgColor = EEPROM.readULong(0);
        keyColor = EEPROM.readULong(4);
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