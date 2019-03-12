# LightASM

LightASM is an assembler virtual machine loosely based on AQA's ASM spec (http://filestore.aqa.org.uk/resources/computing/AQA-75162-75172-ALI.PDF). The aim of this project is for me to learn the spec.

## Plan

This was originally a slightly (very) broken program. I have a number of ideas to which I will begin to develop.

- Use GLIB Hash maps to better handle program virtual memory
- Write a virtual machine to better execute the code, allowing for registers such as a program counter to be implemented.
- Consider either web-based UI or an iOS app port. 
- Persistant storage

Crazy ideas? Of course.
- Develop into a small computer architecture.

I will gradually rewrite the original code of this project, you may view the original readme from past commits. 

##

Feel free to contribute, just make a PR. 

## Build

Litterally run `configure.sh`, then `make`. It's not got very complicated yet :P.