Nathan Pringle 
Last modified: 02/05/2021
----------------------------------
This application reads in a .c file and returns information about each of the variables and functions. 
Part A stores this information in a vector of structs. Part B uses a binary search tree to do this instead
----------------------------------
Part A can be built using my makefile by doing:

nmake Vector

This will compile the application, to run it simply type:

symbol_table *file.c* 

Where file.c is any .c file.
----------------------------------
Part B can be built using my makefile by doing:

nmake BinarySearchTree

This will compile the application and link the library to the main application. To run it, simply type:

symbol_table_b *file.c* 

Where file.c is any .c file
----------------------------------
If you only want the BST library you can get this by doing:

nmake BinarySearchTreeLibrary.
----------------------------------

This was made on the Microsoft Compiler