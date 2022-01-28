#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 


void go(char * args, int alen) { 
   datap   parser;
   formatp buffer; 
   char *  userString;
   int     userStringLen = 0;
   int     userInt;
   char *  bufferString;
   int     bufferStringLen;

   /* Parse the parameters */
   BeaconDataParse(&parser, args, alen);
   userString = BeaconDataExtract(&parser, &userStringLen);
   userInt    = BeaconDataInt(&parser);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! Start testBeaconFormat !!!!");

   /* Allocate space for our buffer */
   BeaconFormatAlloc(&buffer, 1024);

   /* Build up a buffer of information */
   BeaconFormatPrintf(&buffer, "Start of the formated buffer:\n");
   BeaconFormatPrintf(&buffer, "The user passed in the integer: %d\n", userInt); 
   BeaconFormatPrintf(&buffer, "The user passed in the string: ");
   BeaconFormatAppend(&buffer, userString, userStringLen);
   BeaconFormatPrintf(&buffer, "\nAppending some test integer: ");
   BeaconFormatInt(&buffer, 2022);

   /* Send the buffer of information with BeaconPrintf */
   /* Note: BecaonFormatToString has a defect and requires the size parameter to be set */
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, &bufferStringLen));
   
   /* Reset the buffer and format the information differently */
   BeaconFormatReset(&buffer);
   BeaconFormatPrintf(&buffer, "Format buffer has been reset\n");
   BeaconFormatPrintf(&buffer, "Input String (%d): %s Input Integer: %d\n", userStringLen, userString, userInt);
   
   /* Send the buffer of information with BeaconOutput */
   bufferString = BeaconFormatToString(&buffer, &bufferStringLen);
   BeaconOutput(CALLBACK_OUTPUT, bufferString, bufferStringLen);
   

   /* Cleanup */
   BeaconFormatFree(&buffer);

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconFormat !!!!\n\n");
} 

