// NOTE, DID NOT TEST ENABLE / DISABLE FOR STEPPER, BUT SHOULD BE EASY. NEED TO READ DATASHEET, THEN WIRE ENABLE PIN TO DIGITAL

// Define pin connections & motor's steps per revolution
const int dirPin_S = 2;
const int stepPin_S = 3;

const int dirPin_L = 4;
const int stepPin_L = 5;

const int dirPin_UP = 6;
const int stepPin_UP = 7;


const int stepsPerRevolution = 200;

const int STEPS_L =  2*89; // steps for 1 launcher rotation, 1/2 for half launcher rotaion
unsigned long SPEED_L = 1; // ms, delay "Speed" for launcher conveyor
const int STEPS_S =  25;
unsigned long SPEED_S =20; // ms , delay "Speed" for storage 
const int STEPS_UP =  72; //was 100 incorrectly
unsigned long SPEED_UP = 7; // ms , delay "Speed" for launcher lift


void setup()
{
  // Declare pins as Outputs
  pinMode(stepPin_L, OUTPUT);
  pinMode(dirPin_L, OUTPUT);
  
  pinMode(stepPin_S, OUTPUT);
  pinMode(dirPin_S, OUTPUT);

  pinMode(stepPin_UP, OUTPUT);
  pinMode(dirPin_UP, OUTPUT);

  stepper(0, STEPS_UP, stepPin_UP, dirPin_UP, SPEED_UP); // UP LAUNCHER

  
}
void loop() // test loop to load and drop balls
{
  
  stepper(0, STEPS_L, stepPin_L, dirPin_L, SPEED_L); // LAUNCHER

  delay(500);

  stepper(1, STEPS_S, stepPin_S, dirPin_S, SPEED_S); // STORAGE

 
 delay(500); // Wait 2 seconds  TESTING ONLY

}

int stepper(int dir, int steps, int step_pin, int dir_pin, int spd_dly){

  digitalWrite(dir_pin, dir);   // Set motor direction 

  unsigned long t_0 = millis(); // get init time
  int step_out = LOW; // start with stepper LOW
  int step_ct = 0; // couting + of steps taken
  
  while(step_ct <= 2*steps)
  {
    if (millis() >= (t_0 + spd_dly))
    {   
      step_out = !step_out; //switch stepper ON or OFF
      digitalWrite(step_pin, step_out); //write output to stepper
  
      step_ct++; //incriment step ct
      t_0 = millis(); //reset timer;

     }
  }
}
