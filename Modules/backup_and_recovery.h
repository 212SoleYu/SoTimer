
// this file use nv.h and dma to backup the whole stack and the register into FRAM, and recovery.

#include<Modules/driver_include.h>

#ifndef _DRIVE_BACKUP_AND_RECOVERY_H
#define _DRIVE_BACKUP_AND_RECOVERY_H
// backup to backup all the stack context into NVM
void backup();

// recovery the register and the stack
void recovery();


#endif
