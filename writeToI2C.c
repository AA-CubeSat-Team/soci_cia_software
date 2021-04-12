#include "ciaAllocation.h"
#include <Wire.h>



void writeToI2C(struct CIADataStruct *CIAData) {


//Option 1: Adafruit Library Method

    //X-face commands 

    //posXlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    for (int i = 0; i < 4; i++) {
        CIAData->write(posXlead1Addr[i]; //Pin address (Register Address)
        CIAData->write(posXlead1[i]);
    }
    CIAData->endTransmission();

    //posXlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
        for (int i = 0; i < 4; i++) {
        CIAData->write(posXlead2Addr[i]; //Pin address (Register Address)
        CIAData->write(posXlead2[i]);
    }
    CIAData->endTransmission();

    //negXlead1  
    CIAData->beginTransmission(devAddrWrite); //I2C Address
        for (int i = 0; i < 4; i++) {
        CIAData->write(negXlead1Addr[i]; //Pin address (Register Address)
        CIAData->write(negXlead1[i]);
    }
    CIAData->endTransmission();

    //negXlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
        for (int i = 0; i < 4; i++) {
        CIAData->write(negXlead2Addr[i]; //Pin address (Register Address)
        CIAData->write(negXlead2[i]);
    }
    CIAData->endTransmission();

    //Y-face commands   

    //posYlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
            for (int i = 0; i < 4; i++) {
        CIAData->write(posYlead1Addr[i]; //Pin address (Register Address)
        CIAData->write(posYlead1[i]);
    }
    CIAData->endTransmission();

    //posYlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
            for (int i = 0; i < 4; i++) {
        CIAData->write(posYlead2Addr[i]; //Pin address (Register Address)
        CIAData->write(posYlead2[i]);
    }
    CIAData->endTransmission();

    //negYlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
                for (int i = 0; i < 4; i++) {
        CIAData->write(negYlead1Addr[i]; //Pin address (Register Address)
        CIAData->write(negYlead1[i]);
    }
    CIAData->endTransmission();

    //negYlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
                for (int i = 0; i < 4; i++) {
        CIAData->write(negYlead2Addr[i]; //Pin address (Register Address)
        CIAData->write(negYlead2[i]);
    }
    CIAData->endTransmission();

    //Z-face commands  

    //posZlead1
    CIAData->beginTransmission(devAddrWrite); //I2C Address
    CIAData->write(posZlead1Addr[1]; //Pin address (Register Address)
                for (int i = 0; i < 4; i++) {
        CIAData->write(posZlead1Addr[i]; //Pin address (Register Address)
        CIAData->write(posZlead1[i]);
    }
    CIAData->endTransmission();
    
    //posZlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
                for (int i = 0; i < 4; i++) {
        CIAData->write(posZlead2Addr[i]; //Pin address (Register Address)
        CIAData->write(posZlead2[i]);
    }
    CIAData->endTransmission();
}
