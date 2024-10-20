# The ADI driver file format
### magic number and architecture
The magic number is `0x414449204B4F4F4C`(ASCII "`ADI KOOL`") if the target arch is little-endian and `0x4C4F4F4B20494441`(ASCII "`LOOK IDA`") otherwise


### Header
other fields in the header include:
* Architecture(`1` byte): see the list bellow
* Init routine entry point(`4` or `8` bytes): pointer to the init routine in memory(drivers are NEVER relocatable)
* Driver name(`2` bytes): offset into the string table for the driver's name
* Author name(`2` bytes): offset into the string table for the author's name
* Driver version(`3` bytes): `1` byte for the major version, `1` byte for the minor version and `1` byte for the patch
* Metalanguage table offset(`4` bytes): offset of the metalanguage table in the file
* String table offset(`4` bytes): offset of the string table in the file
* Segment table offset(`4` bytes): offset of the segment table in the file

### Architectures
* `0x00` = x86_86
* `0x01` = i486
* `0x02` = aarch32
* `0x03` = aarch64
* `0x04` = riscv32
* `0x05` = riscv64

### String table
The string table just has strings lul.

### Segment table
The segment table just has segments lul.

### Metalanguage table
The metalanguage table just has metalanguages lul.