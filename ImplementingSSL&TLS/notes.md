<div align="center">
  <h1> Implementing SSL/TLS using Cryptography and PKI  </h1>
  <p> <i> Joshua Davies </i> </p>
</div>

<div align='center'> 
  <img src="./images/capa.png" width="600px"> 
</div>

### Introduction
- *This book should help you understand the internals of libraries like OpenSSL, GnuTLS and NSS*
- *C code examples*
- *Requests for Comments (RFCs)* are maintained by *Internet Engineering Task Force (IETF)*. *RFCs* documents protocols related to the internet.
- *My primary motivation in writing this book was to present, in detail, the interplay between the SSL and TLS protocols and the cryptographic routines thet they rely on.*

### Chapter 1 - Understanding Internet Security
- Standard encryption algorithms: *RSA* and *DSA*.
- *Man in the middle, side-channel, and timing attacks* -> aim to compromise privacy and security.
- *Internet Protocol (IP)*: Outlined in *RFC 971* (How packetization happens and how adresses are attached to packet headers?).
- Packets: *Origin Host -> Packet Data+Destination IP Address -> Router -> ... -> Destination Host*
- *DNS spoof*: Forwarding traffic that's meant for one destination to another.
  - *traceroute* command: Maps the journey that a packet of information undertakes from its source to its destination.
- *Socket*: Connection between a sender and a receiver. A socket refers to an established TCP connection.
- *TCP handshake* (described in *RFC 793*): 
  1) Client sends SYN (synchronize) packet to the server.
  2) Server responds with SYN/ACK (aknowledgment) packet.
  3) Client sends back a ACK packet.
  4) Connection is established (ports on client and server are attached to header).
  5) After that, client and server have a *socket*.  
- *SSL (Secure Socket Layer)*: Performs a secod handshake between client and server to establish a secure channel over the inherently insecure TCP layer.
- *HTTP Protocol*: 
  - Described in *RFC 2616*.
  - Browsers, the client, establish sockets with servers on port 80.
  - Each request demands a new socket.
  - *HTTPS* = HTTP + SSL.
  - It's case sensitive.
  - To request a document, the client needs to establish a socket with the server. *What does it means?* It means that the client needs to create a *SYN* package and send it to the server. The server needs to respond with a *SYN/ACK* package and, finally, the client concludes the handshake sending back an *ACK* package. When the server is not accessible, the client can use a *proxy-server* to funnel its requests to the target server. (*client -> proxy-server -> server*).
  - The standard format for a *Proxy*: 'http://[username:password@]hostname[:port]/'
- *Base64 Encoding*: Map binary into the range of printable ASCII characters.
  - Divides the input into 6-bit chunks (2^6 = 64, so *base64*) and maps each chunk into one of the printable ASCII characters.
  - First 52 combinations ('A-Za-z'); 10 combinations ('0-9'); and last 2 ('+/').
  - Complexity deals with non-aligned input ('=' is added to ensure alignment).
  - Output is 1/3 bigger than input.
  - Base64 it's required by the specification. 
- First release of SSL was SSLv2 (v1 was never release).
    - After that, SSLv3 was release and then renamed to TLS 1.0 (*RFC2246*).
    - TLS 1.1 was specified in *RFC 4346*.
    - TLS 1.2 was specified in *RFC 5346*.
- SSL is completely specified at the Network layer.
- *OpenSSL* is the most popular open-source implementation of SSL.

### Chapter 2 - Protecting Against Eavsdropppers with Symmetric Cryptography
- There's no defense against a *brute force* attack.
- HTTPS encrypts all traffic prior to transmission, and must subsequently be decrypted before processing.
- Two categories of cryptographic algorithms: *Symmetric* and *Public* (Key management differs them).
    - *Symmetric*: Same key is used to encrypt and decrypt.
    - In both cases, the sender and the receiver must agree what the key is before they can perform any encrypted communication.
- *Caesar Cipher*: Oldest known symmetric cipher (Maps letter to numbers)
- *Block Cipher Algorithms*: Operates on a fixed range of bytes rather than on a single character at a time.
    - *DES*: Data Encryption Standard (Implemented by IBM and the behest of the NSA in 1974)
        - Breaks its input up into eight-byte blocks (64-bits)
        - Scrambles the input using an eight-byte key after the first permutation. The permuted output is combined with the key in a series of 16 rounds (*Feistel Function*)
        - Series of permutations, rotations and XORS.
        - *S boxes*: 6-bits of input become 4-bits of output in a fixed but not reversible (just with the key) way. This is what makes DES secure.
        - Why XOR is used? (ex: 0101 (input) XOR 1100 (key) --> 1001 (output encoded). To get the original input, we take the encoded output and uses our key again: 1001 XOR 1100 --> 0101). XOR show us where bits are different. 
        - Described using *big endians* convention.
- *Cipher blocking chaining*: Preventing *replay attacks* (Get the encrypted message - *password, credit card* - and use it without decrypt).
        - DES is safe, but it's possible to brute-force the key with a really powerful hardware. 3DES (triple DES) is impossible to crack, but it's slower (3x slower).
        - 3DES has a 168-bit key.
    - *AES*: Advanced Encryption Standard
        - *Rijndel* Algorithm
        - 128-, 192, 252-bit keys.
