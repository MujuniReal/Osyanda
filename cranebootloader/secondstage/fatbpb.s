devOEM:	.ascii "mkfs.fat"
ByPSect:	.word 0x200
SectPClust:	.byte 0x10
ResSects:	.word 0x10
FatTabs:	.byte 0x2
NRootDirEs:	.word 0x200
TotSects:	.word 0x0
MedDescr:	.byte 0xf8
SectsPFat:	.word 0x100
SectsPTrck:	.word 0x3f
NHeads:	.word 0xff
NHiddenSects:	.word 0x0
NhiddnSectshi:	.word 0x0
TotSectsInFS:	.int 0x100000
LogDrvNo:	.byte 0x80
Resrvd:	.byte 0x0
ExtSig:	.byte 0x29
DrvSeriNum:	.int 0x979a2ce4
VolLabel:	.ascii "NO NAME    "
FSType:	.ascii "FAT16   "
