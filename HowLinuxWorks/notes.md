<div align="center">
  <h3> How Linux Works - What every superuser should Know  </h3>
  <p> <i> Brian Ward, 2nd Edition </i> </p>
</div>

## Chapter 1 - The Big Picture
- Abstraction
- Linux is divided in 3 levels: Hardware, Kernel and Application (Processes).
- Image: Particular physical arrangement of bits in memory.
- The Kernel is in charge with four general system areas: 1) Determine which process will use the CPU (Context Switch and Multitasking Concept); 2) Track and manage memory allocation to processes or between them (MMU - Memory Management Unit; Memory Address Map is called a Page Table); 3) Be the interface between processes and hardware; 4) Support syscalls from processes.
- Kernel does not manage usernames. Instead, it manages userids. A user may terminate or modify the behavior of its own processes (within certain limits), but it cannot interfere with other users’ processes. 
- Linux Directory Hierarchy:
1. “/bin”: Executables or shell scripts
2. “/dev”: Device files
3. “/etc”: Contains setup files (network, password, boot). Many are specific to machine’s hardware.
4. “/home”: Personal Directories
5. “/lib”: Libraries that executables can use. There  are two types of libs: statics and shared. In the root path, there is just shared libs. 
6. “/proc”: Contains information about current processes as well as some kernel parameters.
7. “/sys”: Provides a device and system interface.
8. “/sbin”: System executables related to system management.
9. “/tmp”: A storage area for smaller, temporary files that you don’t care much about.
10. “/usr”: Despite the name, there are no user files. It contains a large directory hierarchy, including the bulk of the Linux System.
11. “/var”: The variable subdirectory, where programs record runtime information.
12. “/boot”: Contain kernel boot loader files (Only the very first stage of the Linux startup procedure)
13. “/media”: A base attachment point for removable media such as flash drives.
14. “/opt”: This may contain third-party softwares.