#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 

/*
  Internal functions which are not publicly documented
  Reason is the message strings that are displayed by 
  this function can not be modified other than the  
  integer that is passed in.
  Can be used if the message text works for your case
*/
DECLSPEC_IMPORT void   BeaconErrorNA(int type);

void go(char * args, int alen) { 

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! testBeaconErrorNA (No Arguments) !!!!");

   BeaconErrorNA(0x01);
   BeaconErrorNA(0x02);
   BeaconErrorNA(0x03);
   BeaconErrorNA(0x04);
   BeaconErrorNA(0x05);
   BeaconErrorNA(0x06);
   BeaconErrorNA(0x3b);
   BeaconErrorNA(0x3e);
   BeaconErrorNA(0x40);
   BeaconErrorNA(0x42);
   BeaconErrorNA(0x43);
   BeaconErrorNA(0x44);
   BeaconErrorNA(0x46);
   BeaconErrorNA(0x4b);
   BeaconErrorNA(0x4d);
   BeaconErrorNA(0x4e);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconErrorNA (No Arguments) !!!!\n\n");
} 

