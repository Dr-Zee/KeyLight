void retrieveMemory() 
{
    // Program 1 values
    program[0].val[0] = EEPROM.readUShort(address[0]);
    program[0].val[1] = EEPROM.readUShort(address[1]);
    program[0].val[2] = EEPROM.readUShort(address[2]);
    program[0].val[3] = EEPROM.readUShort(address[3]);

    //Program 2 values
    program[1].val[0] = EEPROM.readUShort(address[4]);
    program[1].val[1] = EEPROM.readUShort(address[5]);
    program[1].val[2] = EEPROM.readUShort(address[6]);
    program[1].val[3] = EEPROM.readUShort(address[7]);

    //  Program 3 values
    // program[2].val[0] = EEPROM.readUShort(address[8]);
    // program[2].val[1] = EEPROM.readUShort(address[9]);
    // program[2].val[2] = EEPROM.readUShort(address[10]);
    // program[2].val[3] = EEPROM.readUShort(address[11]);

    // //Program 4 values
    // program[3].val[0] = EEPROM.readUShort(address[12]);
    // program[3].val[1] = EEPROM.readUShort(address[13]);
    // program[3].val[2] = EEPROM.readUShort(address[14]);
    // program[3].val[3] = EEPROM.readUShort(address[15]);
}

void setMemory() 
{
    // If the saved and current values are different, save the new value.
    // Program 1
    if (program[0].val[0] != EEPROM.readUShort(address[0]))   { EEPROM.put(address[0], program[0].val[0]); }
    if (program[0].val[1] != EEPROM.readUShort(address[1]))   { EEPROM.put(address[1], program[0].val[1]); }
    if (program[0].val[2] != EEPROM.readUShort(address[2]))   { EEPROM.put(address[2], program[0].val[2]); }
    if (program[0].val[3] != EEPROM.readUShort(address[3]))   { EEPROM.put(address[3], program[0].val[3]); }

    // Program 2
    if (program[1].val[0] != EEPROM.readUShort(address[4]))   { EEPROM.put(address[4], program[1].val[0]); }
    if (program[1].val[1] != EEPROM.readUShort(address[5]))   { EEPROM.put(address[5], program[1].val[1]); }
    if (program[1].val[2] != EEPROM.readUShort(address[6]))   { EEPROM.put(address[6], program[1].val[2]); }
    if (program[1].val[3] != EEPROM.readUShort(address[7]))   { EEPROM.put(address[7], program[1].val[3]); }

    // Program 3
    // if (program[2].val[0] != EEPROM.readUShort(address[8]))   { EEPROM.put(address[8], program[2].val[0]); }
    // if (program[2].val[1] != EEPROM.readUShort(address[9]))   { EEPROM.put(address[9], program[2].val[1]); }
    // if (program[2].val[2] != EEPROM.readUShort(address[10]))  { EEPROM.put(address[10], program[2].val[2]); }
    // if (program[2].val[3] != EEPROM.readUShort(address[11]))  { EEPROM.put(address[11], program[2].val[3]); }

    // Program 4
    // if (program[3].val[0] != EEPROM.readUShort(address[12]))  { EEPROM.put(address[12], program[3].val[0]); }
    // if (program[3].val[1] != EEPROM.readUShort(address[13]))  { EEPROM.put(address[13], program[3].val[1]); }
    // if (program[3].val[2] != EEPROM.readUShort(address[14]))  { EEPROM.put(address[14], program[3].val[2]); }
    // if (program[3].val[3] != EEPROM.readUShort(address[15]))  { EEPROM.put(address[15], program[3].val[3]); }

    EEPROM.commit();
}