#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 

void go(char * args, int alen) { 
   datap  parser;
   short  userShort, minShort, maxShort;
   unsigned short userUShort, minUShort, maxUShort;

   /*
    *  Signed short support:
    *     BeaconDataShort supports the numeric range: -32768 through 32767
    *
    *  Unsigned short support:
    *     (unsigned short) BeaconDataShort supports the numeric range: 0 through 65535
    *
    */
   BeaconDataParse(&parser, args, alen);
   userShort  = BeaconDataShort(&parser);
   userUShort = (unsigned short) BeaconDataShort(&parser);
   minShort   = BeaconDataShort(&parser);
   maxShort   = BeaconDataShort(&parser);
   minUShort  = (unsigned short) BeaconDataShort(&parser);
   maxUShort  = (unsigned short) BeaconDataShort(&parser);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! Start testBeaconDataShorts !!!!");

   BeaconPrintf(CALLBACK_OUTPUT, "user defined signed short   : %hi", userShort);
   BeaconPrintf(CALLBACK_OUTPUT, "user defined unsigned short : %hu", userUShort);

   BeaconPrintf(CALLBACK_OUTPUT, "signed short min            : %hi", minShort);
   BeaconPrintf(CALLBACK_OUTPUT, "signed short max            : %hi", maxShort);

   BeaconPrintf(CALLBACK_OUTPUT, "unsigned short min          : %hu", minUShort);
   BeaconPrintf(CALLBACK_OUTPUT, "unsigned short max          : %hu", maxUShort);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconDataShorts !!!!\n\n");
} 

