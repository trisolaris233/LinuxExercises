include ../../global_cfg.makefile

SOURCE=mycp.c
OUTPUT=mycp

mycp: $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS)

bf: $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS) -DBUFFER_SIZE=512

bf2: $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS) -DBUFFER_SIZE=1024

bf3: $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS) -DBUFFER_SIZE=2048

bf4: $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS) -DBUFFER_SIZE=4096


bf5: $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS) -DBUFFER_SIZE=1


clean:
	rm $(OUTPUT)