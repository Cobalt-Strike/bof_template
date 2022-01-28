#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 

void go(char * args, int alen) { 
   datap  parser;
   char   *string1, *string2, *string3;
   int    string1Len, string2Len;

   BeaconDataParse(&parser, args, alen);
   /* Examples of extracting the string and length */
   string1  = BeaconDataExtract(&parser, &string1Len);
   string2  = BeaconDataExtract(&parser, &string2Len);
   
   /* Example of extracting just the string if you do not need the length */
   string3  = BeaconDataExtract(&parser, NULL);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! Start testBeaconDataStrings !!!!");

   BeaconPrintf(CALLBACK_OUTPUT, "User string: '%s' has %d characters", string1, string1Len);
   BeaconPrintf(CALLBACK_OUTPUT, "Test string: '%s' has %d characters", string2, string2Len);
   BeaconPrintf(CALLBACK_OUTPUT, "Test string: '%s' string length was not extracted.", string3);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconDataStrings !!!!\n\n");
} 

