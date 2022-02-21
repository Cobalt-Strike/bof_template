#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 

void go(char * args, int alen) { 
   datap  parser;
   int    userInt, minInt, maxInt;
   unsigned int userUInt, minUInt, maxUInt;

   /*
    *  Signed int support:
    *     BeaconDataInt   supports the numeric range: -2147483648 through 2147483647
    *
    *  Unsigned int support:
    *     (unsigned int)   BeaconDataInt   supports the numeric range: 0 through 4294967295
    *
    *  However, the unsigned int range: 2147483648 through 4294967295
    *  requires the use of unsigned int casting of the negative integer values
    *    unsigned int 2147483648 == (unsigned int) -2147483648
    *    unsigned int 4294967295 == (unsigned int) -1
    */
   BeaconDataParse(&parser, args, alen);
   userInt  = BeaconDataInt(&parser);
   userUInt = (unsigned int) BeaconDataInt(&parser);
   minInt   = BeaconDataInt(&parser);
   maxInt   = BeaconDataInt(&parser);
   minUInt  = (unsigned int) BeaconDataInt(&parser);
   maxUInt  = (unsigned int) BeaconDataInt(&parser);


   BeaconPrintf(CALLBACK_OUTPUT, "!!!! Start testBeaconDataIntegers !!!!");

   BeaconPrintf(CALLBACK_OUTPUT, "user defined signed int     : %d", userInt);
   BeaconPrintf(CALLBACK_OUTPUT, "user defined unsigned int   : %u", userUInt);

   BeaconPrintf(CALLBACK_OUTPUT, "signed int min              : %d", minInt);
   BeaconPrintf(CALLBACK_OUTPUT, "signed int max              : %d", maxInt);

   BeaconPrintf(CALLBACK_OUTPUT, "unsigned int min            : %u", minUInt);
   BeaconPrintf(CALLBACK_OUTPUT, "unsigned int max            : %u", maxUInt);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconDataIntegers !!!!\n\n");
} 

