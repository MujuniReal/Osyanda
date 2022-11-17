
	.code16
	.global mainSecond
	.global LogDrvNo
	.global NHeads
	.global SectsPTrck
	.global SectsPFat
	.global ResSects
	.global FatTabs
	.global NRootDirEs
	.global ByPSect
	.global SectPClust
	.text
	.org 0x00

mainSecond:
 jmp _start
 nop


devOEM: .ascii "mkfs.fat"
ByPSect: .word 0x200
SectPClust: .byte 0x10
ResSects: .word 0x10
FatTabs: .byte 0x2
NRootDirEs: .word 0x200
TotSects: .word 0x0
MedDescr: .byte 0xf8
SectsPFat: .word 0x100
SectsPTrck: .word 0x20
NHeads: .word 0x10
NHiddenSects: .word 0x0
NhiddnSectshi: .word 0x0
TotSectsInFS: .int 0xfff00
LogDrvNo: .byte 0x80
Resrvd: .byte 0x1
ExtSig: .byte 0x29
DrvSeriNum: .int 0xb31f206e
VolLabel: .ascii "NO NAME    "
FSType: .ascii "FAT16   "


Root_dirSects: .word 0x0000
Root_dirStart: .word 0x0000


_start:
	call crane_main

_hang:
	jmp _hang

Welcome_Note:
kernelfilename: .ascii "IMPALA  IMG"
