DEVOEM         = 3
BYPSECT        = 11
SECTPCLUST     = 13
RESECTS        = 14
FATTABS        = 16
NROOTDIRENT    = 17
TOTSECTS       = 19
DESCR          = 21
SECTSPFAT      = 22
SECTSPTRCK     = 24
NHEADS         = 26
NHIDDNSECTS    = 28
NHIDDNSECTSHI  = 30
TOTSECTSINFS   = 32
DRVNO          = 36
RESRVED        = 37
EXTSIG         = 38
DRVSERIAL      = 39
LABEL          = 43
FSTYPE         = 54

devOEM:	.ascii "mkfs.fat"
ByPSect:	.word 0x200
SectPClust:	.byte 0x10
ResSects:	.word 0x10
FatTabs:	.byte 0x2
NRootDirEs:	.word 0x200
TotSects:	.word 0x0
MedDescr:	.byte 0xf8
SectsPFat:	.word 0x100
SectsPTrck:	.word 0x20
NHeads:	.word 0x10
NHiddenSects:	.word 0x0
NhiddnSectshi:	.word 0x0
TotSectsInFS:	.int 0xfff00
LogDrvNo:	.byte 0x80
Resrvd:	.byte 0x0
ExtSig:	.byte 0x29
DrvSeriNum:	.int 0xb31f206e
VolLabel:	.ascii "NO NAME    "
FSType:	.ascii "FAT16   "


/* Root directory */
FILEDIRNAME     = 0
ATTRB           = 11
DIRRESERVED     = 12
CREATETIMEMILLI = 13
CREATETIME      = 14
CREATEDATE      = 16
LASTACCDATE     = 18
FIRSTCLUSTHI    = 20
WRITETIME       = 22
WRITEDATE       = 24
FIRSTCLUSTLO    = 26
FILESIZE        = 28
  
ROOTDIRENTRYSZ  = 32
FILEATTRIB      = 0x20
