# LightASM

LightASM is an Assembly... simulator. Not sure what to call it really. Anyway, it's based on AQA's ALI found here http://filestore.aqa.org.uk/resources/computing/AQA-75162-75172-ALI.PDF.

The point of this project is mainly for me to learn that spec, and @zistooshort did the same thing and writing my own language seemed fun, and it's assembly so not as complicated to implement than a full language like C.

If you notice me doing something either stupid or n00by, please don't hesitate to raise it with me over Twitter or a pull request. I want to extend my knowledge so if i do make mistakes that's greatly appreciated. 

So, here's some of my ideas. (Will be updated reguarly)

## Operation

I plan to have two modes. A live interpreter, and a mode where you specifiy a file. 

### Live Console

With the live console, it will act much like the Python console. Run each command 1-by-1. I'll detail this more soon.

### Running through a file

With this you would specifiy a file, I plan to used the `.lasm` extension, which would then execute and provide the contents of the registers once completed.

## Build

Litterally run `configure.sh`, then `make`. It's not got very complicated yet :P.