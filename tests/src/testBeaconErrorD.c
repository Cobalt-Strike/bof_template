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
DECLSPEC_IMPORT void   BeaconErrorD(int type, int arg1);

void go(char * args, int alen) { 

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! testBeaconErrorD !!!!");

   BeaconErrorD(0x07, 1234);
   BeaconErrorD(0x08, 1234);
   BeaconErrorD(0x09, 1234);
   BeaconErrorD(0x0a, 1234);
   BeaconErrorD(0x0b, 1234);
   BeaconErrorD(0x0c, 1234);
   BeaconErrorD(0x0d, 1234);
   BeaconErrorD(0x0e, 1234);
   BeaconErrorD(0x0f, 1234);
   BeaconErrorD(0x10, 1234);
   BeaconErrorD(0x11, 1234);
   BeaconErrorD(0x12, 1234);
   BeaconErrorD(0x13, 1234);
   BeaconErrorD(0x14, 1234);
   BeaconErrorD(0x15, 1234);
   BeaconErrorD(0x16, 1234);
   BeaconErrorD(0x17, 1234);
   BeaconErrorD(0x18, 1234);
   BeaconErrorD(0x19, 1234);
   BeaconErrorD(0x1a, 1234);
   BeaconErrorD(0x1b, 1234);
   BeaconErrorD(0x1c, 1234);
   BeaconErrorD(0x1d, 1234);
   BeaconErrorD(0x3f, 1234);
   BeaconErrorD(0x41, 1234);
   BeaconErrorD(0x47, 1234);
   BeaconErrorD(0x49, 1234);
   BeaconErrorD(0x4f, 1234);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconErrorD !!!!\n\n");
} 

