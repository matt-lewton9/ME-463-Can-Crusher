#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(52, OUTPUT);
  // Setup serial
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Wire.begin();
}

void loop() {
  int32_t raw_pressure;

  if (Serial.read() == (char) 49) {
    digitalWrite(52, 1);
    read_PT(&raw_pressure);
    Serial.print(String(raw_pressure,10) + "\n");
    digitalWrite(52, 0);
  }

}

int read_PT(int32_t *raw_pressure) {
  // variables
  uint8_t pressure_H;
  uint8_t pressure_M;
  uint8_t pressure_L;
  int32_t pressure_adc;

  // tell sensor to read pressure and temp
  Wire.beginTransmission(0x6D);
  Wire.write(0x30);
  Wire.write(0x0A);
  Wire.endTransmission();

  // read values from pressure sensor
  Wire.beginTransmission(0x6D);
  Wire.write(0x06);
  Wire.endTransmission();


  Wire.requestFrom(0x6D, 3);
  pressure_H = Wire.read();
  pressure_M = Wire.read();
  pressure_L = Wire.read();

  //Serial.print(String(pressure_H) + ", ");
  //Serial.print(String(pressure_M) + ", ");
  //Serial.print(String(pressure_L) + " ");

  pressure_adc = ((uint32_t)pressure_H << 8) + (uint32_t) pressure_M;
  pressure_adc = (pressure_adc << 8) + (uint32_t) pressure_L;
  *raw_pressure = ((pressure_adc << 8) >> 8);
  //*pressure_PSI = raw_pressure / 8 * 0.0001450377;
  //Serial.print(String(raw_pressure) + "\n");
}

// void send_int32(int32_t data)