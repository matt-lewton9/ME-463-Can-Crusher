// Libraries
#include <Wire.h>

// Pressure Transducers
#define MUX_ADDR 0x70
#define PT_ADDR 0x6D

// Strain Gauges
#define SG1_SCK
#define SG1_DATA
#define SG2_SCK
#define SG2_DATA
#define SG3_SCK
#define SG3_DATA

// Steper Motors
#define M1_IN1
#define M1_IN2
#define M1_IN3
#define M1_IN4
#define M2_IN1
#define M2_IN2
#define M2_IN3
#define M2_IN4
#define M3_IN1
#define M3_IN2
#define M3_IN3
#define M3_IN4

// Serial
#define BAUD 115200


// vars
uint8_t cmd = 0;

void setup() {
  // Setup serial
  Serial.begin(BAUD);
  while (!Serial);

  // Setup I2C
  Wire.begin();
}

void loop() {
  int32_t raw_pressure;
  cmd = Serial.read();
  if (cmd ==49) {
    // send response
    Serial.write(0x01);

    // read sensors, print 
    mux_select(0);
    read_pt(&raw_pressure);
    Serial.print(String(raw_pressure,10) + "\n");

    mux_select(1);
    read_pt(&raw_pressure);
    Serial.print(String(raw_pressure,10) + "\n");

    mux_select(2);
    read_pt(&raw_pressure);
    Serial.print(String(raw_pressure,10) + "\n\n");
  }
}

uint8_t read_pt(int32_t *raw_pressure) {
  // variables
  uint8_t pressure_H;
  uint8_t pressure_M;
  uint8_t pressure_L;
  int32_t pressure_adc;

  // tell sensor to read pressure and temp
  Wire.beginTransmission(PT_ADDR);
  Wire.write(0x30);
  Wire.write(0x0A);
  Wire.endTransmission();

  // read values from pressure sensor
  Wire.beginTransmission(PT_ADDR);
  Wire.write(0x06);
  Wire.endTransmission();


  Wire.requestFrom(PT_ADDR, 3);
  pressure_H = Wire.read();
  pressure_M = Wire.read();
  pressure_L = Wire.read();

  pressure_adc = ((uint32_t)pressure_H << 8) + (uint32_t) pressure_M;
  pressure_adc = (pressure_adc << 8) + (uint32_t) pressure_L;
  *raw_pressure = ((pressure_adc << 8) >> 8);
}

void mux_select(uint8_t i) {
  // select device i from multiplexer
  if (i > 7) return;
 
  Wire.beginTransmission(MUX_ADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}