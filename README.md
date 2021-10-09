# Osyanda
The Osyanda project is a tech project, the project's main aim is building the first computer
in Africa. Along with that the computer will need an operating system, the pieces of source code
on this repository contain bootloading code, and the operating system kernel, the operating system
itself.

Operating system from the Osyanda project

Crane bootloader - Bootloader

#CraneBootloader
The software that is starting the Operating system from the point of switching on your computer.

Impala  	 - Kernel 

#Impala
This is the Operating system itself, The fastest kernel on the planet, faster than linux. As fast as
an impala running away from a predator.
The Impala kernel is believed tobe faster than the Linux kernel
because it is 75% Assembly language which is faster than the C language


#Documentation
There is various documentation in this repository, find the documentation content in the documentation
directories/folders found in each subfolder that is cranebootloader/documentation and impala/documentation;
the documentation of the Cranebootloader and Impala kernel respectively.
The documentation/index.txt files define what is contained in each documentation file in the involved
documentation directory.


Building and running the software

The following are required to be installed on your system inorder to build and run the software;
- The GNU Compiler Collection (GCC) / Mingw for users on windows
- Bochs x86 emulator
- Disk image creation tool; fallocate for GNU/Linux users and Disk Image Creation tool for users on windows comes
with the bochs software.

Building the software;

1) Making a disk Image of a storage medium;
Make a disk image of appropriately 512MBs using the disk creation tool

On GNU/Linux;
* With the fallocate program installed, open terminal and run ``fallocate -l 512M osyanda.img``
This will create a disk image called "osyanda.img", this in a realtime environment represents
a storage device HDD/flash drive
* Next format the disk image to FAT16, by running **``mkfs.fat -F 16 -I osyanda.img``**, This is a very
important step as the FAT16 filesystem has been greatly used in the project.

On Windows;
Disk Image creation tool that comes with bochs
* Run the disk image cretaion tool from start menu
* Select the option number matching the option **Create new floppy or hard disk image**
* Next choose the type of disk image to create either floppy or hardisk choose **hd**
* Next choose the type of image to create as **flat**
* Next type in the size of sectors that should exist in the image **512**
* Next enter the disk image capacity in megabytes type **512**
* Next specify the path where you wish to save the disk image including the disk image
filename like **C:\Users\UsernameX\osyanda.img** with this path, replace **UsernameX** with your exact
username on your windows machine and then hit the enter Key to finish
The disk image **osyanda.img** will be stored in your home directory


2) Building and Running Impala

On GNU/Linux;
* Open your commandline terminal and navigate to the root directory of the Osyanda project **cd Osyanda**.
* Run the ``make config`` command to publish required makefile variables.
* Next, run the ``make`` command to start the build process, this should take a while.
* Mount **(as superuser)** the previously created disk image ``sudo mount osyanda.img /mnt``.
* Run the ``lsblk`` command to note the device name, endevour to locate the disk name matching with its mount point
example;
	**``loop22   7:22   0 511.9M  0 loop /mnt``**
that is an output of the **lsblk** command you can notice that the system identifies our mounted disk image as **loop22**,
take note of the device name.
* Next, run (as superuser) ``sudo dd if=cranebootloader/crane.mbr of=/dev/devicename`` replace ``devicename`` with the previously
noted device name, following the example its ``loop22`` so the command should look like this;
``sudo dd if=cranebootloader/crane-disk of=/dev/loop22``.
* **Copy the required files; cranebl.img and impala.img to the mounted device,(remember our mount directory "/mnt")**, as superuser
run ``sudo cp cranebootloader/cranebl.img /mnt``, run next command ``sudo cp impala/impala.img /mnt``.
* If all is successful with no errors, unmount the device as super user by running ``sudo umount /mnt``
* Make sure that bochs is installed on your GNU/Linux machine correctly.
* Goto the root directory of the Osyanda project and open to edit the **amOsyandaLinux** file, search for the line that contains
the phrase **path** it should look like ``path=**path-to-your-disk-image**``,if the path to your disk image file you created previously
looks like this **/home/user/osyanda.img** then edit the line in the amOsyandaLinux file to look like this;
      **path="/home/user/osyanda.img"**
* Save the file,close it and run the command ``bochs -f amOsyandaLinux``

On Windows
