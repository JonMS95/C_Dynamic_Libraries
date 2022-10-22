src_main 	= Source_files/main.c
src_mult 	= Source_files/mult.c
src_div		= Source_files/div.c

obj_main	= Object_files/main.o
obj_mult	= Object_files/mult.o
obj_div		= Object_files/div.o

so_mult		= Dynamic_libraries/mult.so
so_div		= Dynamic_libraries/div.so

exe_main	= Executable_files/main

main.o: $(src_main)
	gcc -c $(src_main) -o $(obj_main)

mult.o: $(src_mult)
	gcc -c -fPIC $(src_mult) -o $(obj_mult)

div.o: $(src_div)
	gcc -c -fPIC $(src_div) -o $(obj_div)

main: $(obj_main)
	gcc $(obj_main) -o $(exe_main) -ldl

mult.so: $(obj_mult)
	gcc -shared $(obj_mult) -o $(so_mult)

div.so: $(obj_div)
	gcc -shared $(obj_div) -o $(so_div)

clean:
	rm -rf Object_files/* Executable_files/* Dynamic_libraries/*