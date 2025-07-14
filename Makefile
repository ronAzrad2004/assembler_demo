C_ASM_TEST: main_start_project.c my_str_funcs.o my_str_funcs.h checkpoints_entry_extern.o checkpoints_entry_extern.h database_data_string.o database_data_string.h check_excepts.o check_excepts.h assembler.o assembler.h macrs.o macrs.h pre_proccessor.o pre_proccessor.h
	gcc -Wall -g -ansi -pedantic main_start_project.c my_str_funcs.o check_excepts.o checkpoints_entry_extern.o database_data_string.o assembler.o macrs.o pre_proccessor.o -o C_ASM_TEST
assembler.o: assembler.c checkpoints_entry_extern.h database_data_string.h
	gcc -Wall -ansi -pedantic -c assembler.c -o assembler.o

check_excepts.o: check_excepts.c my_str_funcs.h
	gcc -Wall -ansi -pedantic -c check_excepts.c -o check_excepts.o

checkpoints_entry_extern.o: checkpoints_entry_extern.c my_str_funcs.h
	gcc -Wall -ansi -pedantic -c checkpoints_entry_extern.c -o checkpoints_entry_extern.o

database_data_string.o: database_data_string.c my_str_funcs.h
	gcc -Wall -ansi -pedantic -c database_data_string.c -o database_data_string.o

macrs.o: macrs.c my_str_funcs.h
	gcc -Wall -ansi -pedantic -c macrs.c -o macrs.o

pre_proccessor.o: pre_proccessor.c
	gcc -Wall -ansi -pedantic -c pre_proccessor.c -o pre_proccessor.o

my_str_funcs.o: my_str_funcs.c
	gcc -Wall -ansi -pedantic -c my_str_funcs.c -o my_str_funcs.o
