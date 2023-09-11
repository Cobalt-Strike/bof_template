#include <windows.h>
#include "../../beacon.h"

void LoopExampleWithFormatting() {
   // Create the new buffer pointer
   formatp buffer;

   // Allocate memory to hold the formatted data
   BeaconFormatAlloc(&buffer, 1024);

   for(int i = 0; i < 5; i++) {
      // Instead of printing, we will now fill the buffer - notice the new line char
      BeaconFormatPrintf(&buffer, "counter is currently at %d\n", i); 
   }

   // Now that we have the buffer filled up,  let's print it out
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, NULL));

   // Clean up
   BeaconFormatFree(&buffer);
}

void LoopExample() {
   for(int i = 0; i < 5; i++) {
      BeaconPrintf(CALLBACK_OUTPUT, "counter is currently at %d", i); 
   }
}

void go_format(char *args, int len) {
   LoopExampleWithFormatting();
}

void go(char *args, int len) {
   LoopExample();
}

