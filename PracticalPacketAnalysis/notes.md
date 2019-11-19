<div align="center">
   <h1> Practical Packet Analysis, 3rd Edition </h1>
   <p> <i> Chris Sanders </i> </p>
</div>

<div align="center">
   <img src="./images/capa.png" width="600px">
</div>

## Introduction
- *The first half of this book gives you the knowledge you'll need to understand packet analysis and Wireshark. The second half of the book is devoted entirely to practical cases that you could easily encounter in day-to-day network management*.

## Chapter 1 - Packet Analysis and Network Basics
- The more we can do at the packet level, the more we can control our network and solve problems.
- *Packet Analysis*: Describes the process of capturing and interpreting live data as it flows across a network in order to better understand what is happening on that network. It can help with:
    - *Understanding network characteristics*
    - *Learning who is on a network*
    - *Determining who or what is utilizing available bandwidth*
    - *Identifying peak network usage times*
    - *Identifying malicious activity*
    - *Finding unsecured and bloated applications*
- *Packet Sniffers*: Wireshark, tcpdump...
    - How do they work?
        - Cooperative effort between software and hardware.
        1) *Collection*: Switch the network interface into *promiscuous mode*. The packet sniffer collects raw binary data from the wire.
        2) *Conversion*: Raw binary data is converted into a readable form. 
        3) *Analysis*: Packet sniffer conducts an analysis of the captured and converted data. It verifies the protocol of the captured network data. 

## Chapter 2 - Tapping into the wire
- A key decision for effective packet analysis is where to physically position a packet-sniffer to appropriately capture the data.
- Sniffing packets on a network requires a Network Interface Card (NIC) that supports a promiscuous mode driver (Allow a NIC to view all packets crossing the wire).
    - When operating in promiscuous mode, the NIC passes the packet it sees to the host's processor, regardless of addressing. Once the packet makes it to the CPU, a packet-sniffing application can grab it for analysis. 
    - *wireshark* libpcap/WinPcap driver: Switch your NIC directly into promiscuous mode.
- Ways to capture traffic from a switched network:
    1) *Port mirroring or Port spanning*: Forces the switch to copy all traffic on one port to another port. Downside: It's not reliable enough.
    2) *Hubbing out*: Place the target device and your analyzer system on the same network segment by pluggin them both directly into a hub. Downside: You need physial access to the switch. Hubs are antiquated.
    3) *Using a tap*: A tap is a hardware device that you can place between two points on your cabling system to capture the packets between those two points. Plaing tap between the switch and the router allow us monitoring entire network (commonly used in security monitoring).
    4) *ARP caching poisoning or ARP spoofing*: Transmitting computer sends an ARP request to the data link layer broadcast address ff:ff:ff:ff:ff:ff. The packet basically asks: *"Which IP address owns the xx:xx:xx:xx:xx:xx MAC address?"*. It's an Advanced form of tapping. It works by sending ARP messages to an Ethernet switch or router with fake MAC addresses in order to intercept the traffic of another computer. It only works on Local Area Networks that uses ARP for IP address resolution.
- A network map, or network diagram, shows all technical resources on a network and how they are connected.

## Chapter 3 - Introduction to Wireshark
- Creator: Gerald Combs, a computer science graduate of the University of Missouri at Kansas City.
- Wireshark supports more than 1000 protocols.
- Wireshar installation on Ubuntu: *sudo apt-get install wireshark wireshark-qt*
- To find anomalies in daily network activity, you must know what normal daily network activity looks like. 
- Wireshark main panel:
    - *Packet List*: Displays table containing all packets in the current capture file. 
    - *Packet Details*: Hierarchical display of information about a single packet and can be collapsed or expanded to show all about a single packet and can be collapsed or expanded to show all of the information collected about the individual packet.
    - *Packet Bytes*: Packets in its Raw

<div align="center"> 
   <img src="./images/1.png" width="600px">
</div>
<div align="center"> 
   <img src="./images/2.png" width="600px">
</div>
<div align="center"> 
   <img src="./images/3.png" width="600px">
</div>
<div align="center"> 
   <img src="./images/4.png" width="600px">
</div>

## Chapter 4 - Working with Captured Packets
- The flags of a TCP packet are located at offset 13.
- The success or failure of your analysis depends on your ability to create filters appropriate for your current situation.

## Chapter 5 - Advanced Wireshark filters



























