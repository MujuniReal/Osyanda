typedef struct shrub_header{
    char fs_id[8];                      /* This identifies  the filesystem name */
    unsigned int total_sectors;
    unsigned char reserved_sectors;     /* reserved sectors */
    unsigned int free_sectors;          /* free sectors on disk, these csn also represent the free space on the disk */
    unsigned int start_free_sectors;    /* LBA start of free sector */

}__attribute__((packed)) Shrubs;

typedef struct block_descriptor{
    unsigned short int block_metadata;  /* free block bit 15,block 14 reserved, filename size from bit 13 to bit 6, block descriptor size from bit 5 to bit zero */
    unsigned int file_size;
}__attribute__((packed)) Shrubblock;

int main(){
    
}