// CUSTOMER INPUTS





// State Constants
const int STAGE_1 = 101; // START
const int STAGE_2 = 102; // MOVE TO TGT PRESSURE
const int STAGE_2 = 103; // HOLD
const int STAGE_3 = 104; // STOP

// Input Pins
const int PT1 = ;
const int PT2 = ;
const int PT3 = ;

// Output Pins
const int STEP1 = ;
const int STEP2 = ;
const int STEP3 = ;

// INPUT VARIABLES
int TP = 0; // OUTSIDE TARGET PRESSURE?
int SP = 0; // OUTSIDE SAFE PRESSURE?
int HD = 0; // HOLD?
int ST = 0; // START?

// OUTPUT VARIABLES
int STP = 0; // STEP TOWARDS TARGET
int CYL = 0; // CYCLE TO NEXT TARGET

int state = STAGE_1; //Initate home state

void setup() {
  // Set input pins
  pinMode(PT1, INPUT);
  pinMode(PT2, INPUT);
  pinMode(PT3, INPUT);

  // Set output Pins
  pinMode(STEP1, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(STEP3, OUTPUT);

  // Start serial port
  Serial.begin(9600);

  // Wait for serial port to be established
  delay(100);

}

void loop() {
  
  // read inputs

  //CALCULATE PT CRITERIA
  if(//in target range){
    PT == 0;
    SP == 0;
  }
  else if(//outside target but in safe){
    PT == 1;
    SP == 0;
  }
  else{
    PT == 1;
    SP == 1;
  }


  //CHECK HOLD CRITERIA, SET HD

  //CHECK START CRITERIA, SET ST



  switch (state){

  case STAGE_1: //START

    if(SP == 1){
      state = STAGE4;
    }
    else if(ST == 0){
      state = STAGE1;
    }
    else if (TP ==1 && HD == 0){
      state = STAGE2;
    }
    else{
     state = STAGE3;
    }

      STP = 0;
      CYL = 0;
      break;

  case STAGE_2: //MOVE TO TGT
     if(SP == 1){
      state = STAGE4;
    }
    else if(HD == 1 || TP == 0){
      state = STAGE3;
    }
    else{
      state = STAGE2;
    }

      // Write state outputs
      STP = 1;
      CYL = 0;
      break;

  case STAGE_3: //HOLD

      if(SP == 1){
            state = STAGE4;
      }
      else if(HD == 0){
        state = STAGE2;
      }
      else{
        state = STAGE3;
      }
  
      // Write state outputs
      STP = 0;
      CYL = 1;
      break;

  case STAGE_4: //STOP

    state = STAGE4;
  
      // Write state outputs
      STP = 0;
      CYL = 0;
      break;
  }

  // Write outputs
  if (STP == 1) { 
    stepper(STEP1, xx, xx);
    stepper(STEP2, xx, xx);
    stepper(STEP3, xx, xx);
  }

  if (CYL == 1) { 
    TARGET_PRESS = XX;
  }


}
