#include <windows.h> 
#include "../../beacon.h" 

WINBASEAPI int WINAPI KERNEL32$lstrlenA (LPCSTR lpString);


int    gCount = 5;
int    gxCount = 0;
char * gBuffer = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwx";
char * gStrList[] = {"gggg", "5555", "ssss", "zzzz"};
int    gStrListSize = sizeof(gStrList) / sizeof(char *);

/* int gzCount; // not supported instead use int gzCount = 0; */

/* function to take the src and modify it by some offset and 
 * save it into the dest buffer.
 *
 * returns number of characters modified.
 */
int somefunc(char *src, char *dest, int destLen, int offset) {
   int i;
   for(i = 0; i < destLen && src[i] != 0x0; i++) {
      dest[i] = src[i] + offset;
   }
   ++gCount;
   return i;
}

/* function to print an array of strings.
 */
void printStrList(formatp *buffer, char *name, char **list, int count) {
   BeaconFormatPrintf(buffer, "listName: %s length: %d\n", name, count);
   for (int i = 0; i < count; i++) {
      BeaconFormatPrintf(buffer, "%s[%d] %s\n", name, i, list[i]);
   }
   gxCount++;
}

/* entry point */
void go(char * args, int alen) { 
   datap  parser;
   formatp buffer;
   char * str_arg;
   int    num_arg;
   int    result;
   char   stuff1[40] = "AAAAAAAABBBBBBBBCCCCCCCC";
   char   stuff2[20] = { 'Z', 'Z', 'Z', 'Z', 'Z', 'Y', 'Y', 'Y', 'Y', 'Y', 'X', 'X', 'X', 'X', 'X', 'W', 'W', 'W', 'W', 0x0 };
   char * lStrList[] = {"123", "456", "789", "abc"};
   int    lStrListSize = sizeof(lStrList) / sizeof(char *);
   

   BeaconDataParse(&parser, args, alen);
   str_arg = BeaconDataExtract(&parser, NULL);
   num_arg = BeaconDataInt(&parser);

   /* Allocate space for formatted output buffer */
   BeaconFormatAlloc(&buffer, 1024);

   BeaconFormatPrintf(&buffer, "gCount: %d gxGount: %d\n", gCount, gxCount);

   BeaconFormatPrintf(&buffer, "Args[0]: %s Args[1]: %d\n", str_arg, num_arg);

   ++gCount;
   ++gxCount;
   BeaconFormatPrintf(&buffer, "[stuff1 before] %d %s\n", sizeof(stuff1), stuff1);
   result = somefunc(str_arg, stuff1, sizeof(stuff1), 1);
   BeaconFormatPrintf(&buffer, "[stuff1 after ] %d %s\n", result, stuff1);
   BeaconFormatPrintf(&buffer, "gCount: %d gxGount: %d\n", gCount, gxCount);

   BeaconFormatPrintf(&buffer, "[stuff2 before] %d %s\n", sizeof(stuff2), stuff2);
   result = somefunc(stuff2, stuff2, sizeof(stuff2), 1);
   BeaconFormatPrintf(&buffer, "[stuff2 after ] %d %s\n", result, stuff2);

   printStrList(&buffer, "lStrList", lStrList, lStrListSize);
   printStrList(&buffer, "gStrList", gStrList, gStrListSize);

   ++gCount;
   BeaconFormatPrintf(&buffer, "[gBuffer before] %d %s\n", KERNEL32$lstrlenA(gBuffer), gBuffer);
   result = somefunc(stuff1, gBuffer, KERNEL32$lstrlenA(gBuffer), -1);
   BeaconFormatPrintf(&buffer, "[gBuffer after ] %d %s\n", result, gBuffer);
   BeaconFormatPrintf(&buffer, "gCount: %d gxGount: %d\n", gCount, gxCount);


   /* Send the buffer of information with BeaconPrintf */
   BeaconPrintf(CALLBACK_OUTPUT, "%s\n", BeaconFormatToString(&buffer, NULL));

} 

