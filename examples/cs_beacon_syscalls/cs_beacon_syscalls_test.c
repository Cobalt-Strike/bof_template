#include <windows.h> 
#include "../../beacon.h"

void systemCallTestMemory(formatp * outBuffer) {
   LPVOID buffer = NULL;
   SIZE_T size = 0x1000 * 2;
   DWORD oldProtection = 0;

   BeaconFormatPrintf(outBuffer, "Running System Call Test Memory\n");

   /* Allocate some memory to test with */
   buffer = BeaconVirtualAlloc(NULL, NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
   if (!buffer) {
      BeaconPrintf(CALLBACK_ERROR, "Failed to allocate %lu bytes of memory\n");
   }
   BeaconFormatPrintf(outBuffer, "Allocated memory at %p with protection set to %x\n", buffer, PAGE_READWRITE);

   /* Change protection on a page to be PAGE_EXECUTE_READ */
   if (!BeaconVirtualProtect(NULL, buffer, 0x1000, PAGE_EXECUTE_READ, &oldProtection)) {
      BeaconPrintf(CALLBACK_ERROR, "Failed to protect the page of memory\n");
   }
   BeaconFormatPrintf(outBuffer, "Protected memory at %p with protection set to %x previous protection %x\n", buffer, PAGE_EXECUTE_READ, oldProtection);

   /* Change protection on a page to be PAGE_EXECUTE_READ */
   if (!BeaconVirtualProtect(NULL, buffer, 0x1000, PAGE_EXECUTE_READWRITE, &oldProtection)) {
      BeaconPrintf(CALLBACK_ERROR, "Failed to protect the page of memory\n");
   }
   BeaconFormatPrintf(outBuffer, "Protected memory at %p with protection set to %x previous protection %x\n", buffer, PAGE_EXECUTE_READWRITE, oldProtection);

   /* Cleanup */
   if (!BeaconVirtualFree(buffer, 0, MEM_RELEASE)) {
      BeaconPrintf(CALLBACK_ERROR, "Failed to free the page of memory at %p\n", buffer);
   }
   BeaconFormatPrintf(outBuffer, "Released  memory at %p\n", buffer);
}

/* entry point */
void go(char * args, int alen) {
   formatp outBuffer;

   /* Allocate space for formatted output buffer */
   BeaconFormatAlloc(&outBuffer, 8 * 1024);

   BeaconPrintf(CALLBACK_OUTPUT, "Running Beacon System Calls Test Examples");

   systemCallTestMemory(&outBuffer);
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&outBuffer, NULL));
}
