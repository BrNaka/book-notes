<div align="center">
  <h1> Go In Action </h1>
  <p> <i> William Kennedy </i> </p>
</div>

<div align='center'> 
  <img src="./images/capa.png" width="600px"> 
</div>

_Go is an open source programming language that makes it easy to build simple, reliable, and efficient software.
It balances the capabilities of a low-level system language with some high-level features you see in modern languages today._

### Chapter 1 - Introducing Go 
- High-powered servers now have 64, 128, or even more cores, but we're still programming using the techniques we were using for a single core.
- Go rethinks the traditional object-oriented development you might be used to, while still providing an efficient means for code reuse.
- High-performance language with features that make development fast.
- Go's concurrency support is one of its strongest features. _Goroutines_ are like threads, but use far less memory and require less code to use. _Channels_ are data structures that let you send typed messages between goroutines with synchronization build in.
  - *Goroutines* are functions that run concurrently with other goroutines. 
    - They're executed in a single thread. 
    - Go runtime automatically schedule the execution of goroutines against logical processors. Each logical processor is bound to a single OS thread.
    - They have minimal overhead, so it isn't uncommon to spawn tens of thousands of them.
  - *Channels* are data structures that enable sabe data communication between goroutines.
