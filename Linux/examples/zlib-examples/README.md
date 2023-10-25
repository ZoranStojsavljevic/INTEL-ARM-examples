### ZLIB Compression/Decompression

#### ZLIB location in kernel:

	include/linux/zlib.h

#### The test lacmus application for squashing the .mnfb manifests: gun.c.
https://github.com/madler/zlib/blob/master/examples/gun.c

#### The compilation command for gun:

	gcc gun.c -lz -o gun

#### The usage of the ZLIB - gun exec:

	## To decompress using user space zlib:
	./gun ETH-CLICK.mnfb.gz

#### Empirical testing of the short .mnfb files (from 100 to 400 bytes)

Two examples used: EEPROM-2-CLICK.mnfb and ETH-CLICK.mnfb

#### ZLIB compression:

	[vuser@fedora33-ssd zlib-examples]$ ls -al
	-rw-r--r--.  1 vuser vboxusers   232 Feb 24 11:59 EEPROM-2-CLICK.mnfb
	-rw-r--r--.  1 vuser vboxusers   128 Feb 24 19:58 ETH-CLICK.mnfb

	[vuser@fedora33-ssd zlib-examples]$ gzip ETH-CLICK.mnfb
	[vuser@fedora33-ssd zlib-examples]$ gzip EEPROM-2-CLICK.mnfb

	[vuser@fedora33-ssd zlib-examples]$ ls -al
	-rw-r--r--.  1 vuser vboxusers   215 Feb 24 11:59 EEPROM-2-CLICK.mnfb.gz
	-rw-r--r--.  1 vuser vboxusers   145 Feb 24 19:58 ETH-CLICK.mnfb.gz

	[vuser@fedora33-ssd zlib-examples]$ xxd ETH-CLICK.mnfb.gz
	00000000: 1f8b 0808 e0a1 3660 0003 4554 482d 434c  ......6`..ETH-CL
	00000010: 4943 4b2e 6d6e 6662 006b 6060 60e4 6060  ICK.mnfb.k```.``
	00000020: 6460 6462 6090 6060 6210 60f4 cdcc 2eca  d`db`.``b.`.....
	00000030: 77cd 49cd 2e29 cacf cbcc 4e64 6010 008a  w.I..)....Nd`...
	00000040: 7332 b986 7828 38e7 6426 6703 f9ac 0c2c  s2..x(8.d&g....,
	00000050: 8cec ec6c 6cac 40c0 04d4 cfcc c0c8 c5c0  ...ll.@.........
	00000060: c0c1 c002 3609 4433 3130 728b 30b0 3330  ....6.D310r.0.30
	00000070: 3273 3330 a87c 019b 0f02 20b3 3898 53f3  2s30.|.... .8.S.
	00000080: 928d 2cb2 cc0c 1818 00b7 4199 9380 0000  ..,.......A.....
	00000090: 00                                       .

Please, do note zlib compression header: 00000000: 1f 8b 08

#### ZLIB decompression:

	[vuser@fedora33-ssd zlib-examples]$ ./gun EEPROM-2-CLICK.mnfb.gz
	[vuser@fedora33-ssd zlib-examples]$ ./gun ETH-CLICK.mnfb.gz

	[vuser@fedora33-ssd zlib-examples]$ ls -al
	-rw-r--r--.  1 vuser vboxusers   232 Feb 24 11:59 EEPROM-2-CLICK.mnfb
	-rw-r--r--.  1 vuser vboxusers   128 Feb 24 19:58 ETH-CLICK.mnfb

	[vuser@fedora33-ssd zlib-examples]$ xxd ETH-CLICK.mnfb
	00000000: 8000 0001 0800 0100 0102 0000 1800 0200  ................
	00000010: 1001 4d69 6b72 6f45 6c65 6b74 726f 6e69  ..MikroElektroni
	00000020: 6b61 0000 1000 0200 0902 4554 4820 436c  ka........ETH Cl
	00000030: 6963 6b00 1000 0500 0401 0707 0606 0505  ick.............
	00000040: 0505 0201 0800 0300 010a 0000 0800 0400  ................
	00000050: 0100 0102 0800 0400 0200 010b 1400 0700  ................
	00000060: 0103 0b00 0024 f400 0102 0000 0000 0000  .....$..........
	00000070: 1000 0200 0803 656e 6332 386a 3630 0000  ......enc28j60..
