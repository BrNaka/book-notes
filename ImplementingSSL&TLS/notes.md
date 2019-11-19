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
        - Why XOR is used? (ex: 0101 (input) XOR 1100 (key) = 1001 (output encoded). To get the original input, we take the encoded output and uses our key again: 1001 XOR 1100 = 0101). XOR show us where bits are different. 
        - Described using *big endians* convention.
- *Cipher blocking chaining*: Preventing *replay attacks* (Get the encrypted message - *password, credit card* - and use it without decrypt).
        - DES is safe, but it's possible to brute-force the key with a really powerful hardware. 3DES (triple DES) is impossible to crack, but it's slower (3x slower).
        - 3DES has a 168-bit key.
    - *AES*: Advanced Encryption Standard
        - *Rijndel* Algorithm
        - 128, 192, 252-bit keys.
        - Given a 16-byte input, the AES key schedule computation needs to produce 176 bytes of output.
        - *State*: 4x4 byte array. The bytes from input are split in chunks of four bytes. This chunks are placed vertically in the array.
        - AES is widely supported. In fact, recent Intel chips include assembly-level AES instructions!
    - Other block cipher algorithm: IDEA, RC2, blowfish, twofish, FEAL, LOKI, and Camelia.
*Stream Cipher*: Technically is the same as Block Cipher. However, it operates on a block size of one byte.
    - It concentrate on generating a secure stream of bytes whose length is the same as the plain-text. 
    - Cryptographic security is generated from the keystream generation function.
    - All of the security is in the key schedule generation.
    - Only one stream sipher has been widely implemented in SSL: **RC4 algorithm**
        - *RC4 algorithm*
            - It's not an open standard like AES and DES are.
            - Details of how RC4 works has never been officialy published.
            - 256-byte key schedule is computed from the key.
- A block cipher can be converted into a Stream Cipher.

## Chapter 3 - Secure Key Exchange over an Insecure Medium with Public Key Cryptography
- Challenge in applying private key algorithms is keeping the private key private.
- Solution: *public-key cryptography* (asymmetric/public key)
    - Two keys which are matematically related.
    - An encrypt operation performed with one key can only be decrypted using the other one.
    - *RSA algorithm*: the name comes from its inventors (Ron *Rivest*, Adi *Shamir*, and Leonard *Adleman*).
        - Based entirely on properties of natural numbers.
        - Relies on three numbers: e, n and d (e+n = public key; d = private key).
        - Sender: Converts the message into a number (m) (m^e) % n = c ('e' can be 65.537 which is the smallest prime number and can be represented with two-bits)
        - Receiver: Get the result and uses the private key to decrypt the message, (c^d) % n = message
        - *The modulus operation - that is, the remainder left over after a division operation - is important to modern public-key cryptography and is likely going to remain important for the forseeable future.*
        - Speed up cryptography operations: *Barrett and Montgomery reduction*.
        - Part of the security of the RSA public key cryptosystem is the infeasibility of a brute-force attack.
        - *Padding algorithms*: PKCS1.5 padding and OAEP.
        - Procedure for generating RSA keypairs:
            1) Select two random prime numbers *p* and *q*
            2) Compute the modules n = pq.
            3) Compute the totient function (p-1)(q-1)
            4) Select a random public expoent e < phi(n)
            5) Perform a modular inversion to compute the private expoent d: de % n = 1.
        - SSL calls on you to select a symmetric-key algorithm, generate a key, encrypt that key using an RSA public key, and, after that key has been sent and acknowledged, to begin using the symmetric algorithm for subsequent communications.
        -Although RSA can be used as a complete cryptography solution, its slow runtime limits its practical uses to simple encryption of keys to be used for symmetric cryptography.
- *Elliptic Curve Cryptography*:
    - Euclidean algorithm is an efficient way to discover the greatest common denominator (GCD) of two numbers (the largest number that divides both evenly)
    - ECC an provide the same security with an 80-bit private key as RSA can provide with a 512-bit private key because every single bit (provably) contributes to the security of the cryptosystem.
    - It's popular on bank industry.
    - It's expect that ECC gain popularity int the coming years simply beause of its speed advantages over RSA and DH.

## Chapter 4: Authenticating Communications Using Digital Signatures.
- Public key cryptography is too slow for large blocks of information.
- You're trying to prove that somebody with access to the private key generated the message.
- Shortened representation of the message (*message digest*)that can be computed by both sides. Sender encrypts the message using the private key and the receiver can compute the same shortened representation and decrypt it using the public key.
- Simplest form of a message digest is a *checksum* (but there is a huge vulnerability in this method).
- *MD5 digest Algorithm*: Secure hashing algorithm.
    - Specified in *RFC1321*
    - Creator: Ron Rivest (The 'R' in the RSA algorithm).
    - The goal is to reduce an arbitrarily sized input into an n-bit hash.
    - Operated on 512-bit (64-byte) blocks of input. Each block is reduced to 128-bit (16 byte) hash.
    - MD5 derive their security from their complexity.
    - Vulnerability: *Birthday Paradox*. "The more computers I add to the attack, the faster I can get an answer".
    - *"How to break MD5 and other hash functions"* - http://merlot.usc.edu/csac-s06/papers/Wang05a.pdf
    - Real world MD5 collision - http://th.informatik.uni-mannheim.de/people/lucks/HashCollisions/
    - MD5 is fairly popular. TLS mandates its use.
- *SHA-1 digest Algorithm*: Increases the collision Resistance.
    - *Secure Hash Algorithm*.
    - Similar to MD5, but produces a 160-bit (20-byte) hash rather than 128-bit (16-byte) and deals with big-endian rather than little-endian.
    - SHA-256, SHA-384, SHA-512 digest algorithm: More collision Resistance.
- *HMAC Keyed-Hash Algorithm*
    - Specified in *RFC 2104*.
    - Include a secret in the hash. Both sides share a secret , which is combined with the hash in a secure way.
    - *SSL* requires that every record first be HMAC'ed before being encrypted. SSL uses the HMAC function as a pseudo-random number generator.
- *DSA*: Digital Signature Algorithm
    - DSA is certified for SHA-1 and SHA-256.

## Chapter 5: Creating a Network of Trust Using X.509 Certificates
- Certificates are a holder for a public key.
- The primary purpose of the certificates is to present the user agent with a public key that should then be used to encrypt a symmetric key that is subsequently used to protect the remainder of the connection's traffic.
- Digital signatures are how certificates are authenticated and how you can determine whether or not to trust certificate.
- *Man in the middle attack*: Solution adopted by SSL requires the use of a trusted intermediary (*Certificate Authoriy* (CA) signs the certificate).
- Web brosers have a list of trusted CAs with their public keys.
- Certificates include *validity period*.
- *CRL - Certificate Revocation List*: CAs list of revoked certificates.
- What are the informations included in certifications? 
    - *Public Key*
    - Domain name of the server
    - *Serial ID*: unique within a CA.
    - *Issuer*: uniquely identifies the CA.
- SSL/TLS uses certificates defined and maintained by the *International Telecommunications Union (ITU)*. 
- X.509 Certificates are specified using a syntax referred to as *Abstract Syntax Notation (ASN)*: Standard for public-key certificates and the format on which TLS 1.0 relies.
- *PKI (Public Key Infrastructure)*: 
    - Subject name, Issuer name, Signature, the extensions, and so on: Allows the receiver to verify authenticity of the certification.
 
