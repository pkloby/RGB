#include "peripheral/ports/plib_ports.h"
#include <peripheral/usart/plib_usart.h>
#include "system_definitions.h"

// In ISR
//#define BEFORE_WHILE 1
//#define BEFORE_SIZE_CHECK 64
//#define AFTER_SIZE_CHECK 32
//#define SEND_MESSAGE 11
//#define BEGINNING_WHILE 10
//#define END_WHILE 14
//#define BEGINNING_ISR 1
//#define END_ISR 19
//#define TRANSMIT_ISR 3
//#define DISABLE_TRANSMIT 7 
//#define RECEIVE_ISR 50

void dbgInit();

bool dbgUARTVal(char *outVal);

bool dbgOutputVal(unsigned int outVal);

bool dbgOutputLoc(unsigned int outVal);
