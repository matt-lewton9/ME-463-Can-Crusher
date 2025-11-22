
#include <Arduino.h>
#include "HX711.h"
HX711 scale;

const int DOUT_PIN = 9;
const int SCK_PIN  = 8; 

long StrnGauge (){
  scale.set_gain(128);
  
  if (scale.is_ready()) {
    //pull raw 24 bit value
    long data = scale.read();
    Serial.print("Raw reading: ");
    Serial.println(data);
      
    //convert to V0
    float CC=.802;
    float v0 = CC*data *.02/8388607; //Digital to Volts
    Serial.println (v0, 8);

    //calc strain
    const int C=0; //calibration constant
    long e_read = ((4*v0)/(2.1*5));
    long e_calibrated = e_read- C ;

    return e_calibrated;

  } else {
    Serial.println("HX711 not found.");
    return -1;
  }
}

void setup() {
  Serial.begin(57600);
  scale.begin(DOUT_PIN, SCK_PIN);
  delay (300);
}


void loop() {
    long strain = StrnGauge();
  
    Serial.print("Strain: ");
    Serial.println(strain);
    delay(3000);
}


