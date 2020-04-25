include ../../global_cfg.makefile

OUTPUTLIST=skbfw atomic_append mydup dup_fd_test write_test test_sysconf 
SOURCELIST=seek0_before_append.c atomic_append.c mydup.c dup_fd_test.c write_test.c test_sysconf.c

all:
	$(CC) seek0_before_append.c -o skbfw $(FLAGS)
	$(CC) atomic_append.c -o atomic_append $(FLAGS)
	$(CC) mydup.c -o mydup $(FLAGS)
	$(CC) dup_fd_test.c -o dup_fd_test $(FLAGS)
	$(CC) write_test.c -o write_test $(FLAGS)
	$(CC) test_sysconf.c -o test_sysconf $(FLAGS)


clean:
	rm $(OUTPUTLIST)
