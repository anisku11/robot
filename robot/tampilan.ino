void baca() {
  //setting sound
  sensor = analogRead(sound);

  //setting button
//  buttonState = digitalRead(button);

  //setting api
  kondisi1 = digitalRead(api1);
  kondisi2 = digitalRead(api2);
  kondisi3 = digitalRead(api3);
  kondisi4 = digitalRead(api4);
  kondisi5 = digitalRead(api5);

  //setting garis
  gris1 = analogRead(garis1);
  gris2 = analogRead(garis2);

}

void tampil() {
//  //sensor 5
//  digitalWrite(trig_pin4, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trig_pin4, HIGH);
//  delayMicroseconds(20);
//  digitalWrite(trig_pin4, LOW);
//  pulse4 = pulseIn(echo_pin4, HIGH);
//  cm4 = pulse4 / 58.138;
  //set cursor tampilan flame
  lcd.setCursor(0, 1);
  lcd.print(kondisi1);
  lcd.setCursor(3, 1);
  lcd.print(kondisi2);
  lcd.setCursor(6, 1);
  lcd.print(kondisi3);
  lcd.setCursor(9, 1);
  lcd.print(kondisi4);
  lcd.setCursor(12, 1);
  lcd.print(kondisi5);

  delay(100);
  lcd.clear();
}

void loopingan() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through all the sensors.
    if (millis() >= pingTimer[i]) {         // Is it this sensor's time to ping?
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;  // Set next time this sensor will be pinged.
      if (i == 0 && currentSensor == SONAR_NUM - 1) oneSensorCycle(); // Sensor ping cycle complete, do something with the results.
      sonar[currentSensor].timer_stop();          // Make sure previous timer is canceled before starting a new ping (insurance).
      currentSensor = i;                          // Sensor being accessed.
      cm[currentSensor] = 0;                      // Make distance zero in case there's no ping echo for this sensor.
      sonar[currentSensor].ping_timer(echoCheck); // Do the ping (processing continues, interrupt will call echoCheck to look for echo).
    }
  }
  // Other code that *DOESN'T* analyze ping results can go here.
}

void echoCheck() { // If ping received, set the sensor distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}

void oneSensorCycle() { // Sensor ping cycle complete, do something with the results.
  // The following code would be replaced with your code that does something with the ping results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");

    //print di LCD
    lcd.setCursor(0, 0);
    lcd.print(cm[i]);
  }
  Serial.println();
}
