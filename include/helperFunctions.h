int64_t timeKeeper(int64_t timer) {
    return esp_timer_get_time() - timer;
}

uint16_t encoderConvert(uint16_t count, int i) {

    if (i == 0) {
        count = (count / 2) * 200;
    }
    else if ((i == 1) || (i == 2)) {

        uint16_t converted = (count / 2) * 5;

        if(converted > 255) {
            count = 0;
        }
        if (converted < 0) {
            count = 255;
        }

    } 
    else if (i == 3) {
        count = (count / 2) * 500;
    }
    return count;
}

int getActiveProgram() {
    int p = 0;
    for (int i = 0; i < 4; i++) {
        if (programs[i].active == true) {
            p = i;
        }
    }
    return p;
}

void setActiveProgram(byte button) {
    for (int i = 0; i < 4; i++) {
        if (i == button) {
            programs[i].active = true;
        } else {
            programs[i].active = false;
        }
    }
}
