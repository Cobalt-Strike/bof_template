#include <windows.h>
#include "../../beacon.h"

void go(char * args, int alen) {
   BeaconPrintf(CALLBACK_OUTPUT, "Hello World: %s", args);
}

