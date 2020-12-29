//get rotary encoder speed and control steps based on rotation speed
//step = 1 << (int(hue.speed / 10));


void storeValues() 
{

    template <class T> int EEPROM_writeAnything(int ee, const T& value)
    {
        const byte* p = (const byte*)(const void*)&value;
        unsigned int i;
        for (i = 0; i < sizeof(value); i++)
        EEPROM.write(ee++, *p++);
        return i;
    }

    template <class T> int EEPROM_readAnything(int ee, T& value)
    {
        byte* p = (byte*)(void*)&value;
        unsigned int i;
        for (i = 0; i < sizeof(value); i++)
        *p++ = EEPROM.read(ee++);
        return i;
    }

    struct config_t {
    double Setpoint;
    double consKp;
    double consKi;
    double consKd;
    int MinPower;
    byte Saved;
    } configuration;

    void EEPROMLoad() {
    EEPROM_readAnything(0, configuration);
    if (configuration.Saved != 111)return;
    SPZero = configuration.Setpoint;
    consKp = configuration.consKp;
    consKi = configuration.consKi;
    consKd = configuration.consKd;
    MinPower = configuration.MinPower;
    // Setpoint = 0.00;
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