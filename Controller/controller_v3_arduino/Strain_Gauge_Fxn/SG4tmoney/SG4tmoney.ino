
#include <Arduino.h>
#include "HX711.h"
HX711 scale;

const int DOUT_PIN = 7;
const int SCK_PIN  = 6; 
float cal;
float V_int;


float C2 = .802;
float ve2 = 4.206;
float C1 = .809; 
float ve1 = 4.262;
float C3 = .795;
float ve3 = 4.171;


float C = C2; // chose based on the strain gauge you are testing
float ve = ve2;

float StrnGauge () {
  scale.set_gain(128);
  
  if (scale.is_ready()) {
    //pull raw 24 bit value
    float data = scale.read();
    // Serial.print("Raw reading: ");
    // Serial.println(data,4 );

  //convert to V0
    float v0 = (data*.02*(C)) / (8388607); //Digital to Volts
    // Serial.println (v0, 10);
    float del_v = v0 - V_int;
    
    // Serial.print("Del V:");
    // Serial.println(del_v, 8);

    //calc strain
    float del_e = ((4*del_v)/(2.1*ve));

    return del_e;

  } else {
    Serial.println("HX711 not found.");
    return -1;
  }
}

float StrnCal (){
  Serial.println("Calibrating... Please do not put any load on the specimine!");
  if (scale.is_ready()) {
    float cal = scale.read_average(); // zero point set
    V_int = (cal*.02*(C)) / (8388607);
    Serial.println(V_int,5);
  } else {
    Serial.println("HX711 error");
    while (1); 						// Code stop
  }
  return V_int;
}

void setup() {
  Serial.begin(115200);
  scale.begin(DOUT_PIN, SCK_PIN);
  delay(1000);
  V_int = StrnCal();

  Serial.print("Calibration V_int: ");
  Serial.println(V_int, 6);
}


void loop() {
    float strain = StrnGauge();
    float strain_p= strain * 1000000; 
    // Serial.print("Strain: ");
    Serial.println(strain_p, 10);

    delay(500);
}


