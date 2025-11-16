// NOTE, DID NOT TEST ENABLE / DISABLE FOR STEPPER, BUT SHOULD BE EASY. NEED TO READ DATASHEET, THEN WIRE ENABLE PIN TO DIGITAL

// Define pin connections & motor's steps per revolution
const int stp1 = 53;
const int dir1 = 52;

const int stp2 = 51;
const int dir2 = 50;

const int stp3 = 49;
const int dir3 = 48;

const int stepsPerRevolution = 200;

const int STEPS_ALL =  200; // steps for 1 launcher rotation, 1/2 for half launcher rotaion
unsigned long SPEED_ALL = 20; // ms, delay "Speed" for launcher conveyor

void setup()
{
  // Declare pins as Outputs
  pinMode(stp1, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(stp2, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(stp3, OUTPUT);
  pinMode(dir3, OUTPUT);

  
}
void loop() // test loop to load and drop balls
{
  
  stepper(0, STEPS_ALL, stp1, dir1, SPEED_ALL);
  stepper(0, STEPS_ALL, stp2, dir2, SPEED_ALL);
  stepper(0, STEPS_ALL, stp3, dir3, SPEED_ALL);

  delay(1000);
 
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
