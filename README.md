 # task1
 ``` asm
 global loader
```
Declare the loader label as a global symbol
This is the entry point of the operating system

 # Kernel Entry Point
 ``` asm
loader:
    mov eax, 0xCAFEBABE
``` 
loader is the kernel entry label
Store the verification value 0xCAFEBABE into the EAX register