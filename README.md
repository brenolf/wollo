Wollo
=====

Wollo is a tiny C library that provides a fancy printf with colours. Its main goal is to ease the usage of colours on terminals, using a terminology resembling HTML.

Compiling
---------

To compile the project simply run:

	gcc *.c

You must have a functional installation of ```gcc```.

Usage
-----

The main function of Wollo is ```print```. The ```print``` function takes a format string and infinitely many arguments as it is necessary, such as ```stdio```'s ```printf```. The format of ```print``` may have the following markup tags:

* ```<r>```: red
* ```<g>```: green
* ```<y>```: yellow
* ```<b>```: blue
* ```<m>```: magenta
* ```<c>```: cyan

All of them must be properly surrounded by closing tags just as in HTML. An example of the function is ```print("<m>magenta</m> <b>%d</b>", 1)```.

To-do
-----

There are arguably many features left to be implemented. The list below shows the (perhaps) most important of them:

* There are no checks for argument number
* There should be better error messages
* Maybe there could be more options and/or the tag names ought to be more intelligible
