#include <windows.h>
#include "../../beacon.h"

//WINBASEAPI WINBOOL WINAPI KERNEL32$ReadProcessMemory (HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
WINBASEAPI void *__cdecl MSVCRT$malloc(size_t _Size);
WINBASEAPI void __cdecl MSVCRT$free(void *_Memory);

#define malloc MSVCRT$malloc
#define free   MSVCRT$free

HMODULE GetModHandle(LPCSTR module) {
   HMODULE hModule = GetModuleHandleA(module);
   return hModule ? hModule : LoadLibraryA(module);
}

LPVOID GetMemptr(LPCSTR module, LPCSTR function) {
   
   HMODULE hModule = GetModHandle(module);
   LPVOID memptr = GetProcAddress(hModule, function);
   return memptr ? memptr : NULL;
}

void ReadVirtualMemory(LPCSTR module, LPCSTR function, int len, int format) {
   formatp buffer;
   BYTE *readBuffer;
   SIZE_T bytesRead = 0;
   LPVOID memptr = GetMemptr(module, function);

   if (!memptr) {
      BeaconPrintf(CALLBACK_ERROR, "no memptr found");
      return;
   }

   BeaconFormatAlloc(&buffer, 1024);


   readBuffer = malloc(len);
#if 0
   KERNEL32$ReadProcessMemory((HANDLE) -1, memptr, readBuffer, len, &bytesRead);
#else
   BeaconReadProcessMemory((HANDLE) -1, memptr, readBuffer, len, &bytesRead);
#endif

   BeaconFormatPrintf(&buffer, "Showing the first %i opcodes of %s!%s\n", len, module, function);
   for (SIZE_T i = 0; i < bytesRead; ++i) {
      if (format) {
         BeaconFormatPrintf(&buffer, "\\x%02X", readBuffer[i]); 
      } else {
         BeaconFormatPrintf(&buffer, "%02X", readBuffer[i]); 
      }
   }

   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, NULL));
  
   BeaconFormatFree(&buffer);
   free(readBuffer);
}

void go(char *args, int argLen) {
   char * module;
   char * function;
   int len;
   int format;
   datap parser;

   BeaconDataParse(&parser, args, argLen);
   module = BeaconDataExtract(&parser, NULL);
   function = BeaconDataExtract(&parser, NULL);
   len = BeaconDataInt(&parser);
   format = BeaconDataInt(&parser);

   ReadVirtualMemory(module, function, len, format);
}

