### INTELTOOL to up to Core 10 INTEL CPUs

Provides information about the Intel CPU/chipset hardware configuration (register contents,
MSRs, etc).

This tool is developed using coreboot inteltool directory:

https://github.com/coreboot/coreboot/tree/master/util/inteltool

And using older release of jimmysitu/inteltool:

https://github.com/jimmysitu/inteltool

It is the latest inteltool up-to-date with up to Core 10 INTEL CPUs.

Please, use diff/kdiff3 or some other comparison tool to explore changes.

#### Short User Manual

	$ sudo ./inteltool -h
	usage: ./inteltool [-vh?gGrplmedPMaAsfSRx]

	-v | --version:		print the version
	-h | --help:		print this help

	-s | --spi:		dump southbridge spi and bios_cntrl registers
	-f | --gfx:		dump graphics registers (UNSAFE: may hang system!)
	-R | --ahci:		dump AHCI registers
	-g | --gpio:		dump southbridge GPIO registers
	-G | --gpio-diffs:	show GPIO differences from defaults
	-r | --rcba:		dump southbridge RCBA registers
	-p | --pmbase:		dump southbridge Power Management registers

	-l | --lpc:		dump southbridge LPC/eSPI Interface registers

	-m | --mchbar:		dump northbridge Memory Controller registers
	-S FILE | --spd=FILE:	create a file storing current timings (implies -m)
	-e | --epbar:		dump northbridge EPBAR registers
	-d | --dmibar:		dump northbridge DMIBAR registers
	-P | --pciexpress:	dump northbridge PCIEXBAR registers

	-M | --msrs:		dump CPU MSRs
	-A | --ambs:		dump AMB registers
	-x | --sgx:		dump SGX status
	-a | --all:		dump all known (safe) registers
	     --pcr=PORT_ID:	dump all registers of a PCR port
				(may be specified max 8 times)
