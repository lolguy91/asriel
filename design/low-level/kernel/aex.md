
# Aex: The aesthetic executable format

### Magic value
Aex's magic value is `0x69420666` in the target endianness.

When reading the magic value, if the value is `0x6942`, the endiannesses of the host and target match; if it is `0x4269`, the endiannesses of the host and target don't match, otherwise it is not an `aex` executable.
### Flags
The byte after the magic value is the flags byte:
* Bit `0`: Always 1
* Bit `1`: Relocatable
* Bit `2`: Executable
* Bit `3`: Contains Debug Symbols
* Bits `4-5`: Machine
* Bits `6`: Reserved
* Bits `7`: Reserved

The machines are:
* `0x0` = `x86_64`
* `0x1` = `aarch64`
* `0x2` = `riscv64`
* `0x2` = `Reserved`
### Other header parameters
* Entry point adress(`8 bytes`)
* Number of segments(`1 byte`)
* Symbol table size(`2 bytes`)
<!-- TODO: Relocatons --->
### Segment table
The segment table follows after the Header:
One entry contains the following things:
* Flags(`1 byte`)
* Base(`8 bytes`)
* Size(`8 bytes`)
* Union
  * Offset(`4 bytes`)
  * Prefill value(`1 byte`)
  * Prefill value(`2 bytes`)
  * Prefill value(`4 bytes`)

And the flags are:
* Bit `0`: Relocatable
* Bit `1`: MMU Perms: Read
* Bit `2`: MMU Perms: Write
* Bit `3`: MMU Perms: Exec
* Bits `4-5`: prefill size(`0` = not prefilled)
* Bit `6-7`: Reserved
### Symbol table
The symbol table follows after the Segment table:
One entry contain the following things:
* Type(`1 byte`)
* Adress(`8 bytes`)
* Name offset(`2 bytes`)

And the types are:
* `0x0` = Variable?
* `0x1` = Function?