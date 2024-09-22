#include "disk.h"

EFI_GUID gEfiBlockIoProtocolGuid = EFI_BLOCK_IO_PROTOCOL_GUID;

EFI_STATUS DiskRead(DISK *disk, EFI_LBA lba, EFI_UINTN size, VOID *buffer) {
    return disk->BlockIo->ReadBlocks(disk->BlockIo, disk->BlockIo->Media->MediaId, lba, size, buffer);
}

EFI_STATUS DiskWrite(DISK *disk, EFI_LBA lba, EFI_UINTN size, VOID *buffer) {
    return disk->BlockIo->WriteBlocks(disk->BlockIo, disk->BlockIo->Media->MediaId, lba, size, buffer);
}

EFI_STATUS DiskOpen(DISK *disk) {
    
    if (disk->BlockIo->Media->ReadOnly == EFI_TRUE) {
        output_string("Disk is read only aborting the boot process!\r\n");
        return EFI_WRITE_PROTECTED;
    }
    EFI_STATUS status;

    status = ST->BootServices->HandleProtocol(IH, &gEfiBlockIoProtocolGuid, (VOID**)&disk->BlockIo);
    if (EFI_ERROR(status)) {
        return status;
    }

    disk->Handle = IH;
    disk->Status = EFI_SUCCESS;

    return EFI_SUCCESS;
}