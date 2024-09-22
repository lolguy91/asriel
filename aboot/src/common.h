#ifndef __COMMON_H__
#define __COMMON_H__

#include <efi/efi.h>
#include <stddef.h>
#include <include/malloc.h>
#include <include/io/sfs.h>

extern EFI_HANDLE IH;
extern EFI_SYSTEM_TABLE *ST;

void output_string(const char *ascii_str);
void __aboot_common(EFI_HANDLE IHs, EFI_SYSTEM_TABLE *STs);

#endif // __COMMON_H__