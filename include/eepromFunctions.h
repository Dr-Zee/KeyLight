
void writeValue() {
    float f = 123.456f;
    int eeAddress = 0;
    EEPROM.put(eeAddress, f);
    MyObject customVar = {
        3.14f,
        65,
        "Working!"
    };
    eeAddress += sizeof(float); //Move address to the next byte after float 'f'.
    EEPROM.put(eeAddress, customVar);
}