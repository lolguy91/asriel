# The ADI driver file format
### magic number and architecture
The magic number is `0x414449204B4F4F4C`(ASCII "`ADI KOOL`") if the target arch is little-endian and `0x4C4F4F4B20494441`(ASCII "`LOOK IDA`") otherwise

The byte after the magic value is the architecture byte,
there are `16` valid architectures:

* `0x00` = i486
* `0x01` = x86_86
* `0x02` = aarch32
* `0x03` = aarch64
* `0x04` = riscv32
* `0x05` = riscv64
* `0x06` = powerpc
* `0x07` = power
* `0x08` = mips32
* `0x09` = mips64
* `0x0A` = alpha
* `0x0B` = arc
* `0x0C` = openrisc
* `0x0D` = sparc
* `0xFF` = ADI interpreted language

### other fields
other fields in the header include:

