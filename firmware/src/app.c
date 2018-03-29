/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

#define I2CID I2C_ID_1
#define SLAVE_TARGET_ADDRESS 0x29 //This should be the slave address of the RGB
#define COMMAND_REGISTER_COMMAND 0xB6 //This is sent to the command register of the slave to configure
#define MAX_BYTE_COUNT 7

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    dbgInit();
    
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3); //LED Initialize
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1);
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1, 1);
    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */



void APP_Tasks ( void )
{
//    retrieveDataFromI2C();
    
    uint8_t slaveAddress;
    uint8_t data;
    int count = 0;
    dbgOutputLoc(66);
//    DRV_I2C_MasterStart();
//    DRV_I2C_WaitForStartComplete();
//    while(!DRV_I2C_MasterBusIdle());
//    PLIB_I2C_StartWasDetected(myID);
    //Check if the bus is idle and available to use
    if (PLIB_I2C_BusIsIdle(I2CID)){
        //Initiate the master start signal
        PLIB_I2C_MasterStart(I2CID);
        //After sending the master start, must check for arbitration loss incase
        //another master initiated start at the same time
//        while(!PLIB_I2C_StartWasDetected(I2CID));
        if (PLIB_I2C_ArbitrationLossHasOccurred(I2CID)){
            //Abort transfer, try again later
            PLIB_I2C_ArbitrationLossClear(I2CID);
        }
        else{
            //No arbitration loss, proceed with data transfer
            //Formats the slave address with the write indication bit 0
            slaveAddress = (SLAVE_TARGET_ADDRESS << 1);
            if (PLIB_I2C_TransmitterIsReady(I2CID)){
                PLIB_I2C_TransmitterByteSend(I2CID, slaveAddress);
                //Once you transmit, you must once again check for arbitration
                //loss and an ACK or NACK from the slave
                if (PLIB_I2C_ArbitrationLossHasOccurred(I2CID)){
                    PLIB_I2C_ArbitrationLossClear(I2CID);
                }
                else{
                    if (PLIB_I2C_TransmitterByteWasAcknowledged(I2CID)){
                        //Transmission of the slave address was successful. Now
                        //we want to configure the command register.
                        if (PLIB_I2C_TransmitterIsReady(I2CID)){
                            PLIB_I2C_TransmitterByteSend(I2CID, 0x01);
//                            PLIB_I2C_TransmitterByteSend(I2CID, COMMAND_REGISTER_COMMAND);
                            if (PLIB_I2C_ArbitrationLossHasOccurred(I2CID)){
                                PLIB_I2C_ArbitrationLossClear(I2CID);
                            }
                            else{
                                if(PLIB_I2C_TransmitterByteWasAcknowledged(I2CID)){
                                    //Configuring the command register was successful.
                                    //Now we want to send a repeated start followed
                                    //by the slave address masked to read
                                    PLIB_I2C_MasterStartRepeat(I2CID);
                                    if (PLIB_I2C_ArbitrationLossHasOccurred(I2CID)){
                                        PLIB_I2C_ArbitrationLossClear(I2CID);
                                    }
                                    else{
                                        slaveAddress = (SLAVE_TARGET_ADDRESS << 1) | 0x1;
                                        if(PLIB_I2C_TransmitterIsReady(I2CID)){
                                            PLIB_I2C_TransmitterByteSend(I2CID, slaveAddress);
                                            if (PLIB_I2C_ArbitrationLossHasOccurred(I2CID)){
                                                PLIB_I2C_ArbitrationLossClear(I2CID);
                                            }
                                            else{
                                                if(PLIB_I2C_TransmitterByteWasAcknowledged(I2CID)){
                                                    //Now we want to start receiving data.
                                                    //Note: Arbitration Loss cannot occur during a master
                                                    //receiving data.
                                                    PLIB_I2C_MasterReceiverClock1Byte(I2CID);
                                                    PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
                                                    if(PLIB_I2C_ReceivedByteIsAvailable(I2CID)){
                                                        data = PLIB_I2C_ReceivedByteGet(I2CID);
                                                        
                                                        count++;
                                                        dbgOutputLoc(64);
                                                        //Determine if the data should be ACKed or NACKed
                                                        //NACKing a byte tells the slave you want to terminate
                                                        //Transmissions. So you must ACK in between each byte 
                                                        //until the last one.
                                                        if (count < MAX_BYTE_COUNT){
                                                            PLIB_I2C_ReceivedByteAcknowledge(I2CID, true);
                                                        }
                                                        else if (count >= MAX_BYTE_COUNT){
                                                            PLIB_I2C_ReceivedByteAcknowledge(I2CID, false);
                                                            //Must wait for ACK/NACK to complete
                                                            if (PLIB_I2C_ReceiverByteAcknowledgeHasCompleted(I2CID)){
                                                                //Byte transfer complete. Terminate connection
                                                                PLIB_I2C_MasterStop(I2CID);
                                                            }
                                                        }
                                                    }
                                                    dbgOutputLoc(2);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        
                    }
                    else{
                        //Transmission failed
                    }
                }
            }
        }
    }
    dbgOutputVal(2);
}

void retrieveDataFromI2C( void ){
    /*Start communications on I2C*/
    I2C_startProcess();
    /*Send the slave address*/
    I2C_writeAddress(SLAVE_TARGET_ADDRESS);
    
}

void I2C_startProcess( void ){
    /*Wait for bus to be Idle*/
    while(!DRV_I2C_MasterBusIdle(I2CID));
    /*Once it becomes open, must initiate start and check for completion*/
    DRV_I2C_MasterStart(I2CID);
    DRV_I2C_WaitForStartComplete(I2CID);
    /*Wait for bus to become idle again*/
    while(!DRV_I2C_MasterBusIdle(I2CID));
}

void I2C_writeAddress(uint8_t address){
    DRV_I2C_ByteWrite(I2CID, address);
    /*After writing, you must wait for completion*/
    DRV_I2C_WaitForByteWriteToComplete(I2CID);
    /*Wait for bus to become idle again*/
    while (!DRV_I2C_MasterBusIdle(I2CID));
}
/*******************************************************************************
 End of File
 */
