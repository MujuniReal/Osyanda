import subprocess
import re

blk_info = subprocess.check_output("lsblk", shell=True)
blk_info = blk_info.decode("utf-8")
# print(blk_info)
disk_info_list = blk_info.split("\n")

looper = 0
loop_num_list = []
for info_line in disk_info_list:
    inf_lne = info_line.strip(' ')
    if(inf_lne[:4] == 'loop'):
        loop_num_list.append(int(info_line.split(" ")[0].split('loop')[1]))
        
loop_num_list.sort()
new_blk = loop_num_list.pop() + 1

print(new_blk)


def activate_block(blk_num):
    subprocess.check_output("lsblk", shell=True)