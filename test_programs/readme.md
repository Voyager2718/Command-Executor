# Summary
This directory contains test programs that can be used to test this project.

# argv_print_return.cpp
This program takes any number of arguments and print each of if using cout.

Finally it will return 127.

Example: 

Input:

`argv_print_return.cpp 1 2 3`.

Output:

```
1
2
3
```

Return value:

127

# err_message
This program takes 0 or 1 argument when starting up.

If no argument is specified, by default it will print 50 normal output lines with one error message in the middle of normal lines.

If a string that can be parsed to int, it will print specific number of normal output lines with one message in the middle of normal lines.

Example:

Input:

`err_message 5`.

Output:
```
[Mon Jul 10 12:29:15 2017 CST] Normal Output.
[Mon Jul 10 12:29:15 2017 CST] Normal Output.
[Mon Jul 10 12:29:15 2017 CST] Normal Output.
[Mon Jul 10 12:29:15 2017 CST] Normal Output.
[Mon Jul 10 12:29:15 2017 CST] TEST-1234: Error output.
[Mon Jul 10 12:29:15 2017 CST] Normal Output.
```

Return value:

63