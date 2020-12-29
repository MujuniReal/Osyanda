# OSyanda

with floppy drives, you will have to trust the FAT BPB
but with hard disks, you will have to call for BIOS calls
to get the real CHS values please dont forget to use the BIOS
int 0x13 with 8 inside %ah coz thats the subfunction number

we need bios extended functions to read heavy boys of about 8GB

	LBA = (C * TH * SPT) + (H * SPT) + (S - 1)

## now listen here, heres the plan;
	use the ext2 on vin.img to store your OS files period
	that includes designing algorithms to read the ext2 filesystem


## where we stopped:
	make a filesystem for your OS
		ext and the rest suck coz we didnt make them and they arent for Impala
	assembly port interactions (serial / parallel)
		may also involve microcontroller interaction with assembly language
	interrupt handling the above point and this one to help out on bootloader design
	
