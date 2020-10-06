## MCHBAR for the 4th Generation Intel® Mobile Processor (code name Haswell)

README.md tries to document in details two C examples for checking on ECC, found in this
directory:

	c2xx_memory_status.c
	ecc_check.c

Both are standalone (compiled/linked with gcc *.c).

Author strongly encourages readers to re-write c2xx_memory_status.c C example for Cores
6, 7, 8, 9, 10, with assistance of the 10th Generation Intel® Processor Families Datasheet,
Volume 2, included in the ../core-10gen/ .

### Author's remarks

The 4th Generation Intel® Mobile Processor, Volume 2 is included for much better
understanding of MCHBAR description. The net link is provided as well:

https://www.intel.com/content/dam/www/public/us/en/documents/datasheets/4th-gen-core-family-mobile-u-y-processor-lines-vol-2-datasheet.pdf

MCHBAR HW registers' definitions did change from Core 6 (Sky Lake).

### Some problems found in Linux kernel code while programming MCHBAR
https://lkml.org/lkml/2019/8/9/580

Resource sanity check: requesting [mem 0xfed10000-0xfed1ffff], which spans more than reserved
[mem 0xfed10000-0xfed17fff] caller dnv_rd_reg+0xc8/0x240 [pnd2_edac] mapping multiple BARs.

Not all of the mmio regions used in dnv_rd_reg() are the same size.  The MCHBAR window is 32KB
and the sideband ports are 64KB. Pass the correct size to ioremap() depending on which resource
it is read from.

### Mobile 4th Generation Intel "Core" Processor Family, Mobile Intel "Pentium/Celeron" Processor Family

#### 3.0 Host Device Configuration RegistersHost Bridge/DRAM (0/0/0/CFG) Registers Summary (page 41)

#### 3.1 Host Bridge/DRAM (0/0/0/CFG) Registers Summary (page 41)

This chapter documents the registers for the Bus 0, Device 0, Function 0.

	NOTE: These registers apply to all processors of the same family

##### 3.1.12 MCHBAR—Host Memory Mapped Register Range Base - Offset 48h (page 47)

	WARNING: Bit 0 of very high importance

This is the base address for the Host Memory Mapped Configuration space.

There is no physical memory within this 32KB window that can be addressed.

The 32KB reserved by this register does not alias to any PCI 2.3 compliant memory mapped space.

On reset, the Host MMIO Memory Mapped Configuration space is disabled and must be enabled by
writing a 1 to MCHBAREN [Dev 0, offset 48h, bit 0].

All the bits in this register are locked in Intel TXT mode.

The register space contains memory control, initialization, timing, buffer strength registers,
clocking registers and power and thermal management registers.

	Host Bridge and DRAM Controller (D0:F0) => Bus 0, Device 0, Function 0

	_____________________________________________________________________________________________
	Type	Size	Offset			Default

	PCI	64 bit	[B:0, D:0, F:0] + 48h	0000000000000000h
	_____________________________________________________________________________________________
	BIOS Access	SMM Access		OS Access

	RW		R			R
	_____________________________________________________________________________________________
	Bit Range	Default & Access	Field Name (ID): Description

	63:39		0h - RO			Reserved

	38:15		000000h - RW		MCHBAR:
						This field corresponds to bits 38 to 15 of the
						base address Host Memory Mapped configuration
						space. BIOS will program this register resulting
						in a base address for a 32KB block of contiguous
						memory address space. This register ensures that
						a naturally aligned 32KB space is allocated within
						the first 512GB of addressable memory space.
						System Software uses this base address to program
						the Host Memory Mapped register set. All the bits
						in this register are locked in Intel TXT mode.

	14:1		0h - RO			Reserved

	0		0h - RW			MCHBAREN:
						0: MCHBAR is disabled and does not claim any memory
						1: MCHBAR memory mapped accesses are claimed and
						decoded appropriatelyThis register is locked in
						Intel TXT mode.
	_____________________________________________________________________________________________

#### 4.2 MCHBAR Registers Summary (Memory Controller (MCHBAR) Registers)

This chapter documents the Memory Controller MCHBAR registers.

##### 4.2.16 MAD—Address decode channel 0 (page 126)

	_____________________________________________________________________________________________
	Bit Range	Default & Access	Field Name (ID): Description

	24:25		0h - RW/L		ECC Channel Configuration (ECC):
						ECC configuration in the channel:
						00: No ECC active in the channel.
						11: ECC active in both IO and ECC logic.

						Note: This field must be programmed identically
						for all populated channels.
	_____________________________________________________________________________________________

##### 4.2.17 MAD—Address decode channel 1 (page 127)

	_____________________________________________________________________________________________
	Bit Range	Default & Access	Field Name (ID): Description

	24:25		0h - RW/L		ECC Channel Configuration (ECC):
						ECC configuration in the channel:
						00: No ECC active in the channel.
						11: ECC active in both IO and ECC logic.

						Note: This field must be programmed identically
						for all populated channels.
	_____________________________________________________________________________________________
