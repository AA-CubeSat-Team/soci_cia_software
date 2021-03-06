#ifndef mtq_wrap_dev_H
#define mtq_wrap_dev_H
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#define DEV_ADDR_WRITE 142

// CIA data struct: Stores translated magnetic moment commands for each lead of
// every magnetorquer.
struct CIADataStruct
{
  /** definitions of the 4 bytes in each lead (pg. 21 of data sheet)
    register  Bit     Access  Value       Description
    LEDX_ON_L [7:0] R/W     0000 0000*  LED_ON count for LEDX, 8 LSBs
    LEDX_ON_H [7:5] R     000*      non-writable
              [4]     R/W        0*     LEDX full ON
              [3:0] R/W          0000*  LED_ON count for LEDX, 4 MSBs
    LEDX_OFF_L  [7:0] R/W     0000 0000*  LED_OFF count for LEDX, 8 LSBs
    LEDX_OFF_H  [7:5] R     000*      non-writable
              [4]     R/W        1*     LEDX full OFF
              [3:0] R/W          0000*  LED_OFF count for LEDX, 4 MSBs
    = default value
    The LEDn_ON_H output control bit 4, when set to logic 1, causes the output to be always
    ON. The turning ON of the LED is delayed by the amount in the LEDn_ON registers.
    LEDn_OFF[11:0] are ignored. When this bit = 0, then the LEDn_ON and LEDn_OFF
    registers are used according to their normal definition.
    The LEDn_OFF_H output control bit 4, when set to logic 1, causes the output to be
    always OFF. In this case the values in the LEDn_ON registers are ignored.
    Remark: When all LED outputs are configured as �always OFF�, the prescale counter and
    all associated PWM cycle timing logic are disabled. If LEDn_ON_H[4] and
    LEDn_OFF_H[4] are set at the same time, the LEDn_OFF_H[4] function takes
    precedence. (pg. 24 of data sheet)
    see PCA9685 data sheet for more info: https://cdn-shop.adafruit.com/datasheets/PCA9685.pdf
  */

  // positive x-face commands
  unsigned char posXlead1[4]; //!< 4 commands for the positive x face magnetorquer, lead 1
  unsigned char posXlead2[4]; //!< 4 commands for the positive x face magnetorquer, lead 2

  // negative x-face commands
  unsigned char negXlead1[4]; //!< 4 commands for the negative x face magnetorquer, lead 1
  unsigned char negXlead2[4]; //!< 4 commands for the negative x face magnetorquer, lead 2

  // positive y-face commands
  unsigned char posYlead1[4]; //!< 4 commands for the positive y face magnetorquer, lead 1
  unsigned char posYlead2[4]; //!< 4 commands for the positive y face magnetorquer, lead 2

  // negative y-face commands
  unsigned char negYlead1[4]; //!< 4 commands for the negative y face magnetorquer, lead 1
  unsigned char negYlead2[4]; //!< 4 commands for the negative y face magnetorquer, lead 2

  // positive z-face commands
  unsigned char posZlead1[4]; //!< 4 commands for the positive z face magnetorquer, lead 1
  unsigned char posZlead2[4]; //!< 4 commands for the positive z face magnetorquer, lead 2

  //Address (Moved into struct)

  unsigned char posXlead1Addr[4] = {14, 15, 16, 17}; // MTQ2_A
  unsigned char posXlead2Addr[4] = {18, 19, 20, 21}; // MTQ2_B

  unsigned char negXlead1Addr[4] = {6, 7, 8, 9};     // MTQ1_A
  unsigned char negXlead2Addr[4] = {10, 11, 12, 13}; // MTQ1_B

  unsigned char posYlead1Addr[4] = {22, 23, 24, 25}; // MTQ3_A
  unsigned char posYlead2Addr[4] = {26, 27, 28, 29}; // MTQ3_B

  unsigned char negYlead1Addr[4] = {30, 31, 32, 33}; // MTQ4_A
  unsigned char negYlead2Addr[4] = {34, 35, 36, 37}; // MTQ4_B

  unsigned char posZlead1Addr[4] = {38, 39, 40, 41}; // MTQ5_A
  unsigned char posZlead2Addr[4] = {42, 43, 44, 45}; // MTQ5_B
};

// inputs for allocation
struct allocationParameters {
  // contains a single magnetic moment command (units Am2)
  double command;
  // designates which magnetorquer to write to (1 is posX, 2 is negX, and so on)
  unsigned int whichMag;
};

// inputs for setMags
struct setMagsParameters {
  // contains the magnetic moment commands in the x, y, and z directions (units Am2)
  double commands[3];
  // contains the operational status of each of the five magnetorquers
  bool magStatus[5];
};

// PCA9685 device address with read
static const unsigned char devAddrRead = 143; // 10001111

// Register addresses for each magnetorquer lead. Each array of addresses has a
// corresponding array of commands in the "CIADataStruct". As with the
// "CIADataStruct", each array corresponds to a single magnetorquer lead. See
// "I2C communication starter" file for more info on sending commands to the
// board. Each array was labeled according to the CIA board schematic.

//Address moved into CIADataStruct


// helpful constants
static const char offLead[4] = {0, 0, 0, 16}; // for leads set to "full off"
static const double maxMoment = 0.0515; // 0.0515 Am2 is max dipole moment
// from SOC-i PDR
static const unsigned int separateBytes = 256; // used to split values into
// two separate bytes
static const unsigned int cycleLength = 4096; // number of counts in a full cycle

// function declarations
/** setMags
    The first input to setMags is a pointer to a setMagsParameters struct,
    containing a 3-element array of magnetic moment commands and a 5-element
    array of the status of each magnetorquer. setMags then writes the correct
    commands to each lead in the passed CIADataStruct pointer, according to the
    magnetic moment command array.
    If both magnetorquers in the x or y direction are working, then half of the
    command is sent to the positive face magnetorquer and the negative of the
    other half to the negative face magnetorquer. If one of the redundant
    magnetorquers fails, then all of the signal is sent to the working magnetorquer.
    All nonoperational magnetorquers get "offLead" assigned to both leads.
*/
void setMags(struct setMagsParameters *parameters, struct CIADataStruct *CIAData);

/** allocation
    The first input to allocation is a pointer to an allocationParameters struct,
    containing a single magnetic moment command and an integer that denotes which
    magnetorquer to write to. allocation translates the command and writes to
    the leads of the correct magnetorquer within the passed CIADataStruct pointer.
*/
void allocation(struct allocationParameters *parameters, struct CIADataStruct *CIAData);

/** writeToI2C
    decription...
*/
void writeToI2C(struct CIADataStruct *CIAData);

#endif
