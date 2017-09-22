//  diskid32.cpp

//  for displaying the details of hard drives in a command window

//  06/11/00  Lynn McGuire  written with many contributions from others,
//                            IDE drives only under Windows NT/2K and 9X,
//                            maybe SCSI drives later
//  11/20/03  Lynn McGuire  added ReadPhysicalDriveInNTWithZeroRights
//  10/26/05  Lynn McGuire  fix the flipAndCodeBytes function


#define PRINTING_TO_CONSOLE_ALLOWED


#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <windows.h>
#include <winioctl.h>


	//  special include from the MS DDK
//#include "c:\win2kddk\inc\ddk\ntddk.h"
//#include "c:\win2kddk\inc\ntddstor.h"


#define  TITLE   "DiskId32"


//char HardDriveSerialNumber [1024];
//char HardDriveModelNumber [1024];
// Fetches the MAC address and prints it
DWORD GetMACaddress(void);
