#define FAT32_STRUCT
//the following file is for a hardisk of 20GB formatted with fat32

FATstruct:

devOEM:	.asciz	"mkdosfs"	//Original Equipment Manufacturer 8bytes

ByPSect:	.word 0x0200	//512Bytes per sector

SectPClust:	.byte 0x20	//Sectors per cluster

ResSects:	.word 0x0020	//Reserved Sectors of Floppy 2Bytes

FatTabs:	.byte 0x02	//Number of Fat tables 1Byte

NRootDirEs:	.word 0x0000	//Maximum Number of root directory entries

Undefined:	.word 0x0000	//Total number of sectors on the disk

MedDescr:	.byte 0xf8	//The media descriptor of a floppy disk 1Byte for any floppy disk 0xf0 for removable, f8 for fixed media eg hardisk

undefinedtwo:	.word 0x0000	

SectsPTrck:	.word 0x0020	//Sectors Per Track 2Bytes.

NHeads:		.word 0x0040	//Number of heads 2Bytes

NHiddenSects:	.word 0x0000	//Number of hidden sectors 2Bytes
		.word 0x0000

TotSectsInFS:   .word 0xff60	//low
		.word 0x027f	//high

SectsPFat:	.word 0x2800
		.word 0x0000

FAT_Mirroring:	.word 0x0000

HigherByte:	.word 0x0000

FirstClustForRootDir:	.word 0x0002
			.word 0x0000	//cluster number for the first cluster
					//of the root directory

FsInfo:		.word 0x0001

SectNoInReservdArea:	.word 0x0006


Reserved2:	.word 0x0000
		.word 0x0000
		.word 0x0000
		.word 0x0000
		.word 0x0000
		.word 0x0000

LogDrvNo:	.byte 0x00		//Logical Drive Number 1Byte

Resrvdee:		.byte 0x00	//This here is reserved space 1Byte
ExtSig:		.byte 0x29		//Well this is the extended signature
DrvSeriNum:	.word 0x3fee
		.word 0xf330		//This is the drive Serial Number comes with the drive it spans 4Bytescc

VolLabel:	.ascii "           "	//Volume Label 11Bytes
FSType:		.ascii "FAT12   "	//Filesystem Type This Spans 8Bytes

