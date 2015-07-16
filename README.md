Wollo
=====

Wollo is a tiny C/C++ library that provides a fancy `printf` with colours. Its main goal is to ease the usage of colours on terminals, using a terminology resembling HTML.

Usage
-----

Add `import "wollo.h"` on the preamble of your C/C++ code and you are ready to go.

The main function of Wollo is `print`. The `print` function takes a format string and infinitely many arguments as it is necessary, such as `stdio`'s `printf`. The format of `print` may have the following markup tags:

* `<blink>`: text blinks
* `<dim>`: text is dimmed
* `<u>`: underlined text
* `<inverted>`: inverts foreground and background
* `<r>`: red
* `<g>`: green
* `<y>`: yellow
* `<b>`: blue
* `<m>`: magenta
* `<c>`: cyan

In order to use `<` and `>` you need to escape them by using, respectively, `<<` and `>>`. All tags must be properly surrounded by closing tags just as in HTML, otherwise an error will be raised. An example of the function is the following code:

```c
#include "wollo.h"

int main () {
  print("<r>Hello</r>, <b><u>this</u></b> is a <b>f</b><g>an</g><r>cy</r>\
 text <y>using</y> <inverted>Wollo</inverted>.\n");
  return 0;
}
```

That will produce the following output:
![Example](https://github.com/brenolf/wollo/blob/screenshots/example.png)

Tokenizer
---------
Wollo takes advantage of a special tokenizer. It is a variation of the standard `strtok` allowing the user to pass in an array of strings that are going to be considered delimiters. The function will take the nearest one and return it. Its signature is as follows: ```char* tokenize (char *haystack, char **needles, int n_needles, int *chosen, char **next);```.

`haystack` is the string that is going to be considered. Note that `haystack` is going to be mangled, therefore, you should pass a copy instead. `needles` is an array of delimiter strings, being `n_needles` its length. `chosen` will be changed every time the function finds a delimiter in `haystack`, being the index of the delimiter chosen in `needles`. The last parameter should be a address of a char pointer, that keeps track of the read string; The first time you call the function, `next` **must** be  `NULL`.

The complexity of `tokenize` is pseudo-linear: `O(n * n_needles)`. We also consider the size of the needles to be very small.

To-dos
------

* There is no argument number check
* There could be more styling options
