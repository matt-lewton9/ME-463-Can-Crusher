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
#define M1_DIR
#define M1_PUL
#define M2_DIR
#define M2_PUL
#define M3_DIR
#define M3_PUL

// Serial
#define BAUD 115200


// vars
char cmd = 0;
int32_t PT1_raw;
int32_t PT2_raw;
int32_t PT3_raw;



// Setup
void setup() {
  // Setup serial
  Serial.begin(BAUD);
  while (!Serial);

  // Setup I2C
  Wire.begin();
}

// Loop
void loop() {

  // read in command from matlab
  cmd = Serial.read();

  if (cmd == "1") { // read sensors
    // send ack
    Serial.write("1");

    // read sensors, print 
    mux_select(0);
    read_pt(&PT1_raw);
    Serial.print(String(PT1_raw,10) + "\n");

    mux_select(1);
    read_pt(&PT2_raw);
    Serial.print(String(PT2_raw,10) + "\n");

    mux_select(2);
    read_pt(&PT3_raw);
    Serial.print(String(PT3_raw,10) + "\n");
  }
  if (cmd == "2") { // recive motor commands
    // send ack
    Serial.write("2")

    // recive motor commands
  }
}

void drive_stepper(int8_t M1_steps, int8_t M2_steps, int8_t M3_steps) {
  digitalWrite(M1_PUL, HIGH);
  delayMicroseconds(500);
  digitalWrite(M1_PUL, LOW);
  delayMicroseconds(500);
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