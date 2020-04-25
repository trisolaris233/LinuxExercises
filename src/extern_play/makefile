SOURCE=main.c ./libexternp.a
OUTPUT=main
CC=gcc

$(OUTPUT): $(SOURCE)
	$(CC) $(SOURCE) -o $(OUTPUT) $(FLAGS)


lib: extern_play.c
	$(CC) -c -o extern_play.o extern_play.c
	ar rsc libexternp.a extern_play.o


clean:
	rm *.o
	rm main
	rm *.a

re:
	make lib
	make
	./main