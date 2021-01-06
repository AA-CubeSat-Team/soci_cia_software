#include "ciaAllocation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ciaAllocationUnitTests: Prints to the terminal predicted outputs and actual
// outputs for both functions, setMags and allocation.
int main(void)
{
    /// allocation middle case
    printf("\n");
    printf("allocation Unit Test\n");
    printf("This section will test each MTQ twice with different values to varify the stable-ness of the code.\n");
    printf("Momentum we are generate in each test is completely random.\n");
    printf("\n");
    struct CIADataStruct CIAData1;
    struct allocationParameters parameters1;
    unsigned char MTQ[10][4];

    for (int k = 0; k < 2; k++) {

        if(k == 1) {
                printf("Round 2 starts now.\n");
                printf("\n");
        }

        for (int i = 0; i < 5; i++) {
            
            // robust test by using random float points
            float x = (float)rand() / ((float)RAND_MAX);
            float y = (float)rand() / ((float)RAND_MAX);
            
            if(y <= 0.5) {
                x = -x;
            }

            parameters1.command =  x * maxMoment;
            parameters1.whichMag = i + 1;
            allocation(&parameters1, &CIAData1);

            // compute correct value
            int test = round(x * cycleLength);
            if (test <= 0) {
                test = -1 * test;
            }

            // first value is lead number, second value is the readings of each lead
            for (int j = 0; j < 4; j++) {
                MTQ[0][j] = CIAData1.posXlead1[j];
                MTQ[1][j] = CIAData1.posXlead2[j];
                MTQ[2][j] = CIAData1.negXlead1[j];
                MTQ[3][j] = CIAData1.negXlead2[j];
                MTQ[4][j] = CIAData1.posYlead1[j];
                MTQ[5][j] = CIAData1.posYlead2[j];
                MTQ[6][j] = CIAData1.negYlead1[j];
                MTQ[7][j] = CIAData1.negYlead2[j];
                MTQ[8][j] = CIAData1.posZlead1[j];
                MTQ[9][j] = CIAData1.posZlead2[j];
            }

            // 0 = posXlead1, 1 = posXlead 2, 2 = negXlead 1,.....
            printf("testing for MTQ %d\n", i);
            printf("ramdom float in this test is %e\n", x);
            printf("test variable in this test is %d\n", test);
            if (parameters1.command >= 0) {
                printf("lead1[0] = %d, should be %d\n", (int) MTQ[2*i][0], 0);
                printf("lead1[1] = %d, should be %d\n", (int) MTQ[2*i][1], 0);
                printf("lead1[2] = %d, should be %d\n", (int) MTQ[2*i][2], test % separateBytes);
                printf("lead1[3] = %d, should be %d\n", (int) MTQ[2*i][3], test / separateBytes);
                printf("lead2[0] = %d, should be %d\n", (int) MTQ[2*i+1][0], 0);
                printf("lead2[1] = %d, should be %d\n", (int) MTQ[2*i+1][1], 0);
                printf("lead2[2] = %d, should be %d\n", (int) MTQ[2*i+1][2], 0);
                printf("lead2[3] = %d, should be %d\n", (int) MTQ[2*i+1][3], 16);
            } else {
                printf("lead1[0] = %d, should be %d\n", (int) MTQ[2*i][0], 0); 
                printf("lead1[1] = %d, should be %d\n", (int) MTQ[2*i][1], 0); 
                printf("lead1[2] = %d, should be %d\n", (int) MTQ[2*i][2], 0); 
                printf("lead1[3] = %d, should be %d\n", (int) MTQ[2*i][3], 16); 
                printf("lead2[0] = %d, should be %d\n", (int) MTQ[2*i+1][0], 0); 
                printf("lead2[1] = %d, should be %d\n", (int) MTQ[2*i+1][1], 0); 
                printf("lead2[2] = %d, should be %d\n", (int) MTQ[2*i+1][2], test % separateBytes); 
                printf("lead2[3] = %d, should be %d\n", (int) MTQ[2*i+1][3], test / separateBytes); 
            }
            printf("\n");
        }
    }
    
    printf("\n");

    /// allocation "full on" edge case
    printf("allocation \"Full On\"\n");
    printf("assign positive or negative max moment to each leads of each MTQ to test if full on is robust.\n");
    printf("\n");

    for (int n = 0; n < 2; n++) {
        if (n == 0) {
            printf("positive full on test starts now.\n");
            printf("\n");
        } else {
            printf("negative full on test starts now.\n");
            printf("\n");
        }
        
        
        for (int i = 0; i < 5; i++) {

            if(n == 0) {
                parameters1.command = maxMoment;
            } else {
                parameters1.command = -1.0 * maxMoment;
            }
            parameters1.whichMag = i + 1;
            allocation(&parameters1, &CIAData1);

            for (int j = 0; j < 4; j++) {
                    MTQ[0][j] = CIAData1.posXlead1[j];
                    MTQ[1][j] = CIAData1.posXlead2[j];
                    MTQ[2][j] = CIAData1.negXlead1[j];
                    MTQ[3][j] = CIAData1.negXlead2[j];
                    MTQ[4][j] = CIAData1.posYlead1[j];
                    MTQ[5][j] = CIAData1.posYlead2[j];
                    MTQ[6][j] = CIAData1.negYlead1[j];
                    MTQ[7][j] = CIAData1.negYlead2[j];
                    MTQ[8][j] = CIAData1.posZlead1[j];
                    MTQ[9][j] = CIAData1.posZlead2[j];
            }

            printf("testing for MTQ %d\n", i);

            if (parameters1.command >= 0) {
                printf("lead1[0] = %d, should be %d\n", (int) MTQ[2*i][0], 0);
                printf("lead1[1] = %d, should be %d\n", (int) MTQ[2*i][1], 16);
                printf("lead1[2] = %d, should be %d\n", (int) MTQ[2*i][2], 0);
                printf("lead1[3] = %d, should be %d\n", (int) MTQ[2*i][3], 0);
                printf("lead2[0] = %d, should be %d\n", (int) MTQ[2*i+1][0], 0);
                printf("lead2[1] = %d, should be %d\n", (int) MTQ[2*i+1][1], 0);
                printf("lead2[2] = %d, should be %d\n", (int) MTQ[2*i+1][2], 0);
                printf("lead2[3] = %d, should be %d\n", (int) MTQ[2*i+1][3], 16);
            } else {
                printf("lead1[0] = %d, should be %d\n", (int) MTQ[2*i][0], 0); 
                printf("lead1[1] = %d, should be %d\n", (int) MTQ[2*i][1], 0); 
                printf("lead1[2] = %d, should be %d\n", (int) MTQ[2*i][2], 0); 
                printf("lead1[3] = %d, should be %d\n", (int) MTQ[2*i][3], 16); 
                printf("lead2[0] = %d, should be %d\n", (int) MTQ[2*i+1][0], 0); 
                printf("lead2[1] = %d, should be %d\n", (int) MTQ[2*i+1][1], 16); 
                printf("lead2[2] = %d, should be %d\n", (int) MTQ[2*i+1][2], 0); 
                printf("lead2[3] = %d, should be %d\n", (int) MTQ[2*i+1][3], 0); 
            }
        
            printf("\n");
        }
    }
    
    /// allocation "full off" edge case
    printf("allocation \"Full Off\"\n");
    printf("assign off to each leads of each MTQ to test if full off is robust.\n");
    printf("\n");

    for (int i = 0; i < 5; i++) {
        parameters1.command = 0.0 * maxMoment;
        parameters1.whichMag = i + 1;
        allocation(&parameters1, &CIAData1);

        for (int j = 0; j < 4; j++) {
            MTQ[0][j] = CIAData1.posXlead1[j];
            MTQ[1][j] = CIAData1.posXlead2[j];
            MTQ[2][j] = CIAData1.negXlead1[j];
            MTQ[3][j] = CIAData1.negXlead2[j];
            MTQ[4][j] = CIAData1.posYlead1[j];
            MTQ[5][j] = CIAData1.posYlead2[j];
            MTQ[6][j] = CIAData1.negYlead1[j];
            MTQ[7][j] = CIAData1.negYlead2[j];
            MTQ[8][j] = CIAData1.posZlead1[j];
            MTQ[9][j] = CIAData1.posZlead2[j];
        }

        printf("testing for MTQ %d\n", i);

        if (parameters1.command >= 0) {
            printf("lead1[0] = %d, should be %d\n", (int) MTQ[2*i][0], 0);
            printf("lead1[1] = %d, should be %d\n", (int) MTQ[2*i][1], 0);
            printf("lead1[2] = %d, should be %d\n", (int) MTQ[2*i][2], 0);
            printf("lead1[3] = %d, should be %d\n", (int) MTQ[2*i][3], 16);
            printf("lead2[0] = %d, should be %d\n", (int) MTQ[2*i+1][0], 0);
            printf("lead2[1] = %d, should be %d\n", (int) MTQ[2*i+1][1], 0);
            printf("lead2[2] = %d, should be %d\n", (int) MTQ[2*i+1][2], 0);
            printf("lead2[3] = %d, should be %d\n", (int) MTQ[2*i+1][3], 16);
        } else {
            printf("lead1[0] = %d, should be %d\n", (int) MTQ[2*i][0], 0); 
            printf("lead1[1] = %d, should be %d\n", (int) MTQ[2*i][1], 0); 
            printf("lead1[2] = %d, should be %d\n", (int) MTQ[2*i][2], 0); 
            printf("lead1[3] = %d, should be %d\n", (int) MTQ[2*i][3], 16); 
            printf("lead2[0] = %d, should be %d\n", (int) MTQ[2*i+1][0], 0); 
            printf("lead2[1] = %d, should be %d\n", (int) MTQ[2*i+1][1], 0); 
            printf("lead2[2] = %d, should be %d\n", (int) MTQ[2*i+1][2], 0); 
            printf("lead2[3] = %d, should be %d\n", (int) MTQ[2*i+1][3], 16); 
        }

        printf("\n");
    }
    
    /// setMags NEWWWWW
    printf("setMags Unit Test NEW\n");
    printf("Positive moment test starts now\n");
    printf("\n");
    struct CIADataStruct CIAData2;
    struct setMagsParameters parameters2;
    
    float x;
    float y;
    float z;

    for (int m = 0; m < 2; m++) {
        if (m == 0) {
            x = (float)rand() / ((float)RAND_MAX);
            y = (float)rand() / ((float)RAND_MAX);
            z = (float)rand() / ((float)RAND_MAX);
        } else {
            printf("Negative moment test starts now\n");
            printf("\n");
            x = (float)rand() / ((float)RAND_MAX) - 1;
            y = (float)rand() / ((float)RAND_MAX) - 1;
            z = (float)rand() / ((float)RAND_MAX) - 1;
        }

        parameters2.commands[0] = x * maxMoment;
        parameters2.commands[1] = y * maxMoment;
        parameters2.commands[2] = z * maxMoment;
        int i;
        for (i = 0; i < 5; ++i) {
            parameters2.magStatus[i] = true;
        }

        setMags(&parameters2, &CIAData2);
        for (int j = 0; j < 4; j++) {
            MTQ[0][j] = CIAData2.posXlead1[j];
            MTQ[1][j] = CIAData2.posXlead2[j];
            MTQ[2][j] = CIAData2.negXlead1[j];
            MTQ[3][j] = CIAData2.negXlead2[j];
            MTQ[4][j] = CIAData2.posYlead1[j];
            MTQ[5][j] = CIAData2.posYlead2[j];
            MTQ[6][j] = CIAData2.negYlead1[j];
            MTQ[7][j] = CIAData2.negYlead2[j];
            MTQ[8][j] = CIAData2.posZlead1[j];
            MTQ[9][j] = CIAData2.posZlead2[j];
        }

        int test = abs(round(x * cycleLength));

        // correct value for onlead
        char onLeadx[] = {0, 0, (int) round(abs(x * cycleLength / 2)) % separateBytes, round(abs(x * cycleLength) / 2 / separateBytes)};
        char onLeady[] = {0, 0, (int) abs(round(y * cycleLength / 2)) % separateBytes, round(abs(y * cycleLength) / 2 / separateBytes)};
        char onLeadz[] = {0, 0, abs(round(z * cycleLength)) % separateBytes, abs(round(z * cycleLength)) / separateBytes};
        unsigned char onLead[3][4];

        for (int i = 0; i < 3; i++) {
            if (i == 0) {
                for (int j = 0; j < 4; j++) {
                    onLead[0][j] = onLeadx[j];
                }
            } else if (i == 1) {
                for (int j = 0; j < 4; j++) {
                    onLead[1][j] = onLeady[j];
                }
            } else {
                for (int j = 0; j < 4; j++) {
                    onLead[2][j] = onLeadz[j];
                }
            }
        }
        
        if (m == 0) {
            for (int n = 0; n < 5; n++){
                if (n == 4) {
                    printf("testing for MTQ %d\n", n);
                    printf("lead%d[0] = %d, should be %d\n",2*n, (int) MTQ[2*n][0], onLead[n/2][0]);
                    printf("lead%d[1] = %d, should be %d\n",2*n, (int) MTQ[2*n][1], onLead[n/2][1]);
                    printf("lead%d[2] = %d, should be %d\n",2*n, (int) MTQ[2*n][2], onLead[n/2][2]);
                    printf("lead%d[3] = %d, should be %d\n",2*n, (int) MTQ[2*n][3], onLead[n/2][3]);
                    printf("lead%d[0] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][0], 0);
                    printf("lead%d[1] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][1], 0);
                    printf("lead%d[2] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][2], 0);
                    printf("lead%d[3] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][3], 16);
                    printf("\n");
                } else if (n % 2 == 0){
                    printf("testing for MTQ %d\n", n);
                    printf("lead%d[0] = %d, should be %d\n",2*n, (int) MTQ[2*n][0], onLead[n/2][0]);
                    printf("lead%d[1] = %d, should be %d\n",2*n, (int) MTQ[2*n][1], onLead[n/2][1]);
                    printf("lead%d[2] = %d, should be %d\n",2*n, (int) MTQ[2*n][2], onLead[n/2][2]);
                    printf("lead%d[3] = %d, should be %d\n",2*n, (int) MTQ[2*n][3], onLead[n/2][3]);
                    printf("lead%d[0] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][0], 0);
                    printf("lead%d[1] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][1], 0);
                    printf("lead%d[2] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][2], 0);
                    printf("lead%d[3] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][3], 16);
                    printf("\n");
                } else {
                    printf("testing for MTQ %d\n", n);
                    printf("lead%d[0] = %d, should be %d\n",2*n, (int) MTQ[2*n][0], 0);
                    printf("lead%d[1] = %d, should be %d\n",2*n, (int) MTQ[2*n][1], 0);
                    printf("lead%d[2] = %d, should be %d\n",2*n, (int) MTQ[2*n][2], 0);
                    printf("lead%d[3] = %d, should be %d\n",2*n, (int) MTQ[2*n][3], 16);
                    printf("lead%d[0] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][0], onLead[n/2][0]);
                    printf("lead%d[1] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][1], onLead[n/2][1]);
                    printf("lead%d[2] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][2], onLead[n/2][2]);
                    printf("lead%d[3] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][3], onLead[n/2][3]);
                    printf("\n");
                }
            }
        } else {
            for (int n = 0; n < 5; n++){
                if (n == 4) {
                    printf("testing for MTQ %d\n", n);
                    printf("lead%d[0] = %d, should be %d\n",2*n, (int) MTQ[2*n][0], 0);
                    printf("lead%d[1] = %d, should be %d\n",2*n, (int) MTQ[2*n][1], 0);
                    printf("lead%d[2] = %d, should be %d\n",2*n, (int) MTQ[2*n][2], 0);
                    printf("lead%d[3] = %d, should be %d\n",2*n, (int) MTQ[2*n][3], 16);
                    printf("lead%d[0] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][0], onLead[n/2][0]);
                    printf("lead%d[1] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][1], onLead[n/2][1]);
                    printf("lead%d[2] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][2], onLead[n/2][2]);
                    printf("lead%d[3] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][3], onLead[n/2][3]);
                    printf("\n");
                } else if (n % 2 == 0){
                    printf("testing for MTQ %d\n", n);
                    printf("lead%d[0] = %d, should be %d\n",2*n, (int) MTQ[2*n][0], 0);
                    printf("lead%d[1] = %d, should be %d\n",2*n, (int) MTQ[2*n][1], 0);
                    printf("lead%d[2] = %d, should be %d\n",2*n, (int) MTQ[2*n][2], 0);
                    printf("lead%d[3] = %d, should be %d\n",2*n, (int) MTQ[2*n][3], 16);
                    printf("lead%d[0] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][0], onLead[n/2][0]);
                    printf("lead%d[1] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][1], onLead[n/2][1]);
                    printf("lead%d[2] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][2], onLead[n/2][2]);
                    printf("lead%d[3] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][3], onLead[n/2][3]);
                    printf("\n");
                } else {
                    printf("testing for MTQ %d\n", n);
                    printf("lead%d[0] = %d, should be %d\n",2*n, (int) MTQ[2*n][0], onLead[n/2][0]);
                    printf("lead%d[1] = %d, should be %d\n",2*n, (int) MTQ[2*n][1], onLead[n/2][1]);
                    printf("lead%d[2] = %d, should be %d\n",2*n, (int) MTQ[2*n][2], onLead[n/2][2]);
                    printf("lead%d[3] = %d, should be %d\n",2*n, (int) MTQ[2*n][3], onLead[n/2][3]);
                    printf("lead%d[0] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][0], 0);
                    printf("lead%d[1] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][1], 0);
                    printf("lead%d[2] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][2], 0);
                    printf("lead%d[3] = %d, should be %d\n",2*n+1, (int) MTQ[2*n+1][3], 16);
                    printf("\n");
                }
            }
        }
    }

}
