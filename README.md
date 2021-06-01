# Ellisya Virtual Machine

# V2

Simply: `opcode`-`mem addr1`-`mem addr2`-`mem addr3`-`data`

No need for useless Cache................

# V1 IS COMPLETELY GARBAGE/CRAP
## Specification V1

Ellisya Virtual Machine is a switch & register based VM implemented in C/C++. It has 3 registers $1 $2 and $3 (aka 3 args for each instruction), and 3 Caches (to hold temporary data) (Actually, 256 units of Cache can be accessed easily).

Because of the limitation of register/Data size, the VM can utilize maximum 64kb of memory address space (`0x0000 - 0xFFFF`).

### Bytecode format

Each instruction is 8 bytes word containing 1 byte for operator, 3 bytes for register and 4 bytes for Data.
The Data will store in little-endian byteorder. 

```text
Diagram of one instruction in bit
-------------------------------
Operator  | Register1 | Register2 | Register3 | Data
0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 | 0000 0000 0000 0000 0000 0000 0000 0000
```
Note that `0000 0000` is 8 bits, 4 bytes or 2 nipple.

```text
Diagram of one instruction in bytes
---------------------------------
          0x
Operator  00
Register1 00
Register2 00
Register3 00
Data     00 00 00 00                   
```
### Operators

`$1`,`$2`,`$3` are caches, they can be either data or memory location of the VM.

Hex | Word  | Usage       | Description
----|-------|-------------|------------|
0x00| halt  | halt |  |
0x01| load  | load $1 0x12AF | load `Data` to Cache$1
0x02| inc   | inc  $1      | increase value on Cache$1 by 1
0x03| add   | add  $3 $1 $2| add Cache$1 and Cache$2 then store it to Cache$3 
0x04| read  | read $2 $1   | read  the content of memory address indicated by Cache$1 to Cache$2
0x05| write | write $2 $1  | write the content of Cache$1 to memory address indicated by Cache$2
0x06| print | print $1     | print the content of Cache$1 to stdout  
0xxx| TODO  | to be expanded |

Currently, only `read` and `write` can access memory directly.

### Assembly

Each line contains only 1 instruction which can be directly translated to 8 bytes.

```text
          assembly <-> hexdump
------------------------------------------------
load $1 0x00000012 <-> 01  01 00 00  00 00 00 12
load $2 0x5FFFFFFF <-> 01  02 00 00  5F FF FF FF
add add $3 $1 $2   <-> 03  03 01 02  00 00 00 00
halt               <-> 00  00 00 00  00 00 00 00
```
## Virtual Machine

Memory are paged as 4 bytes units (same as Data for each instruction). 

Each Cache unit is also 4 bytes, and can be indexed by 01,02,03. (Note: The instruction however use 1 byte ot index the registers.)

## Technical Notes

**1 byte = 1 octet = 2 nibble = 8 bits**

**A 16-bit unsigned integer can hold 2^16=65536 different values.**

This imply that a processor with 16-bit memory addresses can directly access 64KiB (65536/1024) of byte-addressable memory.

**0x00 is 1 byte (8 bits)in hexadecimal form (or base16) and it can hold 2^8=256 possibilities**

Examples:

* 004 -> 0x 04 -> 0b 0000 0100
* 256 -> 0x FF -> 0b 1111 1111 

**X86_64 use little-endian**

That's saying `12 AB CD EF` would become `ef cd ab 12` when written to a binary file.

```text
12 AB CD EF memory 
│  │  │  |
│  │  │  └── EF
│  │  └───── CD
│  └──────── AB
└─────────── 12
```

## Resources
### more ISA(Instruction Set Architecture)
LC-3  <https://justinmeiners.github.io/lc3-vm/supplies/lc3-isa.pdf>

MIPS <http://www.math-cs.gordon.edu/courses/cps311/handouts-2019/MIPS%20ISA.pdf>
### Textbooks
The Elements of Computing Systems 2nd from MIT.

## TODO

Read some python VM <https://tenthousandmeters.com/blog/python-behind-the-scenes-1-how-the-cpython-vm-works/>
