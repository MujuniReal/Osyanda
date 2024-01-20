import subprocess

class Organiser:
    mbr = None
    selected_partition = None

    def __init__(self):
        pass

    def create_disk(self):
        subprocess.call("dd if=/dev/zero of=disk.img bs=1024k seek=500 count=0", shell=True)
        subprocess.call("parted disk.img mklabel msdos", shell=True)
        subprocess.call("losetup -f disk.img", shell=True)

    def check_blocks(self):
        # Do a pwd then catch the path matching our disk
        pass




org = Organiser()

org.create_disk()