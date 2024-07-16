#include <windows.h> 
#include "../../beacon.h"


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

static const char * getPurpose(ALLOCATED_MEMORY_PURPOSE purpose) {
	if (purpose == PURPOSE_EMPTY)
		return "PURPOSE_EMPTY";
	if (purpose == PURPOSE_GENERIC_BUFFER)
		return "PURPOSE_GENERIC_BUFFER";
	if (purpose == PURPOSE_BEACON_MEMORY)
		return "PURPOSE_BEACON_MEMORY";
	if (purpose == PURPOSE_SLEEPMASK_MEMORY)
		return "PURPOSE_SLEEPMASK_MEMORY";
	if (purpose == PURPOSE_BOF_MEMORY)
		return "PURPOSE_BOF_MEMORY";
	if (purpose == PURPOSE_USER_DEFINED_MEMORY)
		return "PURPOSE_USER_DEFINED_MEMORY";

	return "PURPOSE_UNKNOWN";
}

static const char * getLabel(ALLOCATED_MEMORY_LABEL label) {
	if (label == LABEL_EMPTY)
		return "LABEL_EMPTY";
	if (label == LABEL_BUFFER)
		return "LABEL_BUFFER";
	if (label == LABEL_PEHEADER)
		return "LABEL_PEHEADER";
	if (label == LABEL_TEXT)
		return "LABEL_TEXT";
	if (label == LABEL_RDATA)
		return "LABEL_RDATA";
	if (label == LABEL_DATA)
		return "LABEL_DATA";
	if (label == LABEL_PDATA)
		return "LABEL_PDATA";
	if (label == LABEL_RELOC)
		return "LABEL_RELOC";
  	if (label == LABEL_USER_DEFINED)
		return "LABEL_USER_DEFINED";

	return "LABEL_UNKNOWN";
}

static void dump_allocated_memory_section(formatp *buffer, PALLOCATED_MEMORY_SECTION memorySection) {
	BeaconFormatPrintf(buffer, "\t\t\tLabel: %s\n", getLabel(memorySection->Label));
	BeaconFormatPrintf(buffer, "\t\t\tBaseAddress: %p\n", memorySection->BaseAddress);
	BeaconFormatPrintf(buffer, "\t\t\tVirtualSize: 0x%x (%lu)\n", memorySection->VirtualSize, memorySection->VirtualSize);
	BeaconFormatPrintf(buffer, "\t\t\tCurrenProtection: 0x%x\n", memorySection->CurrentProtect);
	BeaconFormatPrintf(buffer, "\t\t\tPreviousProtect: 0x%x\n", memorySection->PreviousProtect);
	BeaconFormatPrintf(buffer, "\t\t\tMaskSection: %s\n", memorySection->MaskSection ? "TRUE" : "FALSE");
}

static void dump_allocated_memory_cleanup_information(formatp *buffer, PALLOCATED_MEMORY_CLEANUP_INFORMATION cleanupInformation) {
	BeaconFormatPrintf(buffer, "\t\tCleanup Information:\n");
	BeaconFormatPrintf(buffer, "\t\t\tCleanup: %s\n", cleanupInformation->Cleanup ? "TRUE" : "FALSE");

	if (cleanupInformation->AllocationMethod == METHOD_HEAPALLOC) {
		BeaconFormatPrintf(buffer, "\t\t\tAllocationMethod: METHOD_HEAPALLOC\n");
		BeaconFormatPrintf(buffer, "\t\t\tAdditionalCleanupInformation: HeapHandle: %p\n", cleanupInformation->AdditionalCleanupInformation.HeapAllocInfo.HeapHandle);
		BeaconFormatPrintf(buffer, "\t\t\tAdditionalCleanupInformation: DestroyHeap: %s\n", cleanupInformation->AdditionalCleanupInformation.HeapAllocInfo.DestroyHeap? "TRUE" : "FALSE");
	}
	else if (cleanupInformation->AllocationMethod == METHOD_MODULESTOMP) {
		BeaconFormatPrintf(buffer, "\t\t\tAllocationMethod: METHOD_MODULESTOMP\n");
		BeaconFormatPrintf(buffer, "\t\t\tAdditionalCleanupInformation: ModuleHandle: %p\n", cleanupInformation->AdditionalCleanupInformation.ModuleStompInfo.ModuleHandle);
	}
	else {
		if (cleanupInformation->AllocationMethod == METHOD_VIRTUALALLOC) {
			BeaconFormatPrintf(buffer, "\t\t\tAllocationMethod: METHOD_VIRTUALALLOC\n");
		}
		else if (cleanupInformation->AllocationMethod == METHOD_NTMAPVIEW) {
			BeaconFormatPrintf(buffer, "\t\t\tAllocationMethod: METHOD_NTMAPVIEW\n");
		}
		else if (cleanupInformation->AllocationMethod == METHOD_UNKNOWN) {
			BeaconFormatPrintf(buffer, "\t\t\tAllocationMethod: METHOD_UNKNOWN\n");
		}
		else {
			BeaconFormatPrintf(buffer, "\t\t\tAllocationMethod: METHOD_USER_DEFINED (%d)\n", cleanupInformation->AllocationMethod);
		}
		BeaconFormatPrintf(buffer, "\t\t\tAdditionalCleanupInformation: NONE\n");
	}
}

static void dump_allocated_memory_region(formatp * buffer, PALLOCATED_MEMORY_REGION memoryRegion) {
	int i = 0;

	BeaconFormatPrintf(buffer, "\t\tPurpose: %s\n", getPurpose(memoryRegion->Purpose));
	BeaconFormatPrintf(buffer, "\t\tBaseAddress: %p\n", memoryRegion->AllocationBase);
	BeaconFormatPrintf(buffer, "\t\tRegionSize: 0x%x (%lu)\n", memoryRegion->RegionSize, memoryRegion->RegionSize);
	BeaconFormatPrintf(buffer, "\t\tType: 0x%x\n", memoryRegion->Type);

	/* loop through the Sections */
	for (i = 0; i < sizeof(memoryRegion->Sections) / sizeof(ALLOCATED_MEMORY_SECTION); ++i) {
		if (memoryRegion->Sections[i].Label == LABEL_EMPTY) {
			continue;
		}
		BeaconFormatPrintf(buffer, "\t\tSection[%d]\n", i);
		dump_allocated_memory_section(buffer, &memoryRegion->Sections[i]);
	}

	dump_allocated_memory_cleanup_information(buffer, &memoryRegion->CleanupInformation);
}

void dump_allocated_memory(formatp * buffer, PBEACON_INFO info) {
   int counted_entries = 0;
   int total_entries = sizeof(info->allocatedMemory.AllocatedMemoryRegions) / sizeof(ALLOCATED_MEMORY_REGION);

   BeaconFormatPrintf(buffer, "\nAllocated memory:\n");
   for (int i = 0; i < total_entries; ++i) {
      PALLOCATED_MEMORY_REGION memoryRegion = &(info->allocatedMemory.AllocatedMemoryRegions[i]);
      if (memoryRegion->Purpose != PURPOSE_EMPTY) {
         ++counted_entries;
         BeaconFormatPrintf(buffer, "\tAllocated memory region[%d]:\n", i);
         dump_allocated_memory_region(buffer, memoryRegion);
      }
   }
   BeaconFormatPrintf(buffer, "\nAllocated memory structure set %d entries out of %d available entries\n",
      counted_entries, total_entries);
}

/* entry point */
void go(char * args, int alen) {
   formatp buffer;
   int size = 0;
   BEACON_INFO info = { 0 };
   char *userData = NULL;

   /* Call beacon api to get the information */
   info.version = 0x041000;
   if (!BeaconInformation(&info)) {
      BeaconPrintf(CALLBACK_ERROR, "BeaconInformation failed: unhandled version: 0x%x\n", info.version);
      return;   
   }

   /* Allocate space for formatted output buffer */
   BeaconFormatAlloc(&buffer, 16 * 1024);

   /* Generate the output */
   BeaconFormatPrintf(&buffer, "Beacon Information:\n");
   BeaconFormatPrintf(&buffer, "\tBase address: %p\n", info.beacon_ptr);
   dump_allocated_memory(&buffer, &info);
   dump_heap_records(&buffer, &info);
   dump_mask(&buffer, &info);
   BeaconFormatPrintf(&buffer, "\nSleep Mask Information:\n");
   BeaconFormatPrintf(&buffer, "\tBase address: %p\n", info.sleep_mask_ptr);
   BeaconFormatPrintf(&buffer, "\tText size   : %lu\n", info.sleep_mask_text_size);
   BeaconFormatPrintf(&buffer, "\tTotal size  : %lu\n", info.sleep_mask_total_size);

   /* Send the buffer of information with */
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, &size));

   /* Cleanup */
   BeaconFormatFree(&buffer);
} 
