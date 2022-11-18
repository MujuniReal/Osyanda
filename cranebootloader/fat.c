#include <stdio.h>
#include <string.h>
#include "types.h"
#include "fat.h"

typedef struct _fatbpb1216 fatbpb1216;

void handleFat(char *mbr){

}


int createFat1216BpbSrc(char *fatbpb){

    fatbpb1216 *bpb = (fatbpb1216*)fatbpb;
    char devoem[9];
    char volabel[12];
    char fstype[9];

    memset((char*)&devoem,'\0',sizeof(devoem));
    memset((char*)&volabel,'\0',sizeof(volabel));
    memset((char*)&fstype,'\0',sizeof(fstype));


    strncpy((char*)&devoem, (char*)&bpb->devOEM,sizeof(bpb->devOEM));
    strncpy((char*)&volabel, (char*)&bpb->VolLabel,sizeof(bpb->VolLabel));
    strncpy((char*)&fstype, (char*)&bpb->FSType,sizeof(bpb->FSType));

    /* printf("devOEM: %s\n",devoem); */
    /* printf("ByPSect %d\n",bpb->ByPSect); */
    /* printf("SectPClust %d\n",bpb->SectPClust); */
    /* printf("ResSects %d\n",bpb->ResSects); */
    /* printf("FatTabs %d\n",bpb->FatTabs); */
    /* printf("NRootDirEs %d\n",bpb->NRootDirEs); */
    /* printf("TotSects %d\n",bpb->TotSects); */
    /* printf("MedDescr 0x%x\n",bpb->MedDescr); */
    /* printf("SectsPFat %d\n",bpb->SectsPFat); */
    /* printf("SectsPTrck %d\n",bpb->SectsPTrck); */
    /* printf("NHeads %d\n",bpb->NHeads);	 */
    /* printf("NHiddenSects 0x%x\n",bpb->NHiddenSects); */
    /* printf("NhiddnSectshi 0x%x\n",bpb->NhiddnSectshi); */
    /* printf("TotSectsInFS 0x%x\n",bpb->TotSectsInFS); */
    /* printf("LogDrvNo 0x%x\n",bpb->LogDrvNo); */
    /* printf("Resrvd %d\n",bpb->Resrvd); */
    /* printf("ExtSig 0x%x\n",bpb->ExtSig); */
    /* printf("DrvSeriNum 0x%x\n",bpb->DrvSeriNum); */
    /* printf("VolLabel %s\n",volabel); */
    /* printf("FSType %s\n",fstype); */

    FILE *Fathdrfile;
    Fathdrfile = fopen("./fatbpb.s","w");

    if(strlen(devoem) == 8){
       fprintf(Fathdrfile,"devOEM:\t.ascii \"%s\"\n",devoem);
    }
    else{

      /* If devOEM is having names with length 7 */
      fprintf(Fathdrfile,"devOEM:\t.asciz \"%s\"\n",devoem);
    }
  
    fprintf(Fathdrfile,"ByPSect:\t.word 0x%x\n",bpb->ByPSect);
    fprintf(Fathdrfile,"SectPClust:\t.byte 0x%x\n",bpb->SectPClust);
    fprintf(Fathdrfile,"ResSects:\t.word 0x%x\n",bpb->ResSects);
    fprintf(Fathdrfile,"FatTabs:\t.byte 0x%x\n",bpb->FatTabs);
    fprintf(Fathdrfile,"NRootDirEs:\t.word 0x%x\n",bpb->NRootDirEs);
    fprintf(Fathdrfile,"TotSects:\t.word 0x%x\n",bpb->TotSects);
    fprintf(Fathdrfile,"MedDescr:\t.byte 0x%x\n",bpb->MedDescr);
    fprintf(Fathdrfile,"SectsPFat:\t.word 0x%x\n",bpb->SectsPFat);
    fprintf(Fathdrfile,"SectsPTrck:\t.word 0x%x\n",bpb->SectsPTrck);
    fprintf(Fathdrfile,"NHeads:\t.word 0x%x\n",bpb->NHeads);
    fprintf(Fathdrfile,"NHiddenSects:\t.word 0x%x\n",bpb->NHiddenSects);
    fprintf(Fathdrfile,"NhiddnSectshi:\t.word 0x%x\n",bpb->NhiddnSectshi);
    fprintf(Fathdrfile,"TotSectsInFS:\t.int 0x%x\n",bpb->TotSectsInFS);
    fprintf(Fathdrfile,"LogDrvNo:\t.byte 0x%x\n",bpb->LogDrvNo);
    fprintf(Fathdrfile,"Resrvd:\t.byte 0x%x\n",bpb->Resrvd);
    fprintf(Fathdrfile,"ExtSig:\t.byte 0x%x\n",bpb->ExtSig);
    fprintf(Fathdrfile,"DrvSeriNum:\t.int 0x%x\n",bpb->DrvSeriNum);
    fprintf(Fathdrfile,"VolLabel:\t.ascii \"%s\"\n",volabel);
    fprintf(Fathdrfile,"FSType:\t.ascii \"%s\"\n",fstype);



    fclose(Fathdrfile);
    
    return 0;
}
