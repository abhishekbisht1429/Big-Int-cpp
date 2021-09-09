**Big Integer Implementation in C++**

- Multiplication is implemented using long multiplication (traditional pen and paper based algorithm)
-  Divsion is implemented using long Division (traditional pen and paper based algorithm)
- This implementaion does not rely on the standard template library or even String class in c++. It has been implemented using char arrays.
- To execute the program compile `main.cpp` using a compiler supporting C++ 11 or later and run the executable file
- `main.cpp` relies on `big_int.cpp` therefore both the files must be in the same directory during compilation.
- `DEBUG` macro must be commented out if the input is to be taken using standard I/O console.
- If `DEBUG` is not commented, then create two files *input.txt' and 'output.txt' for input and output respectively.

**Input Format**
- First line should contain an integer in range 1 to 4 inclusive.
    - 1 is for *exponentiation* and should be followed by a line containing two integers `b p` where b is base and p is power.
    - 2 is for *gcd* and should be followed by a line containing integers `a b` whose gcd is to be computed.
    - 3 is for *factorial* and should be followe by a line contaning a single non-negetive integer.
    - 4 is for *calculator* and should containg a valid expression consisting of non negetive integers and one or more  `+`, `-`, `x` or `/` signs.

**NOTE**
- There is no strict validation of the input provided by the user, therefore, if the input does not meet the format described above the result will be undefined.