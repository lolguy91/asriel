#ifndef DISK_H
#define DISK_H

#include <efi/efi.h>
#include <common.h>

typedef struct {
    EFI_BLOCK_IO_PROTOCOL *BlockIo;
    EFI_HANDLE            Handle;
    EFI_STATUS            Status;
} DISK;

EFI_STATUS DiskRead(DISK *disk, EFI_LBA lba, EFI_UINTN size, VOID *buffer);
EFI_STATUS DiskWrite(DISK *disk, EFI_LBA lba, EFI_UINTN size, VOID *buffer);
EFI_STATUS DiskOpen(DISK *disk);

#endif // DISK_H
