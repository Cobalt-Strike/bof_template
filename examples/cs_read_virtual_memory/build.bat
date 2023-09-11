set PLAT="x86"
IF "%Platform%"=="x64" set PLAT="x64"
set VERSION="WIN32"
IF "%Platform%"=="x64" set VERSION="WIN64"

cl.exe /D %VERSION% /c /GS- cs_read_virtual_memory.c /Focs_read_virtual_memory.%PLAT%.o




