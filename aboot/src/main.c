#include <efi/efi.h>
#include <common.h>

EFI_STATUS __aboot_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    __aboot_common(ImageHandle, SystemTable);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Couldnt finish shared entry function! Please reboot manually\r\n");
    for (;;) {asm ("hlt");}
}