#include <stdio.h>
#include <string.h>
#include <sys/types.h>

//#include <bpbsize.h>

#define MAXFATBPBSIZE 90

/*#define JMPCODE_NOP_SIZE 3
#define DEVOEM_STRSIZE 8
//#define FAT1216_BPBSIZE 25
#define FAT1216_EXTENDEDBPBSIZE 26
#define VOL_LABEL_STR_SIZE 11
#define FILESYSTEM_ID_STR_SIZE 8 */
//#define VOL_LABEL_LOCATION ((JMPCODE_NOP_SIZE + DEVOEM_STRSIZE + FAT1216_BPBSIZE + FAT1216_EXTENDEDBPBSIZE + ) - (VOL_LABEL_STR_SIZE + FILESYSTEM_ID_STR_SIZE))
/* this content below here is for the header file of the organiser program */

typedef struct fat_12_6{
        unsigned short int jmpcode;
        unsigned char nopinstr;
        char devOEM[8];
        unsigned short int ByPSect;             //Bytes per sector
        char SectPClust;                        //Sectors per cluster
        unsigned short int ResSects;            //Reserved Sectors
        char FatTabs;                           //Number of Fat tables
        unsigned short int NRootDirEs;          //No of root dir entries
        unsigned short int TotSects;            //Total number of sectors
        unsigned char MedDescr;                         //The media descriptor
        unsigned short int SectsPFat;           //Sects per fat
        unsigned short SectsPTrck;              //Sectors Per Track
        unsigned short int NHeads;              //Number of heads
        unsigned short int NHiddenSects;        //Hidden sects low
        unsigned short int NhiddnSectshi;       //Hidden sects high
        unsigned int TotSectsInFS;              //Total Sects in FS
        char LogDrvNo;                          //Logical Drive Number
        char Resrvd;                            //Reserved
        char ExtSig;                            //Extended signature
        unsigned int DrvSeriNum;                                //This is the drive Serial Number
        char VolLabel[11];
        char FSType[8];

}__attribute__((packed)) fat_126hdr;
typedef struct fat_32{
        unsigned short int jmpcode;
        unsigned char nopinstr;
        char devOEM[8];
        unsigned short int ByPSect;             //Bytes per sector
        char SectPClust;                        //Sectors per cluster
        unsigned short int ResSects;            //Reserved Sectors
        char FatTabs;                           //Number of Fat tables
        unsigned short int NRootDirEs;          //No of root dir entries
        unsigned short int TotSects;            //Total number of sectors
        unsigned char MedDescr;                         //The media descriptor
        unsigned short Reserved1;
        unsigned short SectsPTrck;              //Sectors Per Track
        unsigned short int NHeads;              //Number of heads
        unsigned short int NHiddenSects;        //Hidden sects low
        unsigned short int NhiddnSectshi;       //Hidden sects high
        unsigned int TotSectsInFS;              //Total Sects in FS
        unsigned int SectsPFat;           //Sects per fat
        unsigned short int FATmirroring;
        unsigned short int Himirroring;
        unsigned int Root_dirStart;
        unsigned short int FSInfo;
        unsigned short int MBRCopyLocation;
        char Reserved2[12];
        char LogDrvNo;                          //Logical Drive Number
        char Resrvd3;                            //Reserved
        char ExtSig;                            //Extended signature
        unsigned int DrvSeriNum;                                //This is the drive Serial Number
        char VolLabel[11];
        char FSType[8];

}__attribute__((packed)) fat_32hdr;
/* this will be code coming from the prep-disk arguement */
/* so this is a library or a function coming from a library */
/* it doesnt deserve tobe with a main function but for now lets just give it we will remove it */
/* another alternative is prep-disk disk */
/* in preparing disk involves many things this is one of them,, making a header file with disk layout */

int fat1216prep_disk_header(void *fatbpb){

    /*we will replace these inside the arguements to disk labels received from main program */
    //*strncpy((&devOEM+), const char *src, size_t n);
    /*cater for if memory was not initialised with zeros in these variables we are using */

   fat_126hdr *MBRdat = (fat_126hdr*)fatbpb;

    /* cater for strings */
    char tmp_devOEM[9];
    char tmp_VolLabel[12];
    char tmp_FSType[9];
    /* initialize variable buffers with zeros */
    memset(tmp_devOEM,'\0',sizeof(tmp_devOEM)); 
    memset(tmp_VolLabel,'\0',sizeof(tmp_VolLabel));
    memset(tmp_FSType,'\0',sizeof(tmp_FSType));

    strncpy(tmp_devOEM,MBRdat->devOEM,8);
    strncpy(tmp_VolLabel,MBRdat->VolLabel,11);
    strncpy(tmp_FSType,MBRdat->FSType,8);

    //FILE *Fathdrfile;
    //Fathdrfile = fopen("./fatstruct.h","w");
    
    
    printf("FATstruct:\n\n");

    /* this if statement is to cater for the last character in the device OEM name */
    if(strlen(tmp_devOEM) == 8){
        printf("devOEM:\t\t\t.ascii  \"%s\"\n",tmp_devOEM);
    }
    else{
        printf("devOEM:\t\t\t.asciz  \"%s\"\n",tmp_devOEM);
    }
    printf("ByPSect:\t.word 0x%x\n",MBRdat->ByPSect);
    printf("SectPClust:\t.byte 0x%x\n",MBRdat->SectPClust);
    printf("ResSects:\t.word 0x%x\n",MBRdat->ResSects);
    printf("FatTabs:\t.byte 0x%x\n",MBRdat->FatTabs);
    printf("NRootDirEs:\t.word 0x%x\n",MBRdat->NRootDirEs);
    printf("TotSects:\t.word 0x%x\n",MBRdat->TotSects);
    printf("MedDescr:\t.byte 0x%x\n",MBRdat->MedDescr);
    printf("SectsPFat:\t.word 0x%x\n",MBRdat->SectsPFat);
    printf("SectsPTrck:\t.word 0x%x\n",MBRdat->SectsPTrck);
    printf("NHeads:\t.word 0x%x\n",MBRdat->NHeads);
    printf("NHiddenSects:\t.word 0x%x\n",MBRdat->NHiddenSects);
    printf("NhiddnSectshi:\t.word 0x%x\n",MBRdat->NhiddnSectshi);
    printf("TotSectsInFS:\t.int 0x%x\n",MBRdat->TotSectsInFS);
    printf("LogDrvNo:\t.byte 0x%x\n",MBRdat->LogDrvNo);
    printf("Resrvd:\t.byte 0x%x\n",MBRdat->Resrvd);
    printf("ExtSig:\t.byte 0x%x\n",MBRdat->ExtSig);
    printf("DrvSeriNum:\t.int 0x%x\n",MBRdat->DrvSeriNum);
    printf("VolLabel:\t.ascii \"%s\"\n",tmp_VolLabel);
    printf("FSType:\t.ascii \"%s\"\n",tmp_FSType);



    //fclose(Fathdrfile);
    
    return 0;
}

int fat32prep_disk_header(void *fatbpb){
    
    fat_32hdr *MBRdat = (fat_32hdr*)fatbpb;
    
    //FILE *Fathdrfile;
    //Fathdrfile = fopen("./fatstruct.h","w");

    /* cater for strings */
    char tmp_devOEM[9];
    char tmp_VolLabel[12];
    char tmp_FSType[9];
    /* initialize variable buffers with zeros */
    memset(tmp_devOEM,'\0',sizeof(tmp_devOEM));
    memset(tmp_VolLabel,'\0',sizeof(tmp_VolLabel));
    memset(tmp_FSType,'\0',sizeof(tmp_FSType));

    strncpy(tmp_devOEM,MBRdat->devOEM,8);
    strncpy(tmp_VolLabel,MBRdat->VolLabel,11);
    strncpy(tmp_FSType,MBRdat->FSType,8);

    printf("FATstruct:\n\n");

    /* this if statement is to cater for the last character in the device OEM name */
    if(strlen(tmp_devOEM) == 8){
        printf("devOEM:\t\t\t.ascii  \"%s\"\n",tmp_devOEM);
    }
    else{
        printf("devOEM:\t\t\t.asciz  \"%s\"\n",tmp_devOEM);
    }

    printf("ByPSect:\t\t\t.word  0x%x\n",MBRdat->ByPSect);             
    printf("SectPClust:\t\t\t.word  0x%x\n",MBRdat->SectPClust);                        
    printf("ResSects:\t\t\t.word  0x%x\n",MBRdat->ResSects);            
    printf("FatTabs:\t\t\t.word  0x%x\n",MBRdat->FatTabs);                           
    printf("NRootDirEs:\t\t\t.word  0x%x\n",MBRdat->NRootDirEs);          
    printf("TotSects:\t\t\t.word  0x%x\n",MBRdat->TotSects);            
    printf("MedDescr:\t\t\t.word  0x%x\n",MBRdat->MedDescr);                         
    printf("Reserved1:\t\t\t.word  0x%x\n",MBRdat->Reserved1);
    printf("SectsPTrck:\t\t\t.word  0x%x\n",MBRdat->SectsPTrck);              
    printf("NHeads:\t\t\t.word  0x%x\n",MBRdat->NHeads);              
    printf("NHiddenSects:\t\t\t.word  0x%x\n",MBRdat->NHiddenSects);        
    printf("NhiddnSectshi:\t\t\t.word  0x%x\n",MBRdat->NhiddnSectshi);       
    printf("TotSectsInFS:\t\t\t.word  0x%x\n",MBRdat->TotSectsInFS);              
    printf("SectsPFat:\t\t\t.word  0x%x\n",MBRdat->SectsPFat);           
    printf("FATmirroring:\t\t\t.word  0x%x\n",MBRdat->FATmirroring);
    printf("Himirroring:\t\t\t.word  0x%x\n",MBRdat->Himirroring);
    printf("Root_dirStart:\t\t\t.word  0x%x\n",MBRdat->Root_dirStart);
    printf("FSInfo:\t\t\t.word  0x%x\n",MBRdat->FSInfo);
    printf("MBRCopyLocation:\t\t\t.word  0x%x\n",MBRdat->MBRCopyLocation);
    //printf("Reserved2:\t\t\t.word  0x%x\n",MBRdat->Reserved2);
    printf("LogDrvNo:\t\t\t.word  0x%x\n",MBRdat->LogDrvNo);                          
    printf("Resrvd3:\t\t\t.word  0x%x\n",MBRdat->Resrvd3);                            
    printf("ExtSig:\t\t\t.word  0x%x\n",MBRdat->ExtSig);                            
    printf("DrvSeriNum:\t\t\t.word  0x%x\n",MBRdat->DrvSeriNum);                                
    printf("VolLabel:\t\t\t.ascii  \"%s\"\n",tmp_VolLabel);
    printf("FSType:\t\t\t.ascii  \"%s\"\n",tmp_FSType);

    //fclose(Fathdrfile);
    return 0;
}

int initiate_fatprep(void *fatbpb){
    char *tmpfat = "FAT32";
    if( strncmp(tmpfat,(fatbpb+(MAXFATBPBSIZE - 8)),5) == 0 ){
        fat32prep_disk_header(fatbpb);
    }
    else{ /*62 is the maximum that is bpb + jump instruction + nop + devOEM(8)  one for fat12 and 16 */
        fat1216prep_disk_header(fatbpb);
        }

    return 0;
}