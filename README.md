## A brief description of the program and how it works.
Input vectors and store in an array.
Validate input and handle errors.
Perform commands such as help, clear, list, quit.
Options to load and save files are included.
Create new vectors, display vectors, perform operations on vectors.
Valid operations include add, sub, mult, dot, scalar.
## How to build the program
Compile: `gcc main.c operations.c commands.c -o vector_lab`
## How to run the program – available command line options
`./vector_lab`
`./vector_lab -h`
## A list of commands supported by the program
- `help` display help menu
- `list` list all vectors in storage
- `clear` clear all vectors in storage
- `load` load vectors from a file
- `save` save vectors to a file
- `quit` quit the program
- `<vector> = 1, 2, 3` create a new vector
- `<vector> = <vector> + <vector>` (or + - * .) perform math on vectors
- `<vector> = <scalar> * <vector>` (or `<vector> = <vector> * <scalar>`) multiply vectors by a scalar
## A short description of how your program uses dynamic memory (ok, not typical – think lab report...)
Dynamic memory is used to store the vectors so more than 10 vectors can be entered if needed.
malloc is used to create space in memory for the vector.
free is used to clear the space in memory.