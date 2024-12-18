#include <windows.h> 
#include "../../beacon.h"

void dump_api_entry(formatp * buffer, char * name, PSYSCALL_API_ENTRY entry) {
   BeaconFormatPrintf(buffer, "   %41s: fnAddr: %p jmpAddr: %p sysnum: %lu\n",
      name,
      entry->fnAddr,
      entry->jmpAddr,
      entry->sysnum);
}

void dump_rtl_entry(formatp * buffer, char * name, PVOID entry) {
   BeaconFormatPrintf(buffer, "   %41s: fnAddr: %p\n", name, entry);
}

void dump_syscalls(formatp * buffer, PBEACON_SYSCALLS info) {
   if (info == NULL) {
      BeaconFormatPrintf(buffer, "Failed to get the beacon system call user data\n");
      return;
   }
   
   BeaconFormatPrintf(buffer, "System Calls:\n");
   dump_api_entry(buffer, "ntAllocateVirtualMemory", &info->syscalls.ntAllocateVirtualMemory);
   dump_api_entry(buffer, "ntProtectVirtualMemory", &info->syscalls.ntProtectVirtualMemory);
   dump_api_entry(buffer, "ntFreeVirtualMemory", &info->syscalls.ntFreeVirtualMemory);
   dump_api_entry(buffer, "ntGetContextThread", &info->syscalls.ntGetContextThread);
   dump_api_entry(buffer, "ntSetContextThread", &info->syscalls.ntSetContextThread);
   dump_api_entry(buffer, "ntResumeThread", &info->syscalls.ntResumeThread);
   dump_api_entry(buffer, "ntCreateThreadEx", &info->syscalls.ntCreateThreadEx);
   dump_api_entry(buffer, "ntOpenProcess", &info->syscalls.ntOpenProcess);
   dump_api_entry(buffer, "ntOpenThread", &info->syscalls.ntOpenThread);
   dump_api_entry(buffer, "ntClose", &info->syscalls.ntClose);
   dump_api_entry(buffer, "ntCreateSection", &info->syscalls.ntCreateSection);
   dump_api_entry(buffer, "ntMapViewOfSection", &info->syscalls.ntMapViewOfSection);
   dump_api_entry(buffer, "ntUnmapViewOfSection", &info->syscalls.ntUnmapViewOfSection);
   dump_api_entry(buffer, "ntQueryVirtualMemory", &info->syscalls.ntQueryVirtualMemory);
   dump_api_entry(buffer, "ntDuplicateObject", &info->syscalls.ntDuplicateObject);
   dump_api_entry(buffer, "ntReadVirtualMemory", &info->syscalls.ntReadVirtualMemory);
   dump_api_entry(buffer, "ntWriteVirtualMemory", &info->syscalls.ntWriteVirtualMemory);
   dump_api_entry(buffer, "ntReadFile", &info->syscalls.ntReadFile);
   dump_api_entry(buffer, "ntWriteFile", &info->syscalls.ntWriteFile);
   dump_api_entry(buffer, "ntCreateFile", &info->syscalls.ntCreateFile);

   BeaconFormatPrintf(buffer, "\nRun Time Library Functions:\n");
   dump_rtl_entry(buffer, "rtlDosPathNameToNtPathNameUWithStatusAddr", info->rtls.rtlDosPathNameToNtPathNameUWithStatusAddr);
   dump_rtl_entry(buffer, "rtlFreeHeapAddr", info->rtls.rtlFreeHeapAddr);
   dump_rtl_entry(buffer, "rtlGetProcessHeapAddr", info->rtls.rtlGetProcessHeapAddr);
}

/* entry point */
void go(char * args, int alen) {
   formatp buffer;
   int size = 0;
   BEACON_SYSCALLS info = {0};
   BOOL status;

   /* Allocate space for formatted output buffer */
   BeaconFormatAlloc(&buffer, 8 * 1024);

   /* Generate the output */
   status = BeaconGetSyscallInformation(&info, sizeof(BEACON_SYSCALLS), TRUE);
   if (status) {
      dump_syscalls(&buffer, &info);
   } else {
      BeaconFormatPrintf(&buffer, "Failed to get the system call information");
   }

   /* Send the buffer of information with */
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, &size));


   /* Cleanup */
   BeaconFormatFree(&buffer);
} 
