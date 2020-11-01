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
    - Handle problems typically seen in programming languages that allow shared memory access.
    - They provide a pattern that makes data safe from concurrent modifications.
    - They enforce the pattern that only one goroutine should modify the data at any time.
- *Go's type system*
  - Object-oriented development, but without the traditional headaches.
  - It uses a design pattern called composition. In Go, types are composed of smaller types
  - You don't to declare that you are implementing an interface. The compiler does the work of determining wheter values of your types satisy the interfaces you're using.
  - A Go interface typically represents just a single action.
- *Memory management*
  - Go has a modern garbage collector.

### Chapter 2 - Quick Start
- All code files in a folder must use the same package name, and it's common practice to name the package after the folder.
- Packages defines a unit of compiled code, and each unit of code represents a package.
- Go compiler won't let you delcare a package to be imported if it's not used.
- The variable located outside the scope of any function is considered a package-level variable.
- Variables that starts with capital letters are public to other packages. Variables that starts with lowercase variables are private to the current package.
- All variables are initialized to their zero value. For numeric types, that value is 0; for strings it's an empty string; for Booleans it's false; and for pointers, the zero value is nil.
- The ':=' operator both declare and initialize variables at the same time.
- A good rule of thumb when declaring variables is to use the key-word 'var' when declaring variable that will be initialized to their zero value, and to use the short variable declaration operator when you're providing extra initialization or making a function call.
- The keyword 'range' can be used with arrays, strings, slices, maps, and channels.
- Use the keyword 'go' to launch and schedule foroutines to run concurrently.
- The keyword 'defer' is used to schedule a function call to be executed right after a function returns.
- Type _interface_ is a special type in Go and works with the reflection support that can be found in the reflect package.
- Interfaces declare behavior that's required to be implemented by struct or named types to satisfy the interface.
- When the interface has only one method, its name should end with the 'er' suffix.
- An empty struct allocates zero bytes.
- It's best practice to declare methods using pointer receivers, since many of the methods you implement need to manipulate the state of the value being used to make the method call.
- Pointers are a way of sharing data across functions and goroutines.
- concurrency and synchronization are acomplished by launching goroutines and using channels.
- Interfaces in Go allow you to write generic code and frameworks. 

### Chapter 3 - Packaging and tooling
- Packages are a critical concept in Go. The idea is to separate semantic units of functionality into different packages. 
- All .go files must declare the package that they belong to as the first line of the file excluding whitespace and comments.
- Packages are contained in a single directory. You may not have multiple packages in the same directory, nor may yout split a package across multiple directories. This means that all .go files in a single directory must declare the same package name.
- The convention for naming package is to use the name of the directory containing it.
- The package _main_ has special meaning in Go. All of the executable programs you build in Go must have a package called _main_.
  - The main package must have a _main()_ function. This is the entry point for the program.
- _go get_ will fetch any specified URL and place the code inside the GOPATH.
- _named imports_: It is used to import packages with same name.
- All the _init_ functions that are discovered by the compiler are scheduled to be executed prior the _main_ function being executed.
  - Good to initialize variable, setting up packages, or performing any other bootstrapping.
- _go clean_ removes all executables in a package.
- _go build_: It compiles the source code and generates an executable.
- _go run_: It complies and run the executable file.
- _go vet_: The vet command will check your code for common errors.
  - Bad parameters in Printf-style functions calls.
  - Method signature errors for common method definitions.
  - Bad struct tags.
  - Unkeyed composite literals.
- _go fmt_ applies indentation to a specific code. Many Go developer configure their development environment to perform a go fmt on save or before commiting.
- Conventions to follow in order to be a good citizen in a distributed development environment.
  - Package should live at the root of the repository
  - Packages can be small
  - Run _go fmt_ on the code
  - Document the code
- Dependency Management
  - _godep_, _vendor_, _gopkg.in_ help package authors publish different versions of their packages.
  - Vendoring and import path rewriting technique: The idea is to copy all the dependencies into a directory inside the project repo, and then rewrite any import paths that reference those dependencies by providing the location inside the project yourself.
  - _Gb_: It is a whole new class of build tool being developed by members of the Go community. Gb replaces the Go tooling workspace metaphor with a project-based approach. Gb project is not compatible with the Go tooling, including go get (_https://getgb.io_).

### Chapter 4 - Arrays, slices, and maps
- Go has three different data structures that allow you to manage collections of data: _arrays_, _slices_, and _maps_. 
- Arrays form the base data structure for both slices and maps.
  - Fixed-length data type
  - It contains contiguous block of elements of the same type.
  - If you need more elements in the array, you need to create a new one with length needed and then copy the values from one array to the other.
  - Only arrays of the same type can be assigned.
  - You can copy multidimensional arrays into each other as long as they have the same type.
  - Passing an array between functions can be an excpensive operation in terms of memory and performance.
    - When you pass between functions, they're always passed by value. When your variable is an array, this means the entire array, regardless of this size, is copied and passed to the funtion.
    - There's a better and more efficient way of doing this. You can pass a pointer to the array and only copy eight bytes, instead of eight megabytes of memory on the stack.
- Slice is a data structure that provides a way for you to work with and manage collections of data.
  - Slices are built around the concept of dynamic arrays that can grow and shrink as you see fit.
  - Slices give you all the benefits of indexing, iteration, and garbage collection optimizations.
  - They're three field data structures that contain the metadata Go needs to manipulate the underlying arrays: _pointer_, _length_, _capacity_
  - _make_: It creates a slice. When you use _make_, one option you have is to specify the length and the capacity of the slice (ex: _slice := make([]string, 5)_)
  - An idiomatic way of creating a slice is to use a slice literal
    - _slice := []string { "Red", "Blue", "Green", "Yellow", "Pink" }_
  - If you specify a value inside the [ ] operator, you're creating an array. If you don't specify a value, you're creating a slice.
  - How to calculate the Length and Capacity of a slice:
    - For _slice[i:j]_ with an underlying array of capacity _k_
      - Length = j - i
      - Capacity = k - i
  - Slices are references.
  - The _append_ operation is cleaver when growing the capacity of the underlying array. Capacity is always doubled when the existing capacity of the slice is under 1000 elements. Once the number of elements goes over 1000, the capacity is grown by a factor of 1.25, or 25%. This growth algorithm may change in the language over time.
  - Detaching the new slice from its original source arrayu makes it safe to change.
    - Ex: slice[2, 3, 3] => When capacity = length, force the creation of a new slice and do not mutate the original slice.
  - The _cap_ and _len_ functions work with arrays, slices, and channels.
  - Passing a slice between two functions requires nothing more than passing the slie by value. Since the size of a slice is small, it's cheap to copy and pass between functions.    - A sliice requires 24 bytes of memory. The pointer field requires 8 bytes, and the length and capacity fields requires 8 bytes respectively.
    - Passing the 24 bytes between functions is fast and easy. This is the beauty of slices.
- _Map_ data structures: It provides you with an unordered collection of key/value pairs.
  - They are collections, and you can iterate over them just like you do with arrays and slices.
  - _Unordered_ collections. Every iteration over a map could return a different order.
  - The purpose of the hash function is to generate an index that evenly distributes key/values pairs across all available buckets.
  - In the case if a Go map, a portion of the generated hash key, specifically the _low order bits_ (LOB), is used to select the bucket.
  - Example: _dict := map[string]string { "Red": "#da1337", "Orange": "#e95a22" }_
  - The map key can be a value from any built-in or struct type as long as the value can be used in an expression with the _==_ operator. Slices, functions, and sctruct types that contain slices can't be used as map keys. This will produce a compiler error.
  - Testing if a map key exists is an important part of working with maps.
  - When you index a map in Go, it will always return a value, even when the key doesn't exist. In this case, the zero value for the value's type is returned.
  - Passing a map between two functions doesn't make a copy of the map (The reference is passed to the function)
  - Maps are designed to be cheap, similar to slices. 
  - Maps don't have a capacity or any restriction on growth.

### Chapter 5 - Go's Type System
- When the compiler knows the type information ahead of time, it can help to make sure that the program is working with values in a safe way.
- There are two ways to declare a user-defined type in Go. The most common way is to use the keyword _struct_, which allows you to create a composite type.
- The zero value would apply to all the different fields in the struct.
- *Methods*
  - Methods provide way to add nehavior to user-defined types. Methods are really functions that contain an extra parameter that's declared between the keyword _func_ and the function name.
  
  ```golang
    // Sambple program to show how to declare methods and how the Go compiler supports them
    package main

    import (
      "fmt"
    )

    // user defines a user in the program.
    type user struct {
      name  string
      email string
    }
    
    // notify implements a method with a value receiver.
    func (u user) notify() {
      fmt.Printf("Sending User Email To %s<%s>\n",
        u.name,
        u.email
      )
    }
  ```
