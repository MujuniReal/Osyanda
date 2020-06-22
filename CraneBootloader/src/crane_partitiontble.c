#include <stdio.h>
#include <stdlib.h>

/* this code inside here could be a scenario of after creating disk headers */
typedef struct mbr_partitiontble{
    unsigned char Boot_signature;
    unsigned char Start_head;
    unsigned char Start_sector;
    unsigned char Start_cylinder;
    unsigned char System_signature;
    unsigned char End_head;
    unsigned char End_sector;
    unsigned char End_cylinder;
    unsigned int Sectors_before_partition;
    unsigned int Sectors_in_partition;
}__attribute__((packed)) mbrprtble;

int initiate_partitiontblehdr(void *Partitble){


    
    mbrprtble *MBRprtbl1 = (mbrprtble*)Partitble;
    mbrprtble *MBRprtbl2 = (mbrprtble*)(Partitble+sizeof(mbrprtble));
    mbrprtble *MBRprtbl3 = (mbrprtble*)(Partitble+(2*sizeof(mbrprtble)));
    mbrprtble *MBRprtbl4 = (mbrprtble*)(Partitble+(3*sizeof(mbrprtble)));

    printf("The_partition_table:\n\n");
    
/* first partition of disk */
    printf("Partition1:\n");
    printf("Boot_signature1:\t.byte 0x%x\n",MBRprtbl1->Boot_signature);
    printf("Start_head1:\t.byte 0x%x\n",MBRprtbl1->Start_head);
    printf("Start_sector1:\t.byte 0x%x\n",MBRprtbl1->Start_sector);
    printf("Start_cylinder1:\t.byte 0x%x\n",MBRprtbl1->Start_cylinder);
    printf("System_signature1:\t.byte 0x%x\n",MBRprtbl1->System_signature);
    printf("End_head1:\t.byte 0x%x\n",MBRprtbl1->End_head);
    printf("End_sector1:\t.byte 0x%x\n",MBRprtbl1->End_sector);
    printf("End_cylinder1:\t.byte 0x%x\n",MBRprtbl1->End_cylinder);
    printf("Sectors_before_partition1:\t.int 0x%x\n",MBRprtbl1->Sectors_before_partition);
    printf("Sectors_in_partition1:\t.int 0x%x\n\n",MBRprtbl1->Sectors_in_partition);

/* second partition of disk */
    printf("Partition2:\n");
    printf("Boot_signature2:\t.byte 0x%x\n",MBRprtbl2->Boot_signature);
    printf("Start_head2:\t.byte 0x%x\n",MBRprtbl2->Start_head);
    printf("Start_sector2:\t.byte 0x%x\n",MBRprtbl2->Start_sector);
    printf("Start_cylinder2:\t.byte 0x%x\n",MBRprtbl2->Start_cylinder);
    printf("System_signature2:\t.byte 0x%x\n",MBRprtbl2->System_signature);
    printf("End_head2:\t.byte 0x%x\n",MBRprtbl2->End_head);
    printf("End_sector2:\t.byte 0x%x\n",MBRprtbl2->End_sector);
    printf("End_cylinder2:\t.byte 0x%x\n",MBRprtbl2->End_cylinder);
    printf("Sectors_before_partition2:\t.int 0x%x\n",MBRprtbl2->Sectors_before_partition);
    printf("Sectors_in_partition2:\t.int 0x%x\n\n",MBRprtbl2->Sectors_in_partition);

/* third partition of disk */
    printf("Partition3:\n");
    printf("Boot_signature3:\t.byte 0x%x\n",MBRprtbl3->Boot_signature);
    printf("Start_head3:\t.byte 0x%x\n",MBRprtbl3->Start_head);
    printf("Start_sector3:\t.byte 0x%x\n",MBRprtbl3->Start_sector);
    printf("Start_cylinder3:\t.byte 0x%x\n",MBRprtbl3->Start_cylinder);
    printf("System_signature3:\t.byte 0x%x\n",MBRprtbl3->System_signature);
    printf("End_head3:\t.byte 0x%x\n",MBRprtbl3->End_head);
    printf("End_sector3:\t.byte 0x%x\n",MBRprtbl3->End_sector);
    printf("End_cylinder3:\t.byte 0x%x\n",MBRprtbl3->End_cylinder);
    printf("Sectors_before_partition3:\t.int 0x%x\n",MBRprtbl3->Sectors_before_partition);
    printf("Sectors_in_partition3:\t.int 0x%x\n\n",MBRprtbl3->Sectors_in_partition);

/* fourth partition of disk */
    printf("Partition4:\n");
    printf("Boot_signature4:\t.byte 0x%x\n",MBRprtbl4->Boot_signature);
    printf("Start_head4:\t.byte 0x%x\n",MBRprtbl4->Start_head);
    printf("Start_sector4:\t.byte 0x%x\n",MBRprtbl4->Start_sector);
    printf("Start_cylinder4:\t.byte 0x%x\n",MBRprtbl4->Start_cylinder);
    printf("System_signature4:\t.byte 0x%x\n",MBRprtbl4->System_signature);
    printf("End_head4:\t.byte 0x%x\n",MBRprtbl4->End_head);
    printf("End_sector4:\t.byte 0x%x\n",MBRprtbl4->End_sector);
    printf("End_cylinder4:\t.byte 0x%x\n",MBRprtbl4->End_cylinder);
    printf("Sectors_before_partition4:\t.int 0x%x\n",MBRprtbl4->Sectors_before_partition);
    printf("Sectors_in_partition4:\t.int 0x%x\n\n",MBRprtbl4->Sectors_in_partition);

    if ( MBRprtbl1->Start_sector != 0 ){        /* it has partition one */
        if ( MBRprtbl2->Start_sector == 0 ){
            return 1;   /* return disk has one partition */
        }

        /* at this point the hardisk has two partitions */
        else if ( MBRprtbl3->Start_sector == 0 ){
            return 2;    /* return disk has two partitions */
        }

        /* at this point the hardisk has 3 partitions */
        else if( MBRprtbl4->Start_sector == 0 ) {
            return 3;   /* return disk has 3 partitions */
        }
        else{
            return 4;   /* if code reaches here then our hardisk has 4 partitions which is the maximum */
        }
    }
    else{
        return 0;
    }
}

