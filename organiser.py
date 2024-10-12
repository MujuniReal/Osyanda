import subprocess
import re
class Organiser:
    mbr = None
    selected_partition = None
    working_dir = None
    disk_path = None
    dev_loop_path = None

    def __init__(self):
        self.working_dir = subprocess.check_output("pwd", shell=True).decode("utf-8").strip()
        # print(self.working_dir)
        if self.disk_exists():
            if not self.check_blocks():
                self.avail_disk()
        else:
            self.create_disk()
            self.avail_disk()

    def create_disk(self):
        subprocess.call("dd if=/dev/zero of=disk.img bs=1024k seek=500 count=0", shell=True)
        subprocess.call("parted disk.img mklabel msdos", shell=True)

    def avail_disk(self):
        subprocess.call("losetup -f disk.img", shell=True)
        # losetup -d /dev/loop29 Unloop

    def check_blocks(self):
        self.disk_path =  "%s/disk.img" %(self.working_dir)
        dev_outp = subprocess.check_output("losetup -a", shell=True).decode("utf-8")
        dev_infos = dev_outp.split("\n")
        for info_line in dev_infos:
            is_matched = re.search(self.disk_path, info_line)
            if(is_matched != None):
                self.dev_loop_path = info_line.split(":")[0]
                return True
        return False
    
    def disk_exists(self):
        try:
            f = open('disk.img', 'r')
            f.close()
            return True
        except:
            return False


#NEXT IS HOW TO PARTITION THE SETUP LOOP DEVICE

org = Organiser()

# org.create_disk()
