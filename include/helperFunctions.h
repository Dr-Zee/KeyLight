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