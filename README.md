# Context Free Grammar
Program in C++ that reads a Context Free Gramar and removes the useless symbols and productions. After that it generates a new simplified CFG in an output file.

## Author
Ángel Luis Igareta Herráiz

## Index
* [Usage](#usage)
* [License](#license)

## Usage
To start the program first you have to compile the source with MakeFile. After that you can start it executing:

```
.bin/cfg inputCFG outputCFG
```
The CFG has to be in the following syntax:
```
2
0 1
3
S A B
S -> 0A | 1S | ~
A -> 0B | 1S | ~
B -> 0A | 1B
```

    1. The first line is the terminals' number of the CFG.
    2. The second line is the list of terminals separated by a whitespace.
    3. The third line is the no-terminals' number of the CFG.
    4. The fourth line is the list of no-terminals separated by a whitespace.
    5. The following lines will be the CFG productions. There must be one for no-terminal.
    
There are examples of CFG in the test folder.

## License
The Mit License.
