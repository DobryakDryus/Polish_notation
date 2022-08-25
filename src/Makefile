all: 
	gcc -Wall -Wextra -Werror -c check_str.c stack_str.c math_operations.c stack_n_list.c graph.c
	gcc check_str.o stack_str.o math_operations.o stack_n_list.o graph.o -o ../build/graph
	rm -rf check_str.o stack_str.o math_operations.o stack_n_list.o graph.o
	
clean:
	rm -rf check_str.o stack_str.o math_operations.o stack_n_list.o graph.o