#include <windows.h> 
#include "../../beacon.h"


void dump_sections(formatp * buffer, BEACON_INFO * info) {
   DWORD * index;
   DWORD a, b;
   DWORD endText = 0;
   int hasHeader = 0;
   int hasText = 0;

   if (info->sections == NULL) {
      BeaconFormatPrintf(buffer, "\tNo Sections (stage.sleep_mask = false)\n");
      return;
   }

   /* walk our sections */
   BeaconFormatPrintf(buffer, "\tSections:\n");
   index = info->sections;
   while (TRUE) {
      a = *index; b = *(index + 1);
      index += 2;
      if (a == 0 && b == 0) {
         break;
      }
      if (a == 0 && b == 0x1000) {
         hasHeader = 1;
      }
      if (a == 0x1000) {
         hasText = 1;
      }
      if (a > 0x1000 && hasText == 0 && endText == 0) {
         endText = a;
      }
      BeaconFormatPrintf(buffer, "\t\tSection: sOff 0x%-8x - eOff 0x%-8x : sAddr %p - eAddr %p\n", a, b,
         info->beacon_ptr + a, info->beacon_ptr + b);
   }

   if (hasHeader == 0 || hasText == 0) {
      BeaconFormatPrintf(buffer, "\n\tSection additional info:\n");
   }
   if (hasHeader == 0) {
      BeaconFormatPrintf(buffer, "\t\tHeader section not in sections list (stage.obfuscate = true)\n");
      BeaconFormatPrintf(buffer, "\t\tAdjusted Beacon Base address: %p\n", info->beacon_ptr + 0x1000);
   }
   if (hasText == 0) {
      BeaconFormatPrintf(buffer, "\t\tText section not in sections list (stage.userwx = false)\n");
      BeaconFormatPrintf(buffer, "\t\tText at: sOff 0x%-8x - eOff 0x%-8x : sAddr %p - eAddr %p\n", 0x1000, endText,
         info->beacon_ptr + 0x1000, info->beacon_ptr + endText);
   }
}

void dump_mask(formatp * buffer, BEACON_INFO * info) {
    char hex_array[] = "0123456789abcdef";
    char mask_hex[MASK_SIZE * 3 + 1] = { 0 };

    for (int i = 0, j = 0; i < MASK_SIZE; ++i, ++j) {
            int v = info->mask[i] & 0xFF;
            mask_hex[j * 3] = hex_array[(unsigned int) (v >> 4)];
            mask_hex[j * 3 + 1] = hex_array[v & 0x0F];
            mask_hex[j * 3 + 2] = ' ';
    }
    BeaconFormatPrintf(buffer, "\n\tMask: %s\n", mask_hex);
}

void dump_heap_records(formatp * buffer, BEACON_INFO * info) {

   if (info->heap_records == NULL) {
      BeaconFormatPrintf(buffer, "\n\tNo heap records\n");
      return;
   }

   /* walk the heap records */
   BeaconFormatPrintf(buffer, "\n\tHeap records:\n");
   for (int i = 0; info->heap_records[i].ptr != NULL; ++i) {
      BeaconFormatPrintf(buffer, "\t\tRecord[%2d]: Address: %p Size %8lu\n",
          i, info->heap_records[i].ptr, info->heap_records[i].size);
   }
}

/* entry point */
void go(char * args, int alen) {
   formatp buffer;
   BEACON_INFO info;

   /* Allocate space for formatted output buffer */
   BeaconFormatAlloc(&buffer, 4096);

   /* Call beacon api to get the information */
   BeaconInformation(&info);

   /* Generate the output */
   BeaconFormatPrintf(&buffer, "Beacon Information:\n");
   BeaconFormatPrintf(&buffer, "\tBase address: %p\n", info.beacon_ptr);
   dump_sections(&buffer, &info);
   dump_heap_records(&buffer, &info);
   dump_mask(&buffer, &info);
   BeaconFormatPrintf(&buffer, "\nSleep Mask Information:\n");
   BeaconFormatPrintf(&buffer, "\tBase address: %p\n", info.sleep_mask_ptr);
   BeaconFormatPrintf(&buffer, "\tText size   : %lu\n", info.sleep_mask_text_size);
   BeaconFormatPrintf(&buffer, "\tTotal size  : %lu\n", info.sleep_mask_total_size);

   /* Send the buffer of information with */
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, NULL));

   /* Cleanup */
   BeaconFormatFree(&buffer);
} 
