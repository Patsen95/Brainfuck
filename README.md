# Brainfuck
Simple, fast and easy to use Brainfuck interpreter ( ͡~ ͜ʖ ͡°)

Damn ugly, BUT singlefile interpreter implementation for the best esoteric prog language EVER!!!
The best one as you can get, 'cause it's born from the purest layziness.

TIP OF THE DAY: code includes some totally pointless comments.


COMMAND DESCRIPTION:

  >	increment the data pointer

  <	decrement the data pointer

  +	increment the byte at the data pointer

  -	decrement the byte at the data pointer

  .	output the byte at the data pointer

  ,	accept one byte of input, storing its value in the byte at the data pointer

  [	if the byte at the data pointer is zero, then instead of moving the instruction pointer 
      forward to the next command, jump it forward to the command after the matching ] command

  ]	if the byte at the data pointer is nonzero, then instead of moving the instruction pointer 
      forward to the next command, jump it back to the command after the matching [ command

Commands description has been taken from: https://en.wikipedia.org/wiki/Brainfuck#Commands
