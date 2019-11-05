<div align="center">
  <h1> How Linux Works - What every superuser should Know  </h1>
  <p> <i> Brian Ward, 2nd Edition </i> </p>
</div>

### Chapter 1 - The Big Picture
- Abstraction
- Linux is divided in 3 levels: Hardware, Kernel and Application (Processes).
- Image: Particular physical arrangement of bits in memory.
- The Kernel is in charge with four general system areas: 
    1. Determine which process will use the CPU (Context Switch and Multitasking Concept) 
    2. Track and manage memory allocation to processes or between them (MMU - Memory Management Unit; Memory Address Map is called a Page Table) 
    3. Be the interface between processes and hardware 
    4. Support syscalls from processes.
- Kernel does not manage usernames. Instead, it manages userids. A user may terminate or modify the behavior of its own processes (within certain limits), but it cannot interfere with other users’ processes. 
- Linux Directory Hierarchy:
  1. **“/bin”**: Executables or shell scripts
  2. **“/dev”**: Device files
  3. **“/etc”**: Contains setup files (network, password, boot). Many are specific to machine’s hardware.
  4. **“/home”**: Personal Directories
  5. **“/lib”**: Libraries that executables can use. There  are two types of libs: statics and shared. In the root path, there is just shared libs. 
  6. **“/proc”**: Contains information about current processes as well as some kernel parameters.
  7. **“/sys”**: Provides a device and system interface.
  8. **“/sbin”**: System executables related to system management.
  9. **“/tmp”**: A storage area for smaller, temporary files that you don’t care much about.
  10. **“/usr”**: Despite the name, there are no user files. It contains a large directory hierarchy, including the bulk of the Linux System.
  11. **“/var”**: The variable subdirectory, where programs record runtime information.
  12. **“/boot”**: Contain kernel boot loader files (Only the very first stage of the Linux startup procedure)
  13. **“/media”**: A base attachment point for removable media such as flash drives.
  14. **“/opt”**: This may contain third-party softwares.
  
### Chapter 3 - Devices
- How the kernel sends a message to a user-space process through udev.
- Device files = Device nodes
H- ow to identify a device file? Look in the file permissions. If started with ‘b’ (block), ‘c’ (character), ‘p’ (pipe) or ‘s’ (socket), you’re dealing with a device file.
- A device may have a different name between reboots, because the kernel assigns devices in order which they are found.
- ‘/dev’: User processes can use the device.
- ‘/sys/devices’: View information and manage the device.
- Why hard drives in Linux receives the prefix name convention of ‘sd’? ‘sd’ stands for SCSI disk (Small Computer System Interface).
- Conventions:
  1. ‘sd’: Hard Disks
  2. ‘sr’: DVD/CD Drives
  3. ‘hd’: Common on older versions of the Linux kernel and with older hardware.
- ‘dev/tty1’ (the first virtual console); ‘dev/pts/0’ (the first pseudoterminal device).
- Audio devices: ‘/dev/snd/*’, ‘/dev/dsp’, ‘/dev/audio’...
- The Linux Kernel can send notifications to a user-space process (called udevd) upon detecting a new device on the system. udevd adds a symbolic link for the incoming device.

### Chapter 4 - Disks and Filesystems
- To access data, Linux uses the system of layers.
- MBR (Master Boot Record): Traditional Table. Limited by four primary partitions. Extended partitions can be subdivided into Logical Partitions.
- GPT (Global Unique Identifier Partition Table)
- FUSE (File System in User Space) allows user-space filesystems in user-space.
- Filesystems Types:
  1. ext4 (Fourth Extended Filesystem)
  2. ISO9660
  3. FAT (msdos, vfat, umsdos): Microsoft systems.
  4. HFS+ (hfsplus): Macintosh systems.
- Mounting: the process of attaching a filesystem. In order to mount a filesystem, you must know the following (“Mount a device on a mount point”)
- The filesystem device.
- The filesystem type.
- The mount point.
- Filesystems UUID (Universal Unique Identifier) - Command ‘blkid’ shows uuid.
<div align='center'> 
  <img src="https://i.imgur.com/vZxiWij.png" width="800px"> 
</div>
- “/etc/fstab” Filesystem Table: 

