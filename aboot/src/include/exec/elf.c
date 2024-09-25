#include "elf.h"
#include <stddef.h>
#include <common.h>
#include <libc/string.h>

int elf_validate_header(Elf32_Ehdr *header)
{
	if (header == NULL) {
		output_string("ERROR: elf_validate_header() called with NULL argument!\r\n");
		return -1;
	}

	if (header->e_ident[EI_MAG0] != ELFMAG0 ||
			header->e_ident[EI_MAG1] != ELFMAG1 ||
			header->e_ident[EI_MAG2] != ELFMAG2 ||
			header->e_ident[EI_MAG3] != ELFMAG3) {
		output_string("ERROR: Invalid ELF magic value!\r\n");
		return -1;
	}

	if (header->e_ident[EI_DATA] != ELFDATA2LSB) {
		output_string("ERROR: ELF is not little endian!\r\n");
		return -1;
	}

	if (header->e_type != ET_EXEC) {
		output_string("ERROR: ELF file is not an executable!\r\n");
		return -1;
	}

	if (header->e_version != EV_CURRENT) {
		output_string("ERROR: ELF version is not EV_CURRENT!\r\n");
		return -1;
	}

	if (header->e_machine != EM_386 &&
		header->e_machine != EM_X86_64 &&
		header->e_machine != EM_ARM &&
		header->e_machine != EM_AARCH64 &&
		header->e_machine != EM_PPC &&
		header->e_machine != EM_PPC64) {
		output_string("ERROR: Unsupported machine specified!\r\n");
		return -1;
	}

	return 0;
}

bool elf_load(void *kernel, void **entryp)
{
	Elf32_Ehdr *header32 = (Elf32_Ehdr *)kernel;
	Elf64_Ehdr *header64 = (Elf64_Ehdr *)kernel;

	if (elf_validate_header(header32) != 0) {
		output_string("ERROR: Invalid ELF header!\r\n");
		return false;
	}

	if (header32->e_machine == EM_386 ||
		header32->e_machine == EM_ARM ||
		header32->e_machine == EM_PPC) {
		if (header32->e_phnum <= 0) {
			output_string("ERROR: No loadable ELF segments found.\r\n");
			return false;
		}

		*entryp = (void *)(uintptr_t)header32->e_entry;

		Elf32_Phdr *phdrs32 = (Elf32_Phdr *)(kernel + header32->e_phoff);
		for (uint16_t i = 0; i < header32->e_phnum; i++) {
			Elf32_Phdr *phdr32 = (Elf32_Phdr *)phdrs32;
			if (phdr32->p_type == PT_LOAD) {
				void *file_segment = (void *)((uintptr_t)kernel + phdr32->p_offset);
				void *memory_segment = (void *)(uintptr_t)phdr32->p_paddr;

				memcpy(memory_segment, file_segment, phdr32->p_filesz);

				uint8_t *extra_zeroes = (uint8_t *)memory_segment + phdr32->p_filesz;
				uint64_t extra_zeroes_count = phdr32->p_memsz - phdr32->p_filesz;

				if (extra_zeroes_count > 0) {
					memset(extra_zeroes, 0x00, extra_zeroes_count);
				}
			}

			phdrs32 = (Elf32_Phdr *)((uint8_t*)phdrs32 + header32->e_phentsize);
		}
	} else {
		if (header64->e_phnum <= 0) {
			output_string("ERROR: No loadable ELF segments found.\r\n");
			return false;
		}

		*entryp = (void *)header64->e_entry;

		Elf64_Phdr *phdrs64 = (Elf64_Phdr *)(kernel + header64->e_phoff);
		for (uint16_t i = 0; i < header64->e_phnum; i++) {
			Elf64_Phdr *phdr64 = (Elf64_Phdr *)phdrs64;
			if (phdr64->p_type == PT_LOAD) {
				void *file_segment = (void *)((uintptr_t)kernel + phdr64->p_offset);
				void *memory_segment = (void *)(uintptr_t)phdr64->p_paddr;
				EFI_PHYSICAL_ADDRESS base;

				if (phdr64->p_memsz == 0) {
					continue;
				}

				memcpy(memory_segment, file_segment, phdr64->p_filesz);

				if (phdr64->p_memsz - phdr64->p_filesz > 0) {
					memset((void *)(memory_segment + phdr64->p_filesz), 0x0, phdr64->p_memsz - phdr64->p_filesz);
				}
			}

			phdrs64 = (Elf64_Phdr *)((uint8_t *)phdrs64 + header64->e_phentsize);
		}

	}

	output_string("Loaded ELF kernel file\r\n");

	return true;
}