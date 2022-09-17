# Brainfuck
Simple, fast and easy-to-use Brainfuck interpreter ( ͡~ ͜ʖ ͡°)

Damn ugly, BUT single-file interpreter implementation for the best esoteric prog language EVER!!!
The best one as you can get, 'cause it\'s born from the purest layziness.

TIP OF THE DAY\: code includes some totally pointless comments.

## Command description

Cmd char | Description
:-:|-
\>|increment data pointer
\<|decrement data pointer
\+|increment byte at the data pointer
\-|decrement byte at the data pointer
\.|output byte at the data pointer
\,|accept one byte of input and store its value in the byte at the data pointer
\[|if the byte at the data pointer is zero, set the instruction pointer next to the command after the matching \] command
\]|if the byte at the data pointer is nonzero, set the instruction pointer next to the command after the matching \[ command

Commands description has been taken from: https://en.wikipedia.org/wiki/Brainfuck#Commands
