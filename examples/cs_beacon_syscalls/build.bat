set PLAT="x86"
IF "%Platform%"=="x64" set PLAT="x64"
set VERSION="WIN32"
IF "%Platform%"=="x64" set VERSION="WIN64"

cl.exe /D %VERSION% /c /GS- cs_beacon_syscalls_info.c /Focs_beacon_syscalls_info.%PLAT%.o
cl.exe /D %VERSION% /c /GS- cs_beacon_syscalls_test.c /Focs_beacon_syscalls_test.%PLAT%.o
