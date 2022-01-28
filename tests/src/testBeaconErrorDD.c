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
DECLSPEC_IMPORT void   BeaconErrorDD(int type, int arg1, int arg2);

void go(char * args, int alen) { 

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! Start testBeaconErrorDD !!!!");

   BeaconErrorDD(0x1e, 123456, 20);
   BeaconErrorDD(0x1f, 123456, 20);
   BeaconErrorDD(0x20, 123456, 20);
   BeaconErrorDD(0x21, 123456, 20);
   BeaconErrorDD(0x22, 123456, 20);
   BeaconErrorDD(0x23, 123456, 20);
   BeaconErrorDD(0x24, 123456, 20);
   BeaconErrorDD(0x25, 123456, 20);
   BeaconErrorDD(0x26, 123456, 20);
   BeaconErrorDD(0x27, 123456, 20);
   BeaconErrorDD(0x48, 123456, 20);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconErrorDD !!!!\n\n");
} 

