void setMemory() {

    uint32_t savedBgColor = EEPROM.readULong(1);
    uint32_t savedKeyColor = EEPROM.readULong(2);

    uint16_t e1 = EEPROM.read(3);
    uint8_t e2 = EEPROM.read(4);
    uint8_t e3 = EEPROM.readUInt(5);
    float e4 = EEPROM.readFloat(6);

    if (e1 != count1) {
        EEPROM.write(3, count1);
        
        Serial.print("put count 1: ");
        Serial.print(EEPROM.readUShort(3));
        Serial.println("");
    }

    if (e2 != count2) {
        EEPROM.write(4, count2 & 0xFF);
        Serial.print("put count 2: ");
        Serial.print(EEPROM.readUInt(4));
        Serial.println("");
    }
    if (e3 != count3) {
        EEPROM.put(5, count3);
        Serial.print("put count 3: ");
        Serial.print(EEPROM.readUInt(5));
        Serial.println("");
    }
    if (e4 != count4) {
        EEPROM.put(6, count4);
        Serial.print("put count 4: ");
        Serial.print(EEPROM.readFloat(6));
        Serial.println("");
    }

}
void readMemory() {
    bgColor = EEPROM.readULong(1);
    keyColor = EEPROM.readULong(2);
}