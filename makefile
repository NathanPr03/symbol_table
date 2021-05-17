BinarySearchTree:
	cl /EHsc /c tree.cpp 
	lib /OUT:tree.lib tree.obj
	cl /EHsc /c symbol_table_b.cpp
	link symbol_table_b.obj tree.lib

Vector:
	cl /EHsc symbol_table.cpp

BinarySearchTreeLibrary:
	cl /EHsc /c tree.cpp 
	lib /OUT:tree.lib tree.obj

Clean:
	del *.obj
	del *.exe
	del *.lib
	