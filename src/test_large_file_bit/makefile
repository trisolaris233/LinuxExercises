include ../../global_cfg.makefile

SOURCE=sklgf.c
OUTPUT=sklgf

$(OUTPUT): $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS) -D_FILE_OFFSET_BITS=64


clean:
	rm $(OUTPUT)