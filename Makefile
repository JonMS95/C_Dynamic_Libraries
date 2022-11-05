src_main 	= Source_files/main.c
src_mult 	= Source_files/mult.c
src_div		= Source_files/div.c

obj_mult	= Object_files/mult.o
obj_div		= Object_files/div.o

so_mult		= Dynamic_libraries/mult.so
so_div		= Dynamic_libraries/div.so

exe_main	= Executable_files/main

shell_dirs	= Shell_files/directories.sh
shell_test	= Shell_files/test.sh

all: directories clean main mult.o div.o mult.so div.so rm_obj test

directories:
	@./$(shell_dirs)

main: $(src_main)
	gcc $(src_main) -o $(exe_main) -ldl

mult.o: $(src_mult)
	gcc -c -fPIC $(src_mult) -o $(obj_mult)

div.o: $(src_div)
	gcc -c -fPIC $(src_div) -o $(obj_div)

mult.so: $(obj_mult)
	gcc -shared $(obj_mult) -o $(so_mult)

div.so: $(obj_div)
	gcc -shared $(obj_div) -o $(so_div)

rm_obj:
	rm -rf Object_files

clean:
	rm -rf Executable_files/* Dynamic_libraries/*

test:
	@./$(shell_test)