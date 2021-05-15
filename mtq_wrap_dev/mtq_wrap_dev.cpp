#include "mtq_wrap_dev.h"
#include <Wire.h>

void setMags(struct setMagsParameters *parameters, struct CIADataStruct *CIAData) {

    unsigned int i,j, firstMag;
    double command;
    bool posMagWorking, negMagWorking;
    struct allocationParameters posParam;
    struct allocationParameters negParam;
    unsigned char *posLead1[4], *posLead2[4], *negLead1[4], *negLead2[4];
    unsigned char dummyLead[4]; // dummy lead (for -z face that doesn't exist)

    // loops through x mags, y mags, and z mag
    for (i = 0; i < 3; ++i) {
        switch (i) {
            case 0: // x mags
                for (j = 0; j < 4; ++j) {
                    posLead1[j] = &CIAData->posXlead1[j];
                    posLead2[j] = &CIAData->posXlead2[j];
                    negLead1[j] = &CIAData->negXlead1[j];
                    negLead2[j] = &CIAData->negXlead2[j];
                }
                break;
            case 1: // y mags
                for (j = 0; j < 4; ++j) {
                    posLead1[j] = &CIAData->posYlead1[j];
                    posLead2[j] = &CIAData->posYlead2[j];
                    negLead1[j] = &CIAData->negYlead1[j];
                    negLead2[j] = &CIAData->negYlead2[j];
                }
                break;
            case 2: // z mags
                for (j = 0; j < 4; ++j) {
                    posLead1[j] = &CIAData->posZlead1[j];
                    posLead2[j] = &CIAData->posZlead2[j];
                    negLead1[j] = &dummyLead[j];
                    negLead2[j] = &dummyLead[j];
                }
                break;
        }

        firstMag = 2*i + 1;
        command = parameters->commands[i];
        posMagWorking = parameters->magStatus[2*i];

        // the case when configuring z axis MTQ
        if(i == 2) {
            negMagWorking = false;
        } else {
            negMagWorking = parameters->magStatus[2 * i + 1];
        }

        // if both mags are working
        if (posMagWorking && negMagWorking) {
            posParam.command = command/2;
            // differentiation for pos/neg MTQ is here. Taylor 11/13 4:48 #CIA, see Worklog MTQ
            // dipole data is flipped properly for the Negative MTQ
            negParam.command = -command/2;
            posParam.whichMag = firstMag;
            negParam.whichMag = firstMag + 1;
            allocation(&posParam, CIAData);
            allocation(&negParam, CIAData);

        // if positive mag works
        } else if (posMagWorking) {
            posParam.command = command;
            posParam.whichMag = firstMag;
            allocation(&posParam, CIAData);
            for (i = 0; i < 4; ++i) {
                *negLead1[i] = offLead[i];
                *negLead2[i] = offLead[i];
            }

        // if negative mag works
        } else if (negMagWorking) {
            // differentiation for pos/neg MTQ is here. Taylor 11/13 4:48 #CIA, see Worklog MTQ
            // dipole data is flipped properly for the Negative MTQ
            negParam.command = -command;
            negParam.whichMag = firstMag + 1;
            allocation(&negParam, CIAData);
            for (i = 0; i < 4; ++i) {
                *posLead1[i] = offLead[i];
                *posLead2[i] = offLead[i];
            }

        // if neither mag works
        } else {
            for (i = 0; i < 4; ++i) {
                *posLead1[i] = offLead[i];
                *posLead2[i] = offLead[i];
                *negLead1[i] = offLead[i];
                *negLead2[i] = offLead[i];
            }
        }
    }

    writeToI2C(CIAData);
}


void allocation(struct allocationParameters *parameters, struct CIADataStruct *CIAData) {

    double command = parameters->command;
    // convert command to duty cycle
    //float absDutyCycle = 0.4; // example duty cycle
    double absDutyCycle = command / maxMoment;

    if (absDutyCycle < 0) {
        absDutyCycle = -absDutyCycle;
    }

    // compute values for each lead
    char onLead[4];
    char lead1[4];
    char lead2[4];
    int i;

    // powered lead
    int delay = round(0);
    int onTime = round(absDutyCycle * cycleLength);
    onLead[0] = (char) (delay % separateBytes);
    onLead[1] = (char) (delay / separateBytes);

    int offStart = delay + onTime;
    onLead[2] = (char) (offStart % separateBytes);
    onLead[3] = (char) (offStart / separateBytes);

    // edge case for "all on" or "all off"
    if(onLead[3] >= 16) {
        onLead[1] = 16;
        onLead[3] = 0;
    } else if (onLead[2] == 0 && onLead[3] == 0) { 
        onLead[3] = 16;                        
    }

    // assign powered and non-powered leads based off command direction
    if (command >= 0.0) {
      for (i = 0; i < 4; ++i) {
        lead1[i] = onLead[i];
        lead2[i] = offLead[i];
      }
    } else {
      for (i = 0; i < 4; ++i) {
        lead1[i] = offLead[i];
        lead2[i] = onLead[i];
      }
    }

    // switch case for assigning to correct magnetorquer
    switch (parameters->whichMag)
    {
        case 1:
            for (i = 0; i < 4; ++i)
              CIAData->posXlead1[i] = lead1[i];

            for (i = 0; i < 4; ++i)
              CIAData->posXlead2[i] = lead2[i];
            break;
        case 2:
      for (i = 0; i < 4; ++i)
              CIAData->negXlead1[i] = lead1[i];

            for (i = 0; i < 4; ++i)
              CIAData->negXlead2[i] = lead2[i];
            break;
        case 3:
            for (i = 0; i < 4; ++i)
              CIAData->posYlead1[i] = lead1[i];

            for (i = 0; i < 4; ++i)
              CIAData->posYlead2[i] = lead2[i];
            break;
        case 4:
            for (i = 0; i < 4; ++i)
              CIAData->negYlead1[i] = lead1[i];

            for (i = 0; i < 4; ++i)
              CIAData->negYlead2[i] = lead2[i];
            break;
        case 5:
            for (i = 0; i < 4; ++i)
              CIAData->posZlead1[i] = lead1[i];

            for (i = 0; i < 4; ++i)
              CIAData->posZlead2[i] = lead2[i];
            break;
    }
}


void writeToI2C(struct CIADataStruct *CIAData) {

    //If this does not work try puting the Wire.endTransmission() inside the for loop
  
    //X-face commands 
    Wire.begin(DEV_ADDR_WRITE);

    //posXlead1
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->posXlead1Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->posXlead1[i]);
    }
    Wire.endTransmission();

    //posXlead2
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->posXlead2Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->posXlead2[i]);
    }
    Wire.endTransmission();

    //negXlead1  
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->negXlead1Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->negXlead1[i]);
    }
    Wire.endTransmission();

    //negXlead2
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->negXlead2Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->negXlead2[i]);
    }
    Wire.endTransmission();

    //Y-face commands   

    //posYlead1
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->posYlead1Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->posYlead1[i]);
    }
    Wire.endTransmission();

    //posYlead2
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->posYlead2Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->posYlead2[i]);
    }
    Wire.endTransmission();

    //negYlead1
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->negYlead1Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->negYlead1[i]);
    }
    Wire.endTransmission();

    //negYlead2
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->negYlead2Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->negYlead2[i]);
    }
    Wire.endTransmission();

    //Z-face commands  

    //posZlead1
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->posZlead1Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->posZlead1[i]);
    }
    Wire.endTransmission();
    
    //posZlead2
    Wire.beginTransmission(DEV_ADDR_WRITE); //I2C Address
    for (int i = 0; i < 4; i++) {
      Wire.write(CIAData->posZlead2Addr[i]); //Pin address (Register Address)
      Wire.write(CIAData->posZlead2[i]);
    }
    Wire.endTransmission();
}
