int64_t timeKeeper(int64_t timer) {
    return esp_timer_get_time() - timer;
}

uint16_t encoderConvert(uint16_t encoderCount, int i) {
     Serial.print("Raw count: ");
    Serial.print(encoderCount);
    Serial.println("");

    if (i == 0) {
        encoderCount = (encoderCount / 2) * 200;
    }
    if ((i == 1) || (i == 2)) {
        encoderCount = (encoderCount / 2) * 5;
      
        //uint16_t converted = (count / 2) * 5;
        if (encoderCount > 255) {
            count[i].encoder.setCount(5);
            count[i].oldCount = count[i].count = 5;
        }
        if (encoderCount < 1) {
            count[i].encoder.setCount(255);
            count[i].oldCount = count[i].count = 255;
        }
    } 
    if (i == 3) {
        encoderCount = (encoderCount / 2) * 200;
    }
    Serial.print("Returned count: ");
    Serial.print(encoderCount);
    Serial.println("");
    return encoderCount;
}