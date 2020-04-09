all:
	gcc -I../../include -g -Wall -c -fPIC get_num.c error_functions.c
	ar r ../../lib/libtlpi.a get_num.o error_functions.o
clean:
	rm *.o
	rm ../../lib/libtlpi.a