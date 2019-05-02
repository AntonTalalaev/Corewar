Corewar is a 1984 programming game created by D.G. Jones and A.K. Dewdney in which two or more battle programs (called "champions") compete for control of a virtual machine (virtual machine load "champions" on a "virtual arena" to fight against one another).

This project can be broken down into three distinctive parts:
1. Chempion. Battle programs (champions) wich are written in an abstract assembly language and contain commands understandable by virtual machine.
2. Assembler. This is the program that will compile champions and translate them from the language written them in (assembly language) into "bytecode". Bytecode is a machine code, which will be directly interpreted by the virtual machine.
3. Virtual machine. Virtual machine generate "virtual arena", load there champions "bytecode" and execute it with visualisation (ncurses).
