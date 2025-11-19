// Libraries
#include <Wire.h>
#include <math.h>

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
#define M1_DIR 52
#define M1_PUL 53
#define M2_DIR 48
#define M2_PUL 49
#define M3_DIR 44
#define M3_PUL 45

// Serial
#define BAUD 115200


// vars
uint8_t cmd = 0; // command from matlab
int32_t PT1_raw = 0;
int32_t PT2_raw = 0;
int32_t PT3_raw = 0;



// Setup
void setup() {
  // Setup serial
  Serial.begin(BAUD);
  while (!Serial);

  // Setup I2C
  Wire.begin();

  // Setup motor pins
  pinMode(M1_DIR, OUTPUT);
  pinMode(M1_PUL, OUTPUT);
  digitalWrite(M1_DIR, LOW);
  pinMode(M2_DIR, OUTPUT);
  pinMode(M2_PUL, OUTPUT);
  digitalWrite(M2_DIR, LOW);
}

// Loop
void loop() {

  // read in command from matlab
  cmd = Serial.read();

  if (cmd == 49) { // read sensors
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
  if (cmd == 50) { // recive motor commands
    // send ack
    Serial.write("2");

    // read motor commands
    while (Serial.available() < 6);
    int m1_dir = Serial.read();
    int m1_steps = Serial.read();
    int m2_dir = Serial.read();
    int m2_steps = Serial.read();
    int m3_dir = Serial.read();
    int m3_steps = Serial.read();
    // drive steppers
    drive_stepper(m1_dir, m1_steps, m2_dir, m2_steps, m3_dir, m3_steps);
  }
}

void drive_stepper(int M1_dir, int M1_steps, int M2_dir, int M2_steps, int M3_dir, int M3_steps) {

  int max_steps = fmax(fmax(M1_steps, M2_steps), M3_steps);
  digitalWrite(M1_DIR, M1_dir);
  digitalWrite(M2_DIR, M2_dir);
  digitalWrite(M3_DIR, M3_dir);

  for (int step = 0; step < max_steps; step++) {
    // digitalWrite(M1_PUL, HIGH);
    // delayMicroseconds(500);
    // digitalWrite(M1_PUL, LOW);
    // delayMicroseconds(500);
    if (M1_steps > step) {
      digitalWrite(M1_PUL, HIGH);
    }
    if (M2_steps > step) {
      digitalWrite(M2_PUL, HIGH);
    }
    if (M3_steps > step) {
      digitalWrite(M3_PUL, HIGH);
    }  
    delayMicroseconds(500);
    if (M1_steps > step) {
      digitalWrite(M1_PUL, LOW);
    }
    if (M2_steps > step) {
      digitalWrite(M2_PUL, LOW);
    }
    if (M3_steps > step) {
      digitalWrite(M3_PUL, LOW);
    }
    delayMicroseconds(500);
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

void single_step(int pin_pul, int delay_ms) {
    digitalWrite(pin_pul, HIGH);
    delayMicroseconds(delay);
    digitalWrite(pin_pul, LOW);
    delayMicroseconds(delay);
}