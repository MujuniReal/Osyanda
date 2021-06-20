#include <stdio.h>

#include <sys/types.h>

#include <bpbsize.h>


/*#define JMPCODE_NOP_SIZE 3
#define DEVOEM_STRSIZE 8
//#define FAT1216_BPBSIZE 25
#define FAT1216_EXTENDEDBPBSIZE 26
#define VOL_LABEL_STR_SIZE 11
#define FILESYSTEM_ID_STR_SIZE 8 */
//#define VOL_LABEL_LOCATION ((JMPCODE_NOP_SIZE + DEVOEM_STRSIZE + FAT1216_BPBSIZE + FAT1216_EXTENDEDBPBSIZE + ) - (VOL_LABEL_STR_SIZE + FILESYSTEM_ID_STR_SIZE))
/* this content below here is for the header file of the organiser program */

char devOEM[9];
short int ByPSect;
unsigned char SectPClust;
short int ResSects;
char FatTabs;
short int NRootDirEs;
short int TotSects;
unsigned char MedDescr;
short int SectsPFat;
short int SectsPTrck;
short int NHeads;	
short int NHiddenSects;
short int NhiddnSectshi;
int TotSectsInFS;
unsigned char LogDrvNo;
unsigned char Resrvd;
unsigned char ExtSig;
int DrvSeriNum;
char VolLabel[12];
char FSType[9];



/* this will be code coming from the prep-disk arguement */
/* so this is a library or a function coming from a library */
/* it doesnt deserve tobe with a main function but for now lets just give it we will remove it */
/* another alternative is prep-disk disk */
/* in preparing disk involves many things this is one of them,, making a header file with disk layout */

int fat1216prep_disk(char *fatbpb){

    /*we will replace these inside the arguements to disk labels received from main program */
    //*strncpy((&devOEM+), const char *src, size_t n);
    /*cater for if memory was not initialised with zeros in these variables we are using */

   
    __asm__("mov %0,%%esi"::"r" (fatbpb+3));    /*because we are using them here */
    __asm__("mov %0,%%edi"::"r" (&devOEM));
    __asm__(
	"movl $0x8,%ecx;"
	"rep movsb;"
		    );      /* after this code the %esi is increamented automatically */
    __asm__("movw (%%esi),%0":"=r" (ByPSect));
    __asm__("movb 0x2(%%esi),%0":"=r" (SectPClust));
    __asm__("movw 0x3(%%esi),%0":"=r" (ResSects));
    __asm__("movb 0x5(%%esi),%0":"=r" (FatTabs));
    __asm__("movw 0x6(%%esi),%0":"=r" (NRootDirEs));
    __asm__("movw 0x8(%%esi),%0":"=r" (TotSects));
    __asm__("movb 0xa(%%esi),%0":"=r" (MedDescr));
    __asm__("movw 0xb(%%esi),%0":"=r" (SectsPFat));
    __asm__("movw 0xd(%%esi),%0":"=r" (SectsPTrck));
    __asm__("movw 0xf(%%esi),%0":"=r" (NHeads));
    __asm__("movw 0x11(%%esi),%0":"=r" (NHiddenSects));
    __asm__("movw 0x13(%%esi),%0":"=r" (NhiddnSectshi));
    __asm__("movl 0x15(%%esi),%0":"=r" (TotSectsInFS));
    __asm__("movb 0x19(%%esi),%0":"=r" (LogDrvNo));
    __asm__("movb 0x1a(%%esi),%0":"=r" (Resrvd));
    __asm__("movb 0x1b(%%esi),%0":"=r" (ExtSig));
    __asm__("movl 0x1c(%%esi),%0":"=r" (DrvSeriNum));
    /* the location of the volume system name is 0x1d after the above */
    /*strings below here */

    __asm__("movl %0,%%esi"::"r" (fatbpb+VOLUMELABEL_STRLOCATION));
    __asm__("mov %0,%%edi;"::"r" (&VolLabel));
    __asm__(
        "movl $0xb,%ecx;"
        "rep movsb;"
        );
    __asm__("movl %0,%%esi"::"r" (fatbpb+FSNAME_STRLOCATION));
    __asm__("mov %0,%%edi;"::"r" (&FSType));
    __asm__(
        "movl $0x8,%ecx;"
        "rep movsb;"
        );
    FILE *Fathdrfile;
    Fathdrfile = fopen("./fatstruct.h","w");

    //__asm__("movw (%%esi),%0":"=r" (FSType));
    //printf("jumpcode:\t.word 0x%x",jumpcode);
    fprintf(Fathdrfile,"devOEM:\t.asciz \"%s\"\n",devOEM);
    fprintf(Fathdrfile,"ByPSect:\t.word 0x%x\n",ByPSect);
    fprintf(Fathdrfile,"SectPClust:\t.byte 0x%x\n",SectPClust);
    fprintf(Fathdrfile,"ResSects:\t.word 0x%x\n",ResSects);
    fprintf(Fathdrfile,"FatTabs:\t.byte 0x%x\n",FatTabs);
    fprintf(Fathdrfile,"NRootDirEs:\t.word 0x%x\n",NRootDirEs);
    fprintf(Fathdrfile,"TotSects:\t.word 0x%x\n",TotSects);
    fprintf(Fathdrfile,"MedDescr:\t.byte 0x%x\n",MedDescr);
    fprintf(Fathdrfile,"SectsPFat:\t.word 0x%x\n",SectsPFat);
    fprintf(Fathdrfile,"SectsPTrck:\t.word 0x%x\n",SectsPTrck);
    fprintf(Fathdrfile,"NHeads:\t.word 0x%x\n",NHeads);
    fprintf(Fathdrfile,"NHiddenSects:\t.word 0x%x\n",NHiddenSects);
    fprintf(Fathdrfile,"NhiddnSectshi:\t.word 0x%x\n",NhiddnSectshi);
    fprintf(Fathdrfile,"TotSectsInFS:\t.int 0x%x\n",TotSectsInFS);
    fprintf(Fathdrfile,"LogDrvNo:\t.byte 0x%x\n",LogDrvNo);
    fprintf(Fathdrfile,"Resrvd:\t.byte 0x%x\n",Resrvd);
    fprintf(Fathdrfile,"ExtSig:\t.byte 0x%x\n",ExtSig);
    fprintf(Fathdrfile,"DrvSeriNum:\t.int 0x%x\n",DrvSeriNum);
    fprintf(Fathdrfile,"VolLabel:\t.ascii \"%s\"\n",VolLabel);
    fprintf(Fathdrfile,"FSType:\t.ascii \"%s\"\n",FSType);


    //printf("ByPsect = %d\n",ByPSect);

    fclose(Fathdrfile);
    
    return 0;
}
