#define FAT_STRUCT
//the following file is for a hard disk of 8GB

FATstruct:

devOEM:				.ascii	"mkfs.fat"	//Original Equipment Manufacturer 8bytes we ended this string with a zero to make up for 8bytes
ByPSect:			.word 0x0200	//512Bytes per sector
SectPClust:			.byte 0x08	//Sectors per cluster in this case one cluster is as heavy as the sector 1Byte
ResSects:			.word 0x0020	//Reserved Sectors of Floppy 2Bytes in this case this is initialized to 1 coz there is onlyone the boot sector as the reserved sector
FatTabs:			.byte 0x02	//Number of Fat tables 1Byte i gues becoz its a floppy with two sides period thats why
NRootDirEs:			.word 0x0000	//Maximum Number of root directory entries for a floppy disk 2Bytes in base 10 they are 224 as max entries
TotSects:			.word 0x0000	//Total number of sectors on the floppy 2Bytes
MedDescr:			.byte 0xf8	//The media descriptor of a floppy disk 1Byte for any floppy disk 0xf0 for removable, f8 for fixed media eg hardisk
Reserved1:			.word 0x0000	//The number of sectors per FAT 2Bytes each FAT table spans 9 sectors
SectsPTrck:			.word 0x003f	//Sectors Per Track 2Bytes. for this floppy they are 18 sectors per track
/* whats below here originally is 0x00ff */
NHeads:				.word 0x001f 	//Number of heads 2Bytes, of the disk or required heads thats if the disk doesnt have the physical heads
NHiddenSects:		.word 0x0000	//Number of hidden sectors 2Bytes we go zero coz we wish not to hide any or naturally there arent any hidden sectors
NhiddnSectshi:		.word 0x0000	//This is the total number of hidden sectors as a high word of the total number spanning 2Bytes
TotSectsInFS:   	.word 0xffc0	//Total sectors in Filesystem
			.word 0x00ff
SectsPFat: 			.word 0x3fe0 	/* low */
SectsPFathi:			.word 0x0000	/* high */
FATmirroring:		.word 0x0000

Himirroring:	.word 0x0000

Root_dirStartClustlo:		.word 0x0002 	/* cluster number of the first cluster of the root directory */
Root_dirStartClusthi:		.word 0x0000
FSInfo:				.word 0x0001

MBRCopyLocation: 	.word 0x0006 	/*location of the copy of the MBR in sectors LBA */

Reserved2:			.word 0x0000
					.word 0x0000
					.word 0x0000
					.word 0x0000	/* 12 freaking bytes */
					.word 0x0000
					.word 0x0000

LogDrvNo:			.byte 0x80	//Logical Drive Number 1Byte. This here is tobe initialized at boot time from the %dl register coz the %dl register holds the number of the selected device as seen from the BIOS perspective  0x0 for a drive disk, hardisks start at 0x80
Resrvd3:			.byte 0x01	//This here is reserved space 1Byte it means current head in use probably

ExtSig:				.byte 0x29	//Well this was the extended signature of this floppy disk 1Byte
DrvSeriNum:			.word 0x8411
				.word 0xc609	//This is the drive Serial Number comes with the drive it spans 4Bytescc
VolLabel:			.ascii "NO NAME    "	//Volume Label 11Bytes like a name We just initialized it with spaces in hexadecimal ascii spaces are 0x20
FSType:				.ascii "FAT32   "	//Filesystem Type This Spans 8Bytes

