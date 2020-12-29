void storeValues() 
{
    void EEPROMLoad() {
        EEPROM_readAnything(0, configuration);
        if (configuration.Saved != 111) {
            return;
        }
        SPZero = configuration.Setpoint;
        consKp = configuration.consKp;
        consKi = configuration.consKi;
        consKd = configuration.consKd;
        MinPower = configuration.MinPower;
    }

    void EEPROMSave() {
        configuration.Setpoint = SPZero;
        configuration.consKp = consKp;
        configuration.consKi = consKi;
        configuration.consKd = consKd;
        configuration.MinPower = MinPower;
        configuration.Saved = 111;
        EEPROM_writeAnything(0, configuration);
    }
}