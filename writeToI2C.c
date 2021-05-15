#include "ciaAllocation.h"
#include <Wire.h>



void writeToI2C(struct CIADataStruct *CIAData) {


//Option 1: Adafruit Library Method

    //X-face commands 

    Wire.begin()

    //posXlead1
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
    for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->posXlead1Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->posXlead1[i]);
    }
    Wire.endTransmission();

    //posXlead2
    CIAData->beginTransmission(devAddrWrite); //I2C Address
        for (int i = 0; i < 4; i++) {
        CIAData->write(CIAData->posXlead2Addr[i]); //Pin address (Register Address)
        CIAData->write(CIAData->posXlead2[i]);
    }
    Wire.endTransmission();

    //negXlead1  
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
        for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->negXlead1Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->negXlead1[i]);
    }
    Wire.endTransmission();

    //negXlead2
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
        for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->negXlead2Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->negXlead2[i]);
    }
    Wire.endTransmission();

    //Y-face commands   

    //posYlead1
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
            for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->posYlead1Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->posYlead1[i]);
    }
    Wire.endTransmission();

    //posYlead2
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
            for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->posYlead2Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->posYlead2[i]);
    }
    Wire.endTransmission();

    //negYlead1
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
                for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->negYlead1Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->negYlead1[i]);
    }
    Wire.endTransmission();

    //negYlead2
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
                for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->negYlead2Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->negYlead2[i]);
    }
    Wire.endTransmission();

    //Z-face commands  

    //posZlead1
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
    Wire.write(CIAData->posZlead1Addr[1]; //Pin address (Register Address)
                for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->posZlead1Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->posZlead1[i]);
    }
    Wire.endTransmission();
    
    //posZlead2
    Wire.beginTransmission(CIAData->devAddrWrite); //I2C Address
                for (int i = 0; i < 4; i++) {
        Wire.write(CIAData->posZlead2Addr[i]); //Pin address (Register Address)
        Wire.write(CIAData->posZlead2[i]);
    }
    Wire.endTransmission();
}
