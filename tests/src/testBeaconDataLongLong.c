#include <windows.h> 
#include <stdio.h>
#include "beacon.h" 

WINBASEAPI long long __cdecl MSVCRT$_atoi64(CONST CHAR *);
WINBASEAPI WINBOOL WINAPI SHLWAPI$StrToInt64ExA(LPCSTR, DWORD, LONGLONG *);

void go(char * args, int alen) { 
   datap  parser;
   char   *userString;
   int    userStringLen;
   int    userInt;
   long long testLongLong;
   long long testFromUserString = 0;

   BeaconDataParse(&parser, args, alen);
   userString = BeaconDataExtract(&parser, &userStringLen);
   userInt = BeaconDataInt(&parser);

   /* Take the userInt and do some calculations to set a long long value */
   /* This is not a good way to set a value with a data type long long.  */
   testLongLong = (long long) userInt * 6;

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! Start testBeaconDataLongLong !!!!");


   BeaconPrintf(CALLBACK_OUTPUT, "signed userInt         : %d", userInt);
   BeaconPrintf(CALLBACK_OUTPUT, "long long              : %lld = (%d * 6)", testLongLong, userInt);

   BeaconPrintf(CALLBACK_OUTPUT, "long long max          : %lld", LLONG_MAX);
   BeaconPrintf(CALLBACK_OUTPUT, "unsigned long long max : %llu", ULLONG_MAX);

   /* Convert the userString to a long long instead. */
   if (SHLWAPI$StrToInt64ExA(userString, 0x0, &testFromUserString)) {
      BeaconPrintf(CALLBACK_OUTPUT, "userString -> long long : %lld", testFromUserString);
      BeaconPrintf(CALLBACK_OUTPUT, "userString -> unsigned long long : %llu", (unsigned long long) testFromUserString);
   } else {
      BeaconPrintf(CALLBACK_ERROR, "userString '%s' is not a valid for conversion", userString);
   }

   BeaconPrintf(CALLBACK_OUTPUT, "!!!! End testBeaconDataLongLong !!!!\n\n");
} 

