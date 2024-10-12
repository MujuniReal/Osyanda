import subprocess

disk_info = subprocess.check_output("fdisk -lu 1GBPartitioned.img", shell=True)
disk_info = disk_info.decode("utf-8")
disk_info_list = disk_info.split("\n")

# Units: sectors of 1 * 512 = 512 bytes
sect_info_list = disk_info_list[1].split('bytes')[0].split(" ")
sect_i = len(sect_info_list) - 1
while(len(sect_info_list[sect_i]) == 0):
    sect_i -= 1

i = len(disk_info_list) - 1
while(len(disk_info_list[i]) == 0):
    i -= 1
# disk.img       2048 2007039 2004992  979M  e W95 FAT16 (LBA)
disk_info_line = disk_info_list[i]
line_info_list = disk_info_line.split(" ")
indx = 1
while(len(line_info_list[indx]) == 0):
    indx += 1

print(line_info_list[indx])
print(sect_info_list[sect_i])

# Mount the partition
# sudo losetup -o 28672 /dev/loop0 sda.img