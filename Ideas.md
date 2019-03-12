# Ideas

This file contains a more in-depth description of the plans and ideas I have for this project.

## Compiling & Interpreting

Unlike the original where commands could be executed live on a console-like interface, LightASM will now take a file as an input, compile it and run. 

## lasmc

`lasmc` will be used to compile a file, for example `program.lasm`, and will produce a 'binary' in the format of `program.lbin`. These files will contain the compiled instructions from the given file, which can then be run in the virtual machine.

The compiler will be able to recognise the instructions set out in AQA's specification, plus a few others that I decide to implement.

To start with, until you can't see this message anymore, there will only be the following instructions. Also, both upper case and lower case will be acceptable. 

Register `rd` is used to denote the destination register and `rn` a register to perform an operation with.

Instruction set and registers:
```

// Instructions
0x00    NOP
0x01    HALT

0x02    MOV
0x03    ADD
0x04    SUB


// Registers
0xE0    R0  (General Purpose)
...                         
0xE9    R10
0xEA    R11 (PC)

```


Example:
```
ASM:
    mov r0, r1

Hex:
    0x02e0e1

Array Literal:
    { 0x02, 0xE0, 0xE1 }

```


## Virtual Machine

`lasmvm` will be used to run a compiled `.lbin` file in the LightASM virtual machine.

[More details soon]