void eepromRead(uint16_t addr, void* output, uint16_t length) {
    uint8_t* src; 
    uint8_t* dst;
    src = (uint8_t*)addr;
    dst = (uint8_t*)output;
    for (uint16_t i = 0; i < length; i++) {
        *dst++ = eeprom_read_byte(src++);
    }
}

void eepromWrite(uint16_t addr, void* input, uint16_t length) {
    uint8_t* src; 
    uint8_t* dst;
    src = (uint8_t*)input;
    dst = (uint8_t*)addr;
    for (uint16_t i = 0; i < length; i++) {
        eeprom_write_byte(dst++, *src++);
    }
}

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