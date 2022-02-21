#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 

void go(char * args, int alen) { 
   datap  parser;
   char * userString;
   int    userNum;
   int    userStringLen = 0;

   /* Parse the parameters */
   BeaconDataParse(&parser, args, alen);
   userString = BeaconDataExtract(&parser, &userStringLen);
   userNum = BeaconDataInt(&parser);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! testBeaconPrintf !!!!");

   BeaconPrintf(CALLBACK_OUTPUT, "Arguments: %s, %d", userString, userNum);
   BeaconPrintf(CALLBACK_OUTPUT, "Some text string with no line feed");
   BeaconPrintf(CALLBACK_OUTPUT, "Another text string with a line feed\n");

   /* Hello world string in Japanese, CALLBACK_OUTPUT_UTF8 is the correct ouput type */
   BeaconPrintf(CALLBACK_OUTPUT, "Next three outputs represent 'Hello world' in Japanese using the 3 output types");
   BeaconPrintf(CALLBACK_OUTPUT, "こんにちは世界");
   BeaconPrintf(CALLBACK_OUTPUT_OEM, "こんにちは世界");
   BeaconPrintf(CALLBACK_OUTPUT_UTF8, "こんにちは世界");

   BeaconPrintf(CALLBACK_ERROR, "Error: %s, %d", userString, userNum);
   BeaconPrintf(CALLBACK_ERROR, "hard coded error string");

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconPrintf !!!!\n\n");
} 

