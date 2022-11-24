	.global devOEM
	.global ByPSect
	.global SectPClust
	.global ResSects
	.global FatTabs
	.global NRootDirEs
	.global TotSects
	.global MedDescr
	.global SectsPFat
	.global SectsPTrck
	.global NHeads
	.global NHiddenSects
	.global NhiddnSectshi
	.global TotSectsInFS
	.global LogDrvNo
	.global Resrvd
	.global ExtSig
	.global DrvSeriNum
	.global VolLabel
	.global FSType

	.global DEVOEM         
	.global BYPSECT        
	.global SECTPCLUST     
	.global RESECTS        
	.global FATTABS        
	.global NROOTDIRENT    
	.global TOTSECTS       
	.global DESCR          
	.global SECTSPFAT      
	.global SECTSPTRCK     
	.global NHEADS         
	.global NHIDDNSECTS    
	.global NHIDDNSECTSHI  
	.global TOTSECTSINFS   
	.global DRVNO          
	.global RESRVED        
	.global EXTSIG         
	.global DRVSERIAL      
	.global LABEL          
	.global FSTYPE

	/* Root directory */
	.global FILEDIRNAME     
	.global ATTRB           
	.global DIRRESERVED     
	.global CREATETIMEMILLI 
	.global CREATETIME      
	.global CREATEDATE      
	.global LASTACCDATE     
	.global FIRSTCLUSTHI    
	.global WRITETIME       
	.global WRITEDATE       
	.global FIRSTCLUSTLO    
	.global FILESIZE        
  
	.global ROOTDIRENTRYSZ  
	.global FILEATTRIB      	
	
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
SectPClust:	.byte 0x20
ResSects:	.word 0x20
FatTabs:	.byte 0x2
NRootDirEs:	.word 0x200
TotSects:	.word 0x0
MedDescr:	.byte 0xf8
SectsPFat:	.word 0x100
SectsPTrck:	.word 0x3f
NHeads:	.word 0xff
NHiddenSects:	.word 0x800
NhiddnSectshi:	.word 0x0
TotSectsInFS:	.int 0x200000
LogDrvNo:	.byte 0x80
Resrvd:	.byte 0x0
ExtSig:	.byte 0x29
DrvSeriNum:	.int 0xa8dd3c69
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
