## INTEL MCHBAR Core 10 (Ice Lake)

### Author's remarks

The 10th Generation Intel® Processor FamiliesDatasheet, Volume 2 of 2 manual is	included for
much better understanding of these files (just in case). The net link is provided as well:

https://www.intel.com/content/dam/www/public/us/en/documents/datasheets/10th-gen-core-families-datasheet-vol-2-datasheet.pdf

### Some problems found in Linux kernel code while programming MCHBAR
https://lkml.org/lkml/2019/8/9/580

Resource sanity check: requesting [mem 0xfed10000-0xfed1ffff], which spans more than reserved
[mem 0xfed10000-0xfed17fff] caller dnv_rd_reg+0xc8/0x240 [pnd2_edac] mapping multiple BARs.

Not all of the mmio regions used in dnv_rd_reg() are the same size.  The MCHBAR window is 32KB
and the sideband ports are 64KB. Pass the correct size to ioremap() depending on which resource
it is read from.

	NOTE from Author: From at least Gen. 8 (9, 10) the minimum assigned MCHBAR mapped space
	is 64KB, NOT 32KB anymore!

### INTEL Core 10 (Ice Lake) MCHBAR documentation (10th-gen-core-families-datasheet-vol-2-datasheet.pdf)

#### 3.1 Host Bridge/DRAM Registers (D0:F0) (page 36)

This chapter documents the registers in Bus 0, Device 0, Function 0.

	NOTE: These registers apply to all processors of the same family

##### 3.1.14 MCHBAR Base Address Register (MCHBAR_0_0_0_PCI) - Offset 48h (page 45)

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

	38:16		000000h - RW		MCHBAR:
						This field corresponds to bits 38 to 16 of the
						base address Host Memory Mapped configuration
						space. BIOS will program this register resulting
						in a base address for a 64KB block of contiguous
						memory address space. This register ensures that
						a naturally aligned 64KB space is allocated within
						the first 512GB of addressable memory space.
						System Software uses this base address to program
						the Host Memory Mapped register set. All the bits
						in this register are locked in Intel TXT mode.

	15:1		0h - RO			Reserved

	0		0h - RW			MCHBAREN:
						0: MCHBAR is disabled and does not claim any memory
						1: MCHBAR memory mapped accesses are claimed and
						decoded appropriatelyThis register is locked in
						Intel TXT mode.
	_____________________________________________________________________________________________

#### 3.2 Memory Controller (MCHBAR) Registers (page 80)

This chapter documents the Memory Controller MCHBAR registers.

Base address of these registers are defined in the MCHBAR_0_0_0_PCI register in Bus 0, Device 0, F-n 0.
The MCHBAR exposes 3 sets of memory controller registers: channel 0, channel 1 as as well broadcast:

	Channel 0 offset range: 4000h-43FFh
	Channel 1 offset range: 4400h-47FFh
	Broadcast offset range: 4C00h-4FFFh

Memory Controller Broadcast register behavior is to write to all channels and read from channel 0.

	NOTE:	For brevity, only channel 0 is documented. For channel 1 registers add 0x0400, for broadcast
		add 0x0C00 to the channel 0 register offset

	NOTE:	These registers apply to all processors (please, read author's remarks)

##### 3.2.36 Intra-Channel 0 Decode Parameters (MAD_INTRA_CH0_0_0_0_MCHBAR) — Offset 5004h (page 109)

	_____________________________________________________________________________________________
	Bit Range	Default & Access	Field Name (ID): Description

	13:12		0h - RW/L		ECC Channel Configuration (ECC):
						0: No ECC active in the channel.
						1: ECC is active in IO, ECC logic is not active.
						2: ECC is disabled in IO, but ECC logic is enabled.
						3: ECC active in both IO and ECC logic.

						Notes: This field must be programmed identically for
						all populated channels.

						In a system with ECC this field must be programmed
						to 1 during training and then 3 before transitioning
						from training mode to Normal mode.
	_____________________________________________________________________________________________

##### 3.2.37 Intra-Channel 0 Decode Parameters (MAD_INTRA_CH1_0_0_0_MCHBAR) — Offset 5008h (page 110)

	_____________________________________________________________________________________________
	Bit Range	Default & Access	Field Name (ID): Description

	13:12		0h - RW/L		ECC Channel Configuration (ECC):
						0: No ECC active in the channel.
						1: ECC is active in IO, ECC logic is not active.
						2: ECC is disabled in IO, but ECC logic is enabled.
						3: ECC active in both IO and ECC logic.

						Notes: This field must be programmed identically for
						all populated channels.

						In a system with ECC this field must be programmed
						to 1 during training and then 3 before transitioning
						from training mode to Normal mode.
	_____________________________________________________________________________________________

### YET TO DO in The Future

Since owner of this repo does not own Core 8, 9 or 10 platforms, the first step is to upgrade Core 4 files:

	c2xx_memory_status.c
	ecc_check.c

To be Core 8, 9 and 10 compliant, according to the well outlined documentation in README and .pdf document
in the current directory.

Then to check if it does work (estimated amount of work 1 to 2 hours for the code solely).

Owner also should (The Time will be scheduled in The Future) port both examples to Core 10 (Ice Lake).
