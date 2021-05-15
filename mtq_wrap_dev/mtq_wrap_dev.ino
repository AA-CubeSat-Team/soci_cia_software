#include "mtq_wrap_dev.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>

//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47);
void setMags(struct setMagsParameters *parameters, struct CIADataStruct *CIAData); 

//struct setMagsParameters parameters1;
//struct CIADataStruct CIAdata;

// setMagsParameters takes three double commands and five boolean operational status
// CIADataStruct takes four commands for each lead
// Have to define inputs for these in this script because it is not in setMags

void setup() {
  Serial.begin(9600);
  Serial.println("MTQ Test");
//
}

//setMags calls allocation.c and writeToI2C.c
/*
void loop() {
  
    // Provide values for setMags and CIAData
  for (int i=0; i<3; i++) {
    parameters1->commands[i]= {0.0,1.0,2.0}; //Not sure what to set these to (Wants a double)
  }
  for (int i=0; i<5; i++) {
    paramaters1->magStatus[i]={0.0,1.0,2.0,3.0,4.0,5.0}; //Also not sure what to set this to (Wants a boolean)
  }


  for (int i=0; i<4; i++){ //Specify four char commands for each lead
  // Positive x-face commands
    CIAData->posXlead1[i]= {0,1,2,3};
    CIAData->posXlead2[i]= {0,1,2,3};

    // negative x-face commands
    CIAData->negXlead1[i]= {0,1,2,3};
    CIAData->negXlead2[i]= {0,1,2,3};

    // positive y-face commands
    CIAData->posYlead1[i]= {0,1,2,3};
    CIAData->posYlead2[i]= {0,1,2,3};

    // negative y-face commands
    CIADatavnegYlead1[i]= {0,1,2,3};
    CIAData->negYlead2[i]= {0,1,2,3};

    // positive z-face commands
    CIAData->posZlead1[i]= {0,1,2,3};
    CIAData->posZlead2[i]= {0,1,2,3};
  }

  setMags(&parameters1, &CIAData);

  

    
  delay(1000);
}
*/
