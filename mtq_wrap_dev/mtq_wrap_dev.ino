#include "mtq_wrap_dev.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Wire.h>
//#include <Adafruit_PWMServoDriver.h>

//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x47);
unsigned char CommandsInputs[3], MagStatusInputs[5]; //Inputs

// Possible Input Values: 
//CommandsInputs[3]={0.0,1.0,2.0};
//MagStatusInputs[5]={0.0,1.0,2.0,3.0,4.0,5.0};
//LeadInputs[4]={0,1,2,3}; (Ignore LeadInputs, SetMags already takes care of this)

// setMagsParameters takes three double commands and five boolean operational status
// CIAdataStruct takes four commands for each lead
// Have to define inputs for these in this script because it is not in setMags

static struct setMagsParameters parameters1;
static struct CIADataStruct CIAdata;




void setup() {
  Serial.begin(9600);
  Serial.println("MTQ Test");
  
//
}

//setMags calls allocation.c and writeToI2C.c

void loop() {
  
    // Provide values for setMags and CIAdata
  for (int i=0; i<3; i++) {
    parameters1.commands[i]= CommandsInputs[i]; //Not sure what to set these to (Wants a double)
  }
  for (int i=0; i<5; i++) {
    parameters1.magStatus[i]= MagStatusInputs[i]; //Also not sure what to set this to (Wants a boolean)
  }


//  for (int i=0; i<4; i++){ //Specify four char commands for each lead
//  // Positive x-face commands
//    CIAdata.posXlead1[i]= LeadInputs[i];
//    CIAdata.posXlead2[i]= LeadInputs[i];
//
//    // negative x-face commands
//    CIAdata.negXlead1[i]= LeadInputs[i];
//    CIAdata.negXlead2[i]= LeadInputs[i];
//
//    // positive y-face commands
//    CIAdata.posYlead1[i]= LeadInputs[i];
//    CIAdata.posYlead2[i]= LeadInputs[i];
//
//    // negative y-face commands
//    CIAdata.negYlead1[i]= LeadInputs[i];
//    CIAdata.negYlead2[i]= LeadInputs[i];
//
//    // positive z-face commands
//    CIAdata.posZlead1[i]= LeadInputs[i];
//    CIAdata.posZlead2[i]= LeadInputs[i];
//  }

  setMags(&parameters1, &CIAdata);

  

    
  delay(1000);
}
