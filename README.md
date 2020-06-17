
# ft_printf
Rebuilding the C library function - printf

## Installation

1. Git clone the repository
1. Compile with make the libftprintf.a

## Features
Following conversions:
+ **csp**
+ **diouxX** with the following flags: **hh,h, l and ll**
+ **f** with the following flags: **l and L**

Manages:
+ **%%**
+ You must manage the flags **#0-+ and space**
+ You must manage the **minimum field-width**
+ You must manage the **precision**
+ My bonuses: 
  + flag character: `'` for decimal conversion the output is to be grouped with thousands' grouping characters
  + vas_printf print to allocated string
  + ft_dprintf write output to the given output stream

## Usage
Use the same way as the libc `printf`

Compile with a program and the header files:

`gcc -Wall -Werror -Wextra main.c libftprintf.a -I includes`
