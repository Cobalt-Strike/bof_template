#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 

void go(char * args, int alen) { 
   datap  parser;
   char   *userString;
   int    userStringLen;
   int    userInt;
   short  userShort;

   BeaconDataParse(&parser, args, alen);
   userString = BeaconDataExtract(&parser, &userStringLen);
   userInt    = BeaconDataInt(&parser);
   userShort  = BeaconDataShort(&parser);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! Start testBeaconDataMixDataTypes !!!!");

   BeaconPrintf(CALLBACK_OUTPUT, "User string         : '%s' has %d characters", userString, userStringLen);

   BeaconPrintf(CALLBACK_OUTPUT, "User signed int     : %d", userInt);
   BeaconPrintf(CALLBACK_OUTPUT, "User unsigned int   : %u", (unsigned int) userInt);
   BeaconPrintf(CALLBACK_OUTPUT, "User signed short   : %hi", userShort);
   BeaconPrintf(CALLBACK_OUTPUT, "User unsigned short : %hu", (unsigned short) userShort);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconDataMixDataTypes !!!!\n\n");
} 

