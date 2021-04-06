#include "ciaAllocation.h"
#include <Wire.h>



void writeToI2C(struct CIADataStruct *CIAData) {


//Option 1: Adafruit Library Method

    //X-face commands 

    //posXlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(posXlead1Addr[1]; //Pin address (Register Address)
    CIAData->write(posXlead1[0]);
    CIAData->write(posXlead1[1]);
    CIAData->write(posXlead1[2];
    CIAData->write(posXlead1[3];
    CIAData->endTransmission();

    //posXlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(posXlead2Addr[1]; //Pin address (Register Address)
    CIAData->write(posXlead2[0]);
    CIAData->write(posXlead2[1]);
    CIAData->write(posXlead2[2];
    CIAData->write(posXlead2[3];
    CIAData->endTransmission();

    //negXlead1  
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(negXlead1Addr[1]; //Pin address (Register Address)
    CIAData->write(negXlead1[0]);
    CIAData->write(negXlead1[1]);
    CIAData->write(negXlead1[2];
    CIAData->write(negXlead1[3];
    CIAData->endTransmission();

    //negXlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(negXlead2Addr[1]; //Pin address (Register Address)
    CIAData->write(negXlead2[0]);
    CIAData->write(negXlead2[1]);
    CIAData->write(negXlead2[2];
    CIAData->write(negXlead2[3];
    CIAData->endTransmission();

    //Y-face commands   

    //posYlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(posYlead1Addr[1]; //Pin address (Register Address)
    CIAData->write(posYlead1[0]);
    CIAData->write(posYlead1[1]);
    CIAData->write(posYlead1[2];
    CIAData->write(posYlead1[3];
    CIAData->endTransmission();

    //posYlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(posYlead2Addr[1]; //Pin address (Register Address)
    CIAData->write(posYlead2Addr[0]);
    CIAData->write(posYlead2[1]);
    CIAData->write(posYlead2[2];
    CIAData->write(posYlead2[3];
    CIAData->endTransmission();

    //negYlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(negYlead1Addr[1]; //Pin address (Register Address)
    CIAData->write(negYlead1[0]);
    CIAData->write(negYlead1[1]);
    CIAData->write(negYlead1[2];
    CIAData->write(negYlead1[3];
    CIAData->endTransmission();

    //negYlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(negYlead2Addr[1]; //Pin address (Register Address)
    CIAData->write(negYlead2[0]);
    CIAData->write(negYlead2[1]);
    CIAData->write(negYlead2[2];
    CIAData->write(negYlead2[3];
    CIAData->endTransmission();

    //Z-face commands  

    //posZlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(posZlead1Addr[1]; //Pin address (Register Address)
    CIAData->write(posZlead1[0]);
    CIAData->write(posZlead1[1]);
    CIAData->write(posZlead1[2];
    CIAData->write(posZlead1[3];
    CIAData->endTransmission();
    
    //posZlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(posZlead2Addr[1]; //Pin address (Register Address)
    CIAData->write(posZlead2[0]);
    CIAData->write(posZlead2[1]);
    CIAData->write(posZlead2[2];
    CIAData->write(posZlead2[3];
    CIAData->endTransmission();
}

//Option 2: Write register address for every command. 

/*
OBC:  *reads acknowledge from chip*
      *sends* "posXlead1Addr[0]" (address for the first register of the first lead of the positive x face magnetorquer)
      *sends* "posXlead1[0]"     (command for the first register of the first lead of the positive x face magnetorquer)
      *sends* "posXlead1Addr[1]" (second register address)
      *sends* "posXlead1[1]"     (second register command)
      *sends* "posXlead1Addr[2]" (third register address)
      *sends* "posXlead1[2]"     (third register command)
      *sends* "posXlead1Addr[3]" (fourth register address)
      *sends* "posXlead1[3]"     (fourth register command)
*/ 