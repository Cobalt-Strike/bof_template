#include <windows.h> 
#include "../../beacon.h"

WINBASEAPI void * WINAPI KERNEL32$HeapAlloc (HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
WINBASEAPI void * WINAPI KERNEL32$HeapFree (HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);
WINBASEAPI HANDLE WINAPI KERNEL32$GetProcessHeap();

#define HeapAlloc       KERNEL32$HeapAlloc
#define HeapFree        KERNEL32$HeapFree
#define GetProcessHeap  KERNEL32$GetProcessHeap

typedef struct {
   char *entry1;
   char *entry2;
} MYDATA, *PMYDATA;


void fill(char * buffer, char c, int len) {
   if (buffer == NULL || len == 0) {
      return;
   }

   while(len--) {
      buffer[len] = c;
   }
}

void cleanup_mydata(formatp *buffer, PMYDATA data) {
   if (data == NULL) {
      return;
   }

   BeaconFormatPrintf(buffer, "HeapFree entry1 at %p\n", data->entry1);
   fill(data->entry1, '\0', 9);
   HeapFree(GetProcessHeap(), 0, data->entry1);
   data->entry1 = NULL;

   BeaconFormatPrintf(buffer, "HeapFree entry2 at %p\n", data->entry2);
   fill(data->entry2, '\0', 9);
   HeapFree(GetProcessHeap(), 0, data->entry2);
   data->entry2 = NULL;

   BeaconFormatPrintf(buffer, "HeapFree data at %p\n", data);
   HeapFree(GetProcessHeap(), 0, data);
}

/* entry point */
void go(char * args, int alen) {
   datap parser;
   formatp buffer;
   char * state;
   char * key;
   PMYDATA data = NULL;

   /* parse the inputs (string) */
   BeaconDataParse(&parser, args, alen);
   state = BeaconDataExtract(&parser, NULL);
   key = BeaconDataExtract(&parser, NULL);

   if (state == NULL) {
      BeaconPrintf(CALLBACK_ERROR, "The state is not set");
      return; 
   }

   /* Allocate space for formatted output buffer */
   BeaconFormatAlloc(&buffer, 4096);

   BeaconFormatPrintf(&buffer, "Running the cs_key_value BOF with state: %s\n", state);

   if (state[0] == 'i') {
      /* Allocate memory for MYDATA */
      data = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));
      data->entry1 = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 10);
      data->entry2 = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 10);
      
      /* initialize the data */
      fill(data->entry1, 'a', 9);
      fill(data->entry2, 'b', 9);

      /* save the data to beacon's key/value store */
      if (BeaconAddValue(key, data)) {
         BeaconFormatPrintf(&buffer, "Added key: %s at %p\n", key, data);
      } else {
         BeaconFormatPrintf(&buffer, "Unable to add key: %s at %p\n", key, data);
         cleanup_mydata(&buffer, data);
      }
   }
   else if (state[0] == 'c') {
      /* Get the data from beacon's key/value store */
      data = BeaconGetValue(key);
      if (data == NULL) {
         BeaconFormatPrintf(&buffer, "Unable to get value for key: %s\n", key);
      } else {
         BeaconFormatPrintf(&buffer, "Found key: %s at %p\n", key, data);
         BeaconFormatPrintf(&buffer, "entry1: %s\n", data->entry1);
         BeaconFormatPrintf(&buffer, "entry2: %s\n", data->entry2);

         /* Change the data */
         char c1 = data->entry1[0] + 1;
         char c2 = data->entry2[0] + 1;
         fill(data->entry1, c1, 5);
         fill(data->entry2, c2, 5);
      } 
      
   }
   else if (state[0] == 'f') {
      /* Get the data to clean up the memory */
      data = BeaconGetValue(key);
      if (data != NULL) {
         BeaconFormatPrintf(&buffer, "Found key: %s at %p\n", key, data);
         cleanup_mydata(&buffer, data);
      }

      /* Remove the key from beacon's key/value store */
      if (BeaconRemoveValue(key)) {
         BeaconFormatPrintf(&buffer, "Removed key: %s\n", key);
      } else {
         BeaconFormatPrintf(&buffer, "Unable to remove key: %s\n", key);
      }
   }
   else {
      BeaconPrintf(CALLBACK_ERROR, "Unknown state");
   }

   /* Send the buffer of information with */
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, NULL));

   /* Cleanup */
   BeaconFormatFree(&buffer);
}
