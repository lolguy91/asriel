#ifndef EFI_PROTOCOLS_MEDIA_ACCESS_H
#define EFI_PROTOCOLS_MEDIA_ACCESS_H

#include "device_path.h"

////
// Load File Protocol
///

#define EFI_LOAD_FILE_PROTOCOL_GUID {0x56ec3091,0x954c,0x11d2, {0x8e,0x3f,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct _EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_LOAD_FILE)(
	IN EFI_LOAD_FILE_PROTOCOL *This,
	IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
	IN EFI_BOOLEAN BootPolicy,
	IN OUT EFI_UINTN *BufferSize,
	IN VOID *Buffer OPTIONAL
);

typedef struct _EFI_LOAD_FILE_PROTOCOL {
	EFI_LOAD_FILE LoadFile;
} EFI_LOAD_FILE_PROTOCOL;

////
// Load File 2 Protocol
///

#define EFI_LOAD_FILE2_PROTOCOL_GUID {0x4006c0c1,0xfcb3,0x403e, {0x99,0x6d,0x4a,0x6c,0x87,0x24,0xe0,0x6d}}

typedef EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE2_PROTOCOL;

////
// File Protocol
///

#define EFI_FILE_PROTOCOL_REVISION								0x00010000
#define EFI_FILE_PROTOCOL_REVISION2								0x00020000
#define EFI_FILE_PROTOCOL_LATEST_REVISION						EFI_FILE_PROTOCOL_REVISION2

#define EFI_FILE_INFO_GUID										{0x09576e92,0x6d3f,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_FILE_MODE_READ										0x0000000000000001
#define EFI_FILE_MODE_WRITE										0x0000000000000002
#define EFI_FILE_MODE_CREATE									0x8000000000000000

#define EFI_FILE_READ_ONLY										0x0000000000000001
#define EFI_FILE_HIDDEN											0x0000000000000002
#define EFI_FILE_SYSTEM											0x0000000000000004
#define EFI_FILE_RESERVED										0x0000000000000008
#define EFI_FILE_DIRECTORY										0x0000000000000010
#define EFI_FILE_ARCHIVE										0x0000000000000020
#define EFI_FILE_VALID_ATTR										0x0000000000000037

typedef struct _EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;

typedef struct {
	EFI_EVENT Event;
	EFI_STATUS Status;
	EFI_UINTN BufferSize;
	VOID *Buffer;
} EFI_FILE_IO_TOKEN;

typedef struct {
	EFI_UINT64 Size;
	EFI_UINT64 FileSize;
	EFI_UINT64 PhysicalSize;
	EFI_TIME CreateTime;
	EFI_TIME LastAccessTime;
	EFI_TIME ModificationTime;
	EFI_UINT64 Attribute;
	CHAR16 FileName[256];
} EFI_FILE_INFO;

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN)(
	IN EFI_FILE_PROTOCOL *This,
	OUT EFI_FILE_PROTOCOL **NewHandle,
	IN CHAR16 *FileName,
	IN EFI_UINT64 OpenMode,
	IN EFI_UINT64 Attributes
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_CLOSE)(
	IN EFI_FILE_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_DELETE)(
	IN EFI_FILE_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ)(
	IN EFI_FILE_PROTOCOL *This,
	IN OUT EFI_UINTN *BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE)(
	IN EFI_FILE_PROTOCOL *This,
	IN OUT EFI_UINTN *BufferSize,
	IN VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_POSITION)(
	IN EFI_FILE_PROTOCOL *This,
	OUT EFI_UINT64 Position
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_POSITION)(
	IN EFI_FILE_PROTOCOL *This,
	IN EFI_UINT64 Position
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_GET_INFO)(
	IN EFI_FILE_PROTOCOL *This,
	IN EFI_GUID *InformationType,
	IN OUT EFI_UINTN *BufferSize,
	OUT EFI_FILE_INFO *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_SET_INFO)(
	IN EFI_FILE_PROTOCOL *This,
	IN EFI_GUID *InformationType,
	IN EFI_UINTN BufferSize,
	IN EFI_FILE_INFO *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH)(
	IN EFI_FILE_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_OPEN_EX)(
	IN EFI_FILE_PROTOCOL *This,
	OUT EFI_FILE_PROTOCOL **NewHandle,
	IN CHAR16 *FileName,
	IN EFI_UINT64 OpenMode,
	IN EFI_UINT64 Attributes,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_READ_EX)(
	IN EFI_FILE_PROTOCOL *This,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_WRITE_EX)(
	IN EFI_FILE_PROTOCOL *This,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef
EFI_STATUS
(EFIAPI *EFI_FILE_FLUSH_EX)(
	IN EFI_FILE_PROTOCOL *This,
	IN OUT EFI_FILE_IO_TOKEN *Token
);

typedef struct _EFI_FILE_PROTOCOL {
	EFI_UINT64 Revision;

	EFI_FILE_OPEN Open;
	EFI_FILE_CLOSE Close;
	EFI_FILE_DELETE Delete;
	EFI_FILE_READ Read;
	EFI_FILE_WRITE Write;
	EFI_FILE_GET_POSITION GetPosition;
	EFI_FILE_SET_POSITION SetPosition;
	EFI_FILE_GET_INFO GetInfo;
	EFI_FILE_SET_INFO SetInfo;
	EFI_FILE_FLUSH Flush;

	// Added for revision 2
	EFI_FILE_OPEN_EX OpenEx;
	EFI_FILE_READ_EX ReadEx;
	EFI_FILE_WRITE_EX WriteEx;
	EFI_FILE_FLUSH_EX FlushEx;
} EFI_FILE_PROTOCOL;

////
// Simple File System Protocol
///

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID {0x0964e5b22,0x6459,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)(
	IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
	OUT EFI_FILE_PROTOCOL **Root
);

typedef struct _EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	EFI_UINT64 Revision;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

////
// Disk I/O Protocol
///

#define EFI_DISK_IO_PROTOCOL_GUID {0xce345171,0xba0b,0x11d2, {0x8e,0x4f,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_DISK_IO_PROTOCOL_REVISION 0x00010000

typedef struct _EFI_DISK_IO_PROTOCOL EFI_DISK_IO_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_READ)(
	IN EFI_DISK_IO_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_UINT64 Offset,
	IN EFI_UINTN BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_WRITE)(
	IN EFI_DISK_IO_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_UINT64 Offset,
	IN EFI_UINTN BufferSize,
	IN VOID *Buffer
);

typedef struct _EFI_DISK_IO_PROTOCOL {
	EFI_UINT64 Revision;
	EFI_DISK_READ ReadDisk;
	EFI_DISK_WRITE WriteDisk;
} EFI_DISK_IO_PROTOCOL;

////
// Disk I/O 2 Protocol
///

#define EFI_DISK_IO2_PROTOCOL_GUID {0x151c8eae,0x7f2c,0x472c, {0x9e,0x54,0x98,0x28,0x19,0x4f,0x6a,0x88}}

#define EFI_DISK_IO2_PROTOCOL_REVISION 0x00020000

typedef struct _EFI_DISK_IO2_PROTOCOL EFI_DISK_IO2_PROTOCOL;

typedef struct {
	EFI_EVENT Event;
	EFI_STATUS TransactionStatus;
} EFI_DISK_IO2_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_CANCEL_EX)(
	IN EFI_DISK_IO2_PROTOCOL *This
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_READ_EX)(
	IN EFI_DISK_IO2_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_UINT64 Offset,
	IN OUT EFI_DISK_IO2_TOKEN *Token,
	IN EFI_UINTN BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_WRITE_EX)(
	IN EFI_DISK_IO2_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_UINT64 Offset,
	IN OUT EFI_DISK_IO2_TOKEN *Token,
	IN EFI_UINTN BufferSize,
	IN VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_DISK_FLUSH_EX)(
	IN EFI_DISK_IO2_PROTOCOL *This,
	IN OUT EFI_DISK_IO2_TOKEN *Token
);

typedef struct _EFI_DISK_IO2_PROTOCOL {
	EFI_UINT64 Revision;
	EFI_DISK_CANCEL_EX Cancel;
	EFI_DISK_READ_EX ReadDiskEx;
	EFI_DISK_WRITE_EX WriteDiskEx;
	EFI_DISK_FLUSH_EX FlushDiskEx;
} EFI_DISK_IO2_PROTOCOL;

////
// Block I/O Protocol
///

#define EFI_BLOCK_IO_PROTOCOL_GUID {0x964e5b21,0x6459,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

#define EFI_BLOCK_IO_PROTOCOL_REVISION2 0x00020001
#define EFI_BLOCK_IO_PROTOCOL_REVISION3 ((2<<16) | (31))

typedef struct _EFI_BLOCK_IO_PROTOCOL EFI_BLOCK_IO_PROTOCOL;

typedef struct {
	EFI_UINT32 MediaId;
	EFI_BOOLEAN RemovableMedia;
	EFI_BOOLEAN MediaPresent;
	EFI_BOOLEAN LogicalPartition;
	EFI_BOOLEAN ReadOnly;
	EFI_BOOLEAN WriteCaching;
	EFI_UINT32 BlockSize;
	EFI_UINT32 IoAlign;
	EFI_LBA LastBlock;
	EFI_LBA LowestAlignedLba;
	EFI_UINT32 LogicalBlocksPerPhysicalBlock;
	EFI_UINT32 OptimalTransferLengthGranularity;
} EFI_BLOCK_IO_MEDIA;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET)(
	IN EFI_BLOCK_IO_PROTOCOL *This,
	IN EFI_BOOLEAN ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ)(
	IN EFI_BLOCK_IO_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_LBA LBA,
	IN EFI_UINTN BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE)(
	IN EFI_BLOCK_IO_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_LBA LBA,
	IN EFI_UINTN BufferSize,
	IN VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH)(
	IN EFI_BLOCK_IO_PROTOCOL *This
);

typedef struct _EFI_BLOCK_IO_PROTOCOL {
	EFI_UINT64 Revision;
	EFI_BLOCK_IO_MEDIA *Media;
	EFI_BLOCK_RESET Reset;
	EFI_BLOCK_READ ReadBlocks;
	EFI_BLOCK_WRITE WriteBlocks;
	EFI_BLOCK_FLUSH FlushBlocks;
} EFI_BLOCK_IO_PROTOCOL;

////
// Block I/O 2 Protocol
///

#define EFI_BLOCK_IO2_PROTOCOL_GUID {0xa77b2472,0xe282,0x4e9f, {0xa2,0x45,0xc2,0xc0,0xe2,0x7b,0xbc,0xc1}}

typedef struct _EFI_BLOCK_IO2_PROTOCOL EFI_BLOCK_IO2_PROTOCOL;

typedef struct {
	EFI_EVENT Event;
	EFI_STATUS TransactionStatus;
} EFI_BLOCK_IO2_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_RESET_EX)(
	IN EFI_BLOCK_IO2_PROTOCOL *This,
	IN EFI_BOOLEAN ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_READ_EX)(
	IN EFI_BLOCK_IO2_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_BLOCK_IO2_TOKEN *Token,
	IN EFI_UINTN BufferSize,
	OUT VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_WRITE_EX)(
	IN EFI_BLOCK_IO2_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_BLOCK_IO2_TOKEN *Token,
	IN EFI_UINTN BufferSize,
	IN VOID *Buffer
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_FLUSH_EX)(
	IN EFI_BLOCK_IO2_PROTOCOL *This,
	IN OUT EFI_BLOCK_IO2_TOKEN *Token
);

typedef struct _EFI_BLOCK_IO2_PROTOCOL {
	EFI_BLOCK_IO_MEDIA *Media;
	EFI_BLOCK_RESET_EX Reset;
	EFI_BLOCK_READ_EX ReadBlocksEx;
	EFI_BLOCK_WRITE_EX WriteBlocksEx;
	EFI_BLOCK_FLUSH_EX FlushBlocksEx;
} EFI_BLOCK_IO2_PROTOCOL;

////
// Inline Cryptographics Interface Protocol
///

#define EFI_BLOCK_IO_CRYPTO_PROTOCOL_GUID {0xa00490ba,0x3f1a,0x4b4c, {0xab,0x90,0x4f,0xa9,0x97,0x26,0xa1,0xe8}}

#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_XTS {0x2f87ba6a,0x5c04,0x4385,0xa7,0x80,0xf3,0xbf,0x78,0xa9,0x7b,0xec}
#define EFI_BLOCK_IO_CRYPTO_ALGO_GUID_AES_CBC_MICROSOFT_BITLOCKER {0x689e4c62,0x70bf,0x4cf3,0x88,0xbb,0x33,0xb3,0x18,0x26,0x86,0x70}

#define EFI_BLOCK_IO_CRYPTO_INDEX_ANY 0xFFFFFFFFFFFFFFFF

typedef struct _EFI_BLOCK_IO_CRYPTO_PROTOCOL EFI_BLOCK_IO_CRYPTO_PROTOCOL;

typedef struct {
	EFI_GUID Algorithm;
	EFI_UINT64 KeySize;
	EFI_UINT64 CryptoBlockSizeBitMask;
} EFI_BLOCK_IO_CRYPTO_CAPABILITY;

typedef struct {
	EFI_BOOLEAN Supported;
	EFI_UINT64 KeyCount;
	EFI_UINT64 CapabilityCount;
	EFI_BLOCK_IO_CRYPTO_CAPABILITY Capabilities [1];
} EFI_BLOCK_IO_CRYPTO_CAPABILITIES;

typedef struct {
	EFI_UINT64 Index;
	EFI_GUID KeyOwnerGuid;
	EFI_BLOCK_IO_CRYPTO_CAPABILITY Capability;
	VOID *CryptoKey;
} EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY;

typedef struct {
	EFI_UINT64 Index;
	EFI_GUID KeyOwnerGuid;
	EFI_BLOCK_IO_CRYPTO_CAPABILITY Capability;
} EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY;

typedef struct {
	EFI_UINT64 InputSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT;

typedef struct {
	EFI_BLOCK_IO_CRYPTO_IV_INPUT Header;
	EFI_UINT64 CryptoBlockNumber;
	EFI_UINT64 CryptoBlockByteSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT_AES_XTS;

typedef struct {
	EFI_BLOCK_IO_CRYPTO_IV_INPUT Header;
	EFI_UINT64 CryptoBlockByteOffset;
	EFI_UINT64 CryptoBlockByteSize;
} EFI_BLOCK_IO_CRYPTO_IV_INPUT_AES_CBC_MICROSOFT_BITLOCKER;

typedef struct {
	EFI_EVENT Event;
	EFI_STATUS TransactionStatus;
} EFI_BLOCK_IO_CRYPTO_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_IO_CRYPTO_RESET)(
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
	IN EFI_BOOLEAN ExtendedVerification
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_IO_CRYPTO_GET_CAPABILITIES)(
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
	OUT EFI_BLOCK_IO_CRYPTO_CAPABILITIES *Capabilities
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_IO_CRYPTO_SET_CONFIGURATION)(
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
	IN EFI_UINT64 ConfigurationCount,
	IN EFI_BLOCK_IO_CRYPTO_CONFIGURATION_TABLE_ENTRY *ConfigurationTable,
	OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY
	*ResultingTable OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_IO_CRYPTO_GET_CONFIGURATION)(
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
	IN EFI_UINT64 StartIndex,
	IN EFI_UINT64 ConfigurationCount,
	IN EFI_GUID *KeyOwnerGuid OPTIONAL,
	OUT EFI_BLOCK_IO_CRYPTO_RESPONSE_CONFIGURATION_ENTRY *ConfigurationTable
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_IO_CRYPTO_READ_EXTENDED)(
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token,
	IN EFI_UINT64 BufferSize,
	OUT VOID *Buffer,
	IN EFI_UINT64 *Index OPTIONAL,
	IN VOID *CryptoIvInput OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_IO_CRYPTO_WRITE_EXTENDED)(
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token,
	IN EFI_UINT64 BufferSize,
	IN VOID *Buffer,
	IN EFI_UINT64 *Index, OPTIONAL
	IN VOID *CryptoIvInput OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_BLOCK_IO_CRYPTO_FLUSH)(
	IN EFI_BLOCK_IO_CRYPTO_PROTOCOL *This,
	IN OUT EFI_BLOCK_IO_CRYPTO_TOKEN *Token
);

typedef struct _EFI_BLOCK_IO_CRYPTO_PROTOCOL {
	EFI_BLOCK_IO_MEDIA *Media;
	EFI_BLOCK_IO_CRYPTO_RESET Reset;
	EFI_BLOCK_IO_CRYPTO_GET_CAPABILITIES GetCapabilities;
	EFI_BLOCK_IO_CRYPTO_SET_CONFIGURATION SetConfiguration;
	EFI_BLOCK_IO_CRYPTO_GET_CONFIGURATION GetConfiguration;
	EFI_BLOCK_IO_CRYPTO_READ_EXTENDED ReadExtended;
	EFI_BLOCK_IO_CRYPTO_WRITE_EXTENDED WriteExtended;
	EFI_BLOCK_IO_CRYPTO_FLUSH FlushBlocks;
} EFI_BLOCK_IO_CRYPTO_PROTOCOL;

////
// Erase Block Protocol
///

#define EFI_ERASE_BLOCK_PROTOCOL_GUID {0x95a9a93e,0xa86e,0x4926, {0xaa,0xef,0x99,0x18,0xe7,0x72,0xd9,0x87}}

#define EFI_ERASE_BLOCK_PROTOCOL_REVISION ((2<<16) (60))

typedef struct _EFI_ERASE_BLOCK_PROTOCOL EFI_ERASE_BLOCK_PROTOCOL;

typedef struct {
	EFI_EVENT Event;
	EFI_STATUS TransactionStatus;
} EFI_ERASE_BLOCK_TOKEN;

typedef
EFI_STATUS*
(EFIAPI *EFI_BLOCK_ERASE)(
	IN EFI_BLOCK_IO_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_LBA LBA,
	IN OUT EFI_ERASE_BLOCK_TOKEN *Token,
	IN EFI_UINTN Size
);

typedef struct _EFI_ERASE_BLOCK_PROTOCOL {
	EFI_UINT64 Revision;
	EFI_UINT32 EraseLengthGranularity;
	EFI_BLOCK_ERASE EraseBlocks;
} EFI_ERASE_BLOCK_PROTOCOL;

////
// ATA Pass Thru Protocol
///

#define EFI_ATA_PASS_THRU_PROTOCOL_GUID {0x1d3de7f0,0x807,0x424f, {0xaa,0x69,0x11,0xa5,0x4e,0x19,0xa4,0x6f}}

#define EFI_ATA_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_ATA_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_ATA_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_HARDWARE_RESET 0x00
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_SOFTWARE_RESET 0x01
#define EFI_ATA_PASS_THRU_PROTOCOL_ATA_NON_DATA 0x02
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_IN 0x04
#define EFI_ATA_PASS_THRU_PROTOCOL_PIO_DATA_OUT 0x05
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA 0x06
#define EFI_ATA_PASS_THRU_PROTOCOL_DMA_QUEUED 0x07
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_DIAGNOSTIC 0x08
#define EFI_ATA_PASS_THRU_PROTOCOL_DEVICE_RESET 0x09
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_IN 0x0A
#define EFI_ATA_PASS_THRU_PROTOCOL_UDMA_DATA_OUT 0x0B
#define EFI_ATA_PASS_THRU_PROTOCOL_FPDMA 0x0C
#define EFI_ATA_PASS_THRU_PROTOCOL_RETURN_RESPONSE 0xFF

#define EFI_ATA_PASS_THRU_LENGTH_BYTES 0x80

#define EFI_ATA_PASS_THRU_LENGTH_MASK 0x70
#define EFI_ATA_PASS_THRU_LENGTH_NO_DATA_TRANSFER 0x00
#define EFI_ATA_PASS_THRU_LENGTH_FEATURES 0x10
#define EFI_ATA_PASS_THRU_LENGTH_SECTOR_COUNT 0x20
#define EFI_ATA_PASS_THRU_LENGTH_TPSIU 0x30

#define EFI_ATA_PASS_THRU_LENGTH_COUNT 0x0F

typedef struct _EFI_ATA_PASS_THRU_PROTOCOL EFI_ATA_PASS_THRU_PROTOCOL;

typedef EFI_UINT8 EFI_ATA_PASS_THRU_CMD_PROTOCOL;
typedef EFI_UINT8 EFI_ATA_PASS_THRU_LENGTH;

typedef struct {
	EFI_UINT32 Attributes;
	EFI_UINT32 IoAlign;
} EFI_ATA_PASS_THRU_MODE;

typedef struct {
	EFI_UINT8 Reserved1[2];
	EFI_UINT8 AtaCommand;
	EFI_UINT8 AtaFeatures;
	EFI_UINT8 AtaSectorNumber;
	EFI_UINT8 AtaCylinderLow;
	EFI_UINT8 AtaCylinderHigh;
	EFI_UINT8 AtaDeviceHead;
	EFI_UINT8 AtaSectorNumberExp;
	EFI_UINT8 AtaCylinderLowExp;
	EFI_UINT8 AtaCylinderHighExp;
	EFI_UINT8 AtaFeaturesExp;
	EFI_UINT8 AtaSectorCount;
	EFI_UINT8 AtaSectorCountExp;
	EFI_UINT8 Reserved2[6];
} EFI_ATA_COMMAND_BLOCK;

typedef struct {
	EFI_UINT8 Reserved1[2];
	EFI_UINT8 AtaStatus;
	EFI_UINT8 AtaError;
	EFI_UINT8 AtaSectorNumber;
	EFI_UINT8 AtaCylinderLow;
	EFI_UINT8 AtaCylinderHigh;
	EFI_UINT8 AtaDeviceHead;
	EFI_UINT8 AtaSectorNumberExp;
	EFI_UINT8 AtaCylinderLowExp;
	EFI_UINT8 AtaCylinderHighExp;
	EFI_UINT8 Reserved2;
	EFI_UINT8 AtaSectorCount;
	EFI_UINT8 AtaSectorCountExp;
	EFI_UINT8 Reserved3[6];
} EFI_ATA_STATUS_BLOCK;

typedef struct {
	EFI_ATA_STATUS_BLOCK *Asb;
	EFI_ATA_COMMAND_BLOCK *Acb;
	EFI_UINT64 Timeout;
	VOID *InDataBuffer;
	VOID *OutDataBuffer;
	EFI_UINT32 InTransferLength;
	EFI_UINT32 OutTransferLength;
	EFI_ATA_PASS_THRU_CMD_PROTOCOL Protocol;
	EFI_ATA_PASS_THRU_LENGTH Length;
} EFI_ATA_PASS_THRU_COMMAND_PACKET;

typedef
EFI_STATUS
(EFIAPI *EFI_ATA_PASS_THRU_PASSTHRU)(
	IN EFI_ATA_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT16 Port,
	IN EFI_UINT16 PortMultiplierPort,
	IN OUT EFI_ATA_PASS_THRU_COMMAND_PACKET *Packet,
	IN EFI_EVENT Event OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_ATA_PASS_THRU_GET_NEXT_PORT)(
	IN EFI_ATA_PASS_THRU_PROTOCOL *This,
	IN OUT EFI_UINT16 *Port
);

typedef
EFI_STATUS
(EFIAPI *EFI_ATA_PASS_THRU_GET_NEXT_DEVICE)(
	IN EFI_ATA_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT16 Port,
	IN OUT EFI_UINT16 *PortMultiplierPort
);

typedef
EFI_STATUS
(EFIAPI *EFI_ATA_PASS_THRU_BUILD_DEVICE_PATH)(
	IN EFI_ATA_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT16 Port,
	IN EFI_UINT16 PortMultiplierPort,
	OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef
EFI_STATUS
(EFIAPI *EFI_ATA_PASS_THRU_GET_DEVICE)(
	IN EFI_ATA_PASS_THRU_PROTOCOL *This,
	IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
	OUT EFI_UINT16 *Port,
	OUT EFI_UINT16 *PortMultiplierPort
);

typedef
EFI_STATUS
(EFIAPI *EFI_ATA_PASS_THRU_RESET_PORT)(
	IN EFI_ATA_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT16 *Port
);

typedef
EFI_STATUS
(EFIAPI *EFI_ATA_PASS_THRU_RESET_DEVICE)(
	IN EFI_ATA_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT16 Port,
	IN EFI_UINT16 PortMultiplierPort
);

typedef struct _EFI_ATA_PASS_THRU_PROTOCOL {
	EFI_ATA_PASS_THRU_MODE *Mode;
	EFI_ATA_PASS_THRU_PASSTHRU PassThru;
	EFI_ATA_PASS_THRU_GET_NEXT_PORT GetNextPort;
	EFI_ATA_PASS_THRU_GET_NEXT_DEVICE GetNextDevice;
	EFI_ATA_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
	EFI_ATA_PASS_THRU_GET_DEVICE GetDevice;
	EFI_ATA_PASS_THRU_RESET_PORT ResetPort;
	EFI_ATA_PASS_THRU_RESET_DEVICE ResetDevice;
} EFI_ATA_PASS_THRU_PROTOCOL;

////
// Storage Security Command Protocol
///

#define EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID {0xc88b0b6d,0x0dfc,0x49a7, {0x9c,0xb4,0x49,0x7,0x4b,0x4c,0x3a,0x78}}

typedef struct _EFI_STORAGE_SECURITY_COMMAND_PROTOCOL EFI_STORAGE_SECURITY_COMMAND_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_STORAGE_SECURITY_RECEIVE_DATA)(
	IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_UINT64 Timeout,
	IN EFI_UINT8 SecurityProtocol,
	IN EFI_UINT16 SecurityProtocolSpecificData,
	IN EFI_UINTN PayloadBufferSize,
	OUT VOID *PayloadBuffer,
	OUT EFI_UINTN *PayloadTransferSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_STORAGE_SECURITY_SEND_DATA)(
	IN EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *This,
	IN EFI_UINT32 MediaId,
	IN EFI_UINT64 Timeout,
	IN EFI_UINT8 SecurityProtocolId,
	IN EFI_UINT16 SecurityProtocolSpecificData,
	IN EFI_UINTN PayloadBufferSize,
	IN VOID *PayloadBuffer
);

typedef struct _EFI_STORAGE_SECURITY_COMMAND_PROTOCOL {
	EFI_STORAGE_SECURITY_RECEIVE_DATA ReceiveData;
	EFI_STORAGE_SECURITY_SEND_DATA SendData;
} EFI_STORAGE_SECURITY_COMMAND_PROTOCOL;

////
// NVM Express Pass Thru Protocol
///

#define EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID {0x52c78312,0x8edc,0x4233, {0x98,0xf2,0x1a,0x1a,0xa5,0xe3,0x88,0xa5}}

#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL 0x0001
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL 0x0002
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004
#define EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM 0x0008

#define NORMAL_CMD 0x00
#define FUSED_FIRST_CMD 0x01
#define FUSED_SECOND_CMD 0x02

#define CDW2_VALID 0x01
#define CDW3_VALID 0x02
#define CDW10_VALID 0x04
#define CDW11_VALID 0x08
#define CDW12_VALID 0x10
#define CDW13_VALID 0x20
#define CDW14_VALID 0x40
#define CDW15_VALID 0x80

typedef struct _EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL;

typedef struct {
	EFI_UINT32 OpCode : 8;
	EFI_UINT32 FusedOperation : 2;
	EFI_UINT32 Reserved : 22;
} NVME_CDW0;

typedef struct {
	NVME_CDW0 Cdw0;
	EFI_UINT8 Flags;
	EFI_UINT32 Nsid;
	EFI_UINT32 Cdw2;
	EFI_UINT32 Cdw3;
	EFI_UINT32 Cdw10;
	EFI_UINT32 Cdw11;
	EFI_UINT32 Cdw12;
	EFI_UINT32 Cdw13;
	EFI_UINT32 Cdw14;
	EFI_UINT32 Cdw15;
} EFI_NVM_EXPRESS_COMMAND;

typedef struct {
	EFI_UINT32 DW0;
	EFI_UINT32 DW1;
	EFI_UINT32 DW2;
	EFI_UINT32 DW3;
} EFI_NVM_EXPRESS_COMPLETION;

typedef struct {
	EFI_UINT32 Attributes;
	EFI_UINT32 IoAlign;
	EFI_UINT32 NvmeVersion;
} EFI_NVM_EXPRESS_PASS_THRU_MODE;

typedef struct {
	EFI_UINT64 CommandTimeout;
	VOID *TransferBuffer OPTIONAL;
	EFI_UINT32 TransferLength OPTIONAL;
	VOID *MetaDataBuffer OPTIONAL;
	EFI_UINT32 MetadataLength OPTIONAL;
	EFI_UINT8 QueueType;
	EFI_NVM_EXPRESS_COMMAND *NvmeCmd;
	EFI_NVM_EXPRESS_COMPLETION *NvmeCompletion;
} EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET;

typedef
EFI_STATUS
(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU)(
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL This,
	IN EFI_UINT32 NamespaceId,
	IN OUT EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET *Packet,
	IN EFI_EVENT Event OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE)(
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *This,
	IN OUT EFI_UINT32 *NamespaceId
);

typedef
EFI_STATUS
(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH)(
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT32 NamespaceId,
	OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef
EFI_STATUS
(EFIAPI *EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE)(
	IN EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL *This,
	IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
	OUT EFI_UINT32 *NamespaceId
);

typedef struct _EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL {
	EFI_NVM_EXPRESS_PASS_THRU_MODE *Mode;
	EFI_NVM_EXPRESS_PASS_THRU_PASSTHRU PassThru;
	EFI_NVM_EXPRESS_PASS_THRU_GET_NEXT_NAMESPACE GetNextNamespace;
	EFI_NVM_EXPRESS_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
	EFI_NVM_EXPRESS_PASS_THRU_GET_NAMESPACE GetNamespace;
} EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL;

////
// SD MMC Pass Thru Protocol
///

#define EFI_SD_MMC_PASS_THRU_PROTOCOL_GUID {0x716ef0d9,0xff83,0x4f69, {0x81,0xe9,0x51,0x8b,0xd3,0x9a,0x8e,0x70}}

typedef struct _EFI_SD_MMC_PASS_THRU_PROTOCOL EFI_SD_MMC_PASS_THRU_PROTOCOL;

typedef enum {
	SdMmcCommandTypeBc,
	SdMmcCommandTypeBcr,
	SdMmcCommandTypeAc,
	SdMmcCommandTypeAdtc
} EFI_SD_MMC_COMMAND_TYPE;

typedef enum {
	SdMmcResponceTypeR1,
	SdMmcResponceTypeR1b,
	SdMmcResponceTypeR2,
	SdMmcResponceTypeR3,
	SdMmcResponceTypeR4,
	SdMmcResponceTypeR5,
	SdMmcResponceTypeR5b,
	SdMmcResponceTypeR6,
	SdMmcResponceTypeR7
} EFI_SD_MMC_RESPONSE_TYPE;

typedef struct {
	EFI_UINT16 CommandIndex;
	EFI_UINT32 CommandArgument;
	EFI_UINT32 CommandType;
	EFI_UINT32 ResponseType;
} EFI_SD_MMC_COMMAND_BLOCK;

typedef struct {
	EFI_UINT32 Resp0;
	EFI_UINT32 Resp1;
	EFI_UINT32 Resp2;
	EFI_UINT32 Resp3;
} EFI_SD_MMC_STATUS_BLOCK;

typedef struct {
	EFI_SD_MMC_COMMAND_BLOCK *SdMmcCmdBlk;
	EFI_SD_MMC_STATUS_BLOCK *SdMmcStatusBlk;
	EFI_UINT64 Timeout;
	VOID *InDataBuffer;
	VOID *OutDataBuffer;
	EFI_UINT32 InTransferLength;
	EFI_UINT32 OutTransferLength;
	EFI_STATUS TransactionStatus;
} EFI_SD_MMC_PASS_THRU_COMMAND_PACKET;

typedef
EFI_STATUS
(EFIAPI *EFI_SD_MMC_PASS_THRU_PASSTHRU)(
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT8 Slot,
	IN OUT EFI_SD_MMC_PASS_THRU_COMMAND_PACKET *Packet,
	IN EFI_EVENT Event OPTIONAL
);

typedef
EFI_STATUS
(EFIAPI *EFI_SD_MMC_PASS_THRU_GET_NEXT_SLOT)(
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
	IN OUT EFI_UINT8 *Slot
);

typedef
EFI_STATUS
(EFIAPI *EFI_SD_MMC_PASS_THRU_BUILD_DEVICE_PATH)(
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT8 Slot,
	OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef
EFI_STATUS
(EFIAPI *EFI_SD_MMC_PASS_THRU_GET_SLOT_NUMBER)(
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
	IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
	OUT EFI_UINT8 *Slot
);

typedef
EFI_STATUS
(EFIAPI *EFI_SD_MMC_PASS_THRU_RESET_DEVICE)(
	IN EFI_SD_MMC_PASS_THRU_PROTOCOL *This,
	IN EFI_UINT8 Slot
);

typedef struct _EFI_SD_MMC_PASS_THRU_PROTOCOL {
	EFI_UINTN IoAlign;
	EFI_SD_MMC_PASS_THRU_PASSTHRU PassThru;
	EFI_SD_MMC_PASS_THRU_GET_NEXT_SLOT GetNextSlot;
	EFI_SD_MMC_PASS_THRU_BUILD_DEVICE_PATH BuildDevicePath;
	EFI_SD_MMC_PASS_THRU_GET_SLOT_NUMBER GetSlotNumber;
	EFI_SD_MMC_PASS_THRU_RESET_DEVICE ResetDevice;
} EFI_SD_MMC_PASS_THRU_PROTOCOL;

////
// RAM Disk Protocol
///

#define EFI_RAM_DISK_PROTOCOL_GUID {0xab38a0df,0x6873,0x44a9, {0x87,0xe6,0xd4,0xeb,0x56,0x14,0x84,0x49}}

typedef struct _EFI_RAM_DISK_PROTOCOL EFI_RAM_DISK_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_RAM_DISK_REGISTER_RAMDISK)(
	IN EFI_UINT64 RamDiskBase,
	IN EFI_UINT64 RamDiskSize,
	IN EFI_GUID *RamDiskType,
	IN EFI_DEVICE_PATH_PROTOCOL *ParentDevicePath OPTIONAL,
	OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath
);

typedef
EFI_STATUS
(EFIAPI *EFI_RAM_DISK_UNREGISTER_RAMDISK)(
	IN EFI_DEVICE_PATH_PROTOCOL *DevicePath
);

typedef struct _EFI_RAM_DISK_PROTOCOL {
	EFI_RAM_DISK_REGISTER_RAMDISK Register;
	EFI_RAM_DISK_UNREGISTER_RAMDISK Unregister;
} EFI_RAM_DISK_PROTOCOL;

////
// Partition Information Protocol
///

#define EFI_PARTITION_INFO_PROTOCOL_GUID {0x8cf2f62c,0xbc9b,0x4821, {0x80,0x8d,0xec,0x9e,0xc4,0x21,0xa1,0xa0}}

#define EFI_PARTITION_INFO_PROTOCOL_REVISION 0x0001000
#define PARTITION_TYPE_OTHER 0x00
#define PARTITION_TYPE_MBR 0x01
#define PARTITION_TYPE_GPT 0x02

typedef struct _EFI_PARTITION_INFO_PROTOCOL EFI_PARTITION_INFO_PROTOCOL;

#pragma pack(1)
typedef struct _EFI_PARTITION_INFO_PROTOCOL {
	EFI_UINT32 Revision;
	EFI_UINT32 Type;
	EFI_UINT8 System;
	EFI_UINT8 Reserved[7];
	union {
		MBR_PARTITION_RECORD Mbr;
		EFI_PARTITION_ENTRY Gpt;
	} Info;
} EFI_PARTITION_INFO_PROTOCOL;
#pragma pack()

////
// NVDIMM Label Protocol
///

#define EFI_NVDIMM_LABEL_PROTOCOL_GUID {0xd40b6b80,0x97d5,0x4282, {0xbb,0x1d,0x22,0x3a,0x16,0x91,0x80,0x58}}

#define EFI_NVDIMM_LABEL_INDEX_SIG_LEN 16
#define EFI_NVDIMM_LABEL_INDEX_ALIGN 256

#define EFI_NVDIMM_LABEL_NAME_LEN 64

#define EFI_NVDIMM_LABEL_FLAGS_ROLABEL 0x00000001
#define EFI_NVDIMM_LABEL_FLAGS_LOCAL 0x00000002
#define EFI_NVDIMM_LABEL_FLAGS_SPACOOKIE_BOUND 0x00000010

// Reserved flag is deprecated.
#define EFI_NVDIMM_LABEL_FLAGS_RESERVED 0x00000004
#define EFI_NVDIMM_LABEL_FLAGS_UPDATING 0x00000008

typedef struct _EFI_NVDIMM_LABEL_PROTOCOL EFI_NVDIMM_LABEL_PROTOCOL;

typedef struct EFI_NVDIMM_LABEL_INDEX_BLOCK {
	CHAR8 Sig[EFI_NVDIMM_LABEL_INDEX_SIG_LEN];
	EFI_UINT8 Flags[3];
	EFI_UINT8 LabelSize;
	EFI_UINT32 Seq;
	EFI_UINT64 MyOff;
	EFI_UINT64 MySize;
	EFI_UINT64 OtherOff;
	EFI_UINT64 LabelOff;
	EFI_UINT32 NSlot;
	EFI_UINT16 Major;
	EFI_UINT16 Minor;
	EFI_UINT64 Checksum;
	EFI_UINT8 Free[];
} EFI_NVDIMM_LABEL_INDEX_BLOCK;

typedef struct EFI_NVDIMM_LABEL {
	EFI_GUID Uuid;
	CHAR8 Name[EFI_NVDIMM_LABEL_NAME_LEN];
	EFI_UINT32 Flags;
	EFI_UINT16 NLabel;
	EFI_UINT16 Position;
	EFI_UINT64 SetCookie;
	EFI_UINT64 LbaSize;
	EFI_UINT64 Dpa;
	EFI_UINT64 RawSize;
	EFI_UINT32 Slot;
	EFI_UINT8 Alignment;
	EFI_UINT8 Reserved[3];
	EFI_GUID TypeGuid;
	EFI_GUID AddressAbstractionGuid;
	EFI_UINT64 SPALocationCookie;
	EFI_UINT8 Reserved1[80];
	EFI_UINT64 Checksum;
} EFI_NVDIMM_LABEL;

typedef struct EFI_NVDIMM_LABEL_SET_COOKIE_MAP {
	EFI_UINT64 RegionOffset;
	EFI_UINT32 SerialNumber;
	EFI_UINT16 VendorId;
	EFI_UINT16 ManufacturingDate;
	EFI_UINT8 ManufacturingLocation;
	EFI_UINT8 Reserved[31];
} EFI_NVDIMM_LABEL_SET_COOKIE_MAP;

typedef
EFI_STATUS
(EFIAPI *EFI_NVDIMM_LABEL_STORAGE_INFORMATION)(
	IN EFI_NVDIMM_LABEL_PROTOCOL *This,
	OUT EFI_UINT32 *SizeOfLabelStorageArea,
	OUT EFI_UINT32 *MaxTransferLength
);

typedef
EFI_STATUS
(EFIAPI *EFI_NVDIMM_LABEL_STORAGE_READ)(
	IN CONST EFI_NVDIMM_LABEL_PROTOCOL *This,
	IN EFI_UINT32 Offset,
	IN EFI_UINT32 TransferLength,
	OUT EFI_UINT8 *LabelData
);

typedef
EFI_STATUS
(EFIAPI *EFI_NVDIMM_LABEL_STORAGE_WRITE)(
	IN CONST EFI_NVDIMM_LABEL_PROTOCOL *This,
	IN EFI_UINT32 Offset,
	IN EFI_UINT32 TransferLength,
	IN EFI_UINT8 *LabelData
);


typedef struct _EFI_NVDIMM_LABEL_PROTOCOL {
	EFI_NVDIMM_LABEL_STORAGE_INFORMATION LabelStorageInformation;
	EFI_NVDIMM_LABEL_STORAGE_READ LabelStorageRead;
	EFI_NVDIMM_LABEL_STORAGE_WRITE LabelStorageWrite;
} EFI_NVDIMM_LABEL_PROTOCOL;

////
// EFI UFS Device Config Protocol
///

#define EFI_UFS_DEVICE_CONFIG_GUID {0xb81bfab0,0xeb3,0x4cf9, {0x84,0x65,0x7f,0xa9,0x86,0x36,0x16,0x64}}

typedef struct _EFI_UFS_DEVICE_CONFIG_PROTOCOL EFI_UFS_DEVICE_CONFIG_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR)(
	IN EFI_UFS_DEVICE_CONFIG_PROTOCOL *This,
	IN EFI_BOOLEAN Read,
	IN EFI_UINT8 DescId,
	IN EFI_UINT8 Index,
	IN EFI_UINT8 Selector,
	IN OUT EFI_UINT8 Descriptor,
	IN OUT EFI_UINT32 *DescSize
);

typedef
EFI_STATUS
(EFIAPI *EFI_UFS_DEVICE_CONFIG_RW_FLAG)(
	IN EFI_UFS_DEVICE_CONFIG_PROTOCOL *This,
	IN EFI_BOOLEAN Read,
	IN EFI_UINT8 FlagId,
	IN OUT EFI_UINT8 *Flag
);

typedef
EFI_STATUS
(EFIAPI *EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE)(
	IN EFI_UFS_DEVICE_CONFIG_PROTOCOL *This,
	IN EFI_BOOLEAN Read,
	IN EFI_UINT8 AttrId,
	IN EFI_UINT8 Index,
	IN EFI_UINT8 Selector,
	IN OUT EFI_UINT8 *Attribute,
	IN OUT EFI_UINT32 *AttrSize
);

typedef struct _EFI_UFS_DEVICE_CONFIG_PROTOCOL {
	EFI_UFS_DEVICE_CONFIG_RW_DESCRIPTOR RwUfsDescriptor;
	EFI_UFS_DEVICE_CONFIG_RW_FLAG RwUfsFlag;
	EFI_UFS_DEVICE_CONFIG_RW_ATTRIBUTE RwUfsAttribute;
} EFI_UFS_DEVICE_CONFIG_PROTOCOL;

#endif /* EFI_PROTOCOLS_MEDIA_ACCESS_H */
