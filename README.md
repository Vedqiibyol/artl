# ARTL - Arguments and options for command line

I forgot why I even named it that way but whatever

It's a "simple" argument parser, that's it. It's read only, has an auto generate help.

# Using

1. Define your variables and set them to 0 or NULL.
2. create an `artl_argument` struct array and use the availble `ARTL_*type*_ARG`
   macro to create your arguments.
   Arguments, or position arguments are required variable passed to your program.
   ARTL will take whatever first argument it is given as an argument, whatever it is.
3. create an `artl_parameter` struct array and use the available `ARTL_*type*_OPT`
   or `ARTL_FLAG` to create options and flags. Flags take boolean values.
   the first parameter of the macro is the short pattern, a single character
   the second is the long pattern, the last is the address to your variable.
4. Run `artl_init` and give, in the following order: your arguments, as `char**`
   (`argv` from your main function), argc (also from your your main function), the
   starting index of your list of string, use ARTL_PROC_MAIN to parse command line
   arguments, the option token, the UNIX standard is '-', your list of arguments
   (as `struct artl_argument*`) and the number of arguments, your list of options
   (as `struct artl_parameter*`) and the number of options.
5. `artl_init` returns the index in your list of string where it was not able to find
   further options of flags


# Installing

Run the install script for your platform, respectively `.sh` for MacOS and Linux, `.ps1` for Windows.
It's a just a simple copy though, you might just want to copy it yourself, I don't know. Alternatively,
you can simply copy and paste `artl.h` into your project.

# Building

There is nothing to build.

