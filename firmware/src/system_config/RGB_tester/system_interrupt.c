/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

//#define myID I2C_ID_1
//#define SLAVE_TARGET_ADDRESS 0x29 //This should be the slave address of the RGB
//#define COMMAND_REGISTER_COMMAND 0xB6 //This is sent to the command register of the slave to configure
//#define MAX_BYTE_COUNT 7

void __ISR(_I2C_1_VECTOR, ipl1AUTO) _IntHandlerDrvI2CInstance0(void)
{
//    uint8_t slaveAddress;
//    uint8_t data;
//    int count = 0;
//    //Check if the bus is idle and available to use
//    if (PLIB_I2C_BusIsIdle(myID)){
//        //Initiate the master start signal
//        PLIB_I2C_MasterStart(myID);
//        //After sending the master start, must check for arbitration loss incase
//        //another master initiated start at the same time
//        if (PLIB_I2C_ArbitrationLossHasOccurred(myID)){
//            //Abort transfer, try again later
//            PLIB_I2C_ArbitrationLossClear(myID);
//        }
//        else{
//            //No arbitration loss, proceed with data transfer
//            //Formats the slave address with the write indication bit 0
//            slaveAddress = (SLAVE_TARGET_ADDRESS << 1);
//            if (PLIB_I2C_TransmitterIsReady(myID)){
//                PLIB_I2C_TransmitterByteSend(myID, slaveAddress);
//                
//                //Once you transmit, you must once again check for arbitration
//                //loss and an ACK or NACK from the slave
//                if (PLIB_I2C_ArbitrationLossHasOccurred(myID)){
//                    PLIB_I2C_ArbitrationLossClear(myID);
//                }
//                else{
//                    if (PLIB_I2C_TransmitterByteWasAcknowledged(myID)){
//                        //Transmission of the slave address was successful. Now
//                        //we want to configure the command register.
//                        if (PLIB_I2C_TransmitterIsReady(myID)){
//                            PLIB_I2C_TransmitterByteSend(myID, COMMAND_REGISTER_COMMAND);
//                            if (PLIB_I2C_ArbitrationLossHasOccurred(myID)){
//                                PLIB_I2C_ArbitrationLossClear(myID);
//                            }
//                            else{
//                                if(PLIB_I2C_TransmitterByteWasAcknowledged(myID)){
//                                    //Configuring the command register was successful.
//                                    //Now we want to send a repeated start followed
//                                    //by the slave address masked to read
//                                    PLIB_I2C_MasterStartRepeat(myID);
//                                    if (PLIB_I2C_ArbitrationLossHasOccurred(myID)){
//                                        PLIB_I2C_ArbitrationLossClear(myID);
//                                    }
//                                    else{
//                                        slaveAddress = (SLAVE_TARGET_ADDRESS << 1) | 0x1;
//                                        if(PLIB_I2C_TransmitterIsReady(myID)){
//                                            PLIB_I2C_TransmitterByteSend(myID, slaveAddress);
//                                            if (PLIB_I2C_ArbitrationLossHasOccurred(myID)){
//                                                PLIB_I2C_ArbitrationLossClear(myID);
//                                            }
//                                            else{
//                                                if(PLIB_I2C_TransmitterByteWasAcknowledged(myID)){
//                                                    //Now we want to start receiving data.
//                                                    //Note: Arbitration Loss cannot occur during a master
//                                                    //receiving data.
//                                                    PLIB_I2C_MasterReceiverClock1Byte(myID);
//                                                    if(PLIB_I2C_ReceivedByteIsAvailable(myID)){
//                                                        data = PLIB_I2C_ReceivedByteGet(myID);
//                                                        PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
//                                                        count++;
//
//                                                        //Determine if the data should be ACKed or NACKed
//                                                        //NACKing a byte tells the slave you want to terminate
//                                                        //Transmissions. So you must ACK in between each byte 
//                                                        //until the last one.
//                                                        if (count < MAX_BYTE_COUNT){
//                                                            PLIB_I2C_ReceivedByteAcknowledge(myID, true);
//                                                        }
//                                                        else if (count >= MAX_BYTE_COUNT){
//                                                            PLIB_I2C_ReceivedByteAcknowledge(myID, false);
//                                                            //Must wait for ACK/NACK to complete
//                                                            if (PLIB_I2C_ReceiverByteAcknowledgeHasCompleted(myID)){
//                                                                //Byte transfer complete. Terminate connection
//                                                                PLIB_I2C_MasterStop(myID);
//                                                            }
//                                                        }
//                                                    }
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                        
//                    }
//                    else{
//                        //Transmission failed
//                    }
//                }
//            }
//        }
//    }
    
//    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_1_MASTER);
//    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_1_ERROR);
//	DRV_I2C0_Tasks();
}
     
 
   

 
 
 

 




 
 
/*******************************************************************************
 End of File
*/
