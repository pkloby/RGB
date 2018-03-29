#include "debug.h"

/*
*******debug.c*********
PLIB_PORTS_PinDirectionOutputSet (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4)
         RC4 pin is an output
		 
PLIB_PORTS_PinWrite (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4, 1)
         Writes a "1" to RC4	

PLIB_PORTS_PinGet (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_4)
         Returns the value on PIN RC4 (PORTC, bit 4)	
		 
PLIB_PORTS_PinToggle (PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_5)
         Invert value on RC5 pin		 
		 
PLIB_USART_BaudRateSet (USART_ID_2, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_2), 9600)
         Set USART2 baud rate to 9600
*/

bool dbgOutputVal(unsigned int outVal) 
{
/*
On chipKit: In J4 --> Numbered 70-77
30 - 17 - RE5
31 - 38 - RE4
32 - 60 - RE3
33 - 61 - RE2
34 - 69 - RE1
35 - 73 - RE0
36 - 80 - RD10
37 - 84 - RD5
*/	

if (outVal > 127)
	return false;
	
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7, (outVal & 1) );	       
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6, ((outVal >> 1) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_5, ((outVal >> 2) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_4, ((outVal >> 3) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3, ((outVal >> 4) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2, ((outVal >> 5) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1, ((outVal >> 6) & 1));

// read current value then toggle last bit
PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_0);

	return true;
}


bool dbgOutputLoc(unsigned int outVal)
{
/*
46 - 89 - RF1
47 - 90 - RD6
48 - 91 - RD8
49 - 92 - RD11
50 - 95 - RG7
51 - 96 - RG8
52 - 97 - RG6
53 - 28 - RG9
*/
if (outVal > 255){
    return false;
}
	

PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1, (outVal & 1) );
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6, ((outVal >> 1) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8, ((outVal >> 2) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11, ((outVal >> 3) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7, ((outVal >> 4) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8, ((outVal >> 5) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6, ((outVal >> 6) & 1));
PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_9, ((outVal >> 7) & 1));

// read current value then toggle last bit
//PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_9);
	return true;
}


void dbgInit(){
    
    // dbgOutputVal Initializations
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_7);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_6);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_5);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_4);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_3);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_2);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_1);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, PORTS_BIT_POS_0);
    
    
    //dbgOutputLoc Initialization
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_9);
    
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_1); //SW3 on the I/O expansion board
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_7); //SW2 on the I/O expansion board
    
    
    
    
    //CLK_BUS_PERIPHERAL_2 = 0x01
//    PLIB_USART_TransmitterEnable(USART_ID_1);
//    PLIB_USART_Enable(USART_ID_1);
}

bool dbgUARTVal(char *outVal) 
{
//	while (PLIB_USART_TransmitterBufferIsFull(USART_ID_1) ) {
//		;
//	}
    int i = 0;
    while (outVal[i] != 0x00)
    {
	PLIB_USART_TransmitterByteSend(USART_ID_1, outVal[i]);
          i++;
    }
          return true;	
}