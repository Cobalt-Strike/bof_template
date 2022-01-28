#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 


void go(char * args, int alen) { 
   datap  parser;
   char * userString;
   int    userStringLen = 0;

   /* Parse the parameters */
   BeaconDataParse(&parser, args, alen);
   userString = BeaconDataExtract(&parser, &userStringLen);

   BeaconOutput(CALLBACK_OUTPUT, "!!!! Start testBeaconOutput !!!!", 32);

   BeaconOutput(CALLBACK_OUTPUT, "Next three outputs represent the user supplied string using the three output types", 84); 
   BeaconOutput(CALLBACK_OUTPUT, userString, userStringLen);
   BeaconOutput(CALLBACK_OUTPUT_OEM, userString, userStringLen);
   BeaconOutput(CALLBACK_OUTPUT_UTF8, userString, userStringLen);

   /* Hello world string in Japanese, CALLBACK_OUTPUT_UTF8 is the correct ouput type */
   BeaconOutput(CALLBACK_OUTPUT, "Next three outputs represent 'Hello world' in Japanese using the 3 output types", 81); 
   BeaconOutput(CALLBACK_OUTPUT, "こんにちは世界", 22);
   BeaconOutput(CALLBACK_OUTPUT_OEM, "こんにちは世界", 22);
   BeaconOutput(CALLBACK_OUTPUT_UTF8, "こんにちは世界", 22);

   /* Examples using the CALLBACK_ERROR type */
   BeaconOutput(CALLBACK_ERROR, userString, userStringLen);
   BeaconOutput(CALLBACK_ERROR, "hard coded error string", 23);

   BeaconOutput(CALLBACK_OUTPUT, "!!!! End testBeaconOutput !!!!\n\n", 32);
} 

