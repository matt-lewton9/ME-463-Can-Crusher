#include <Wire.h>

// defs
#define LED_PIN 52
#define MUX_ADDR 0x70

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  // Setup serial
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Wire.begin();
}

void loop() {
  int32_t raw_pressure;

  if (1) {
    digitalWrite(LED_PIN, 1);

    mux_select(0);
    read_PT(&raw_pressure);
    Serial.print("PT1: " + String(raw_pressure,10) + "\n");

    mux_select(1);
    read_PT(&raw_pressure);
    Serial.print("PT2: " + String(raw_pressure,10) + "\n");

    mux_select(2);
    read_PT(&raw_pressure);
    Serial.print("PT3: " + String(raw_pressure,10) + "\n\n");

    digitalWrite(LED_PIN, 0);
  }
  delay(150);

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

void mux_select(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}