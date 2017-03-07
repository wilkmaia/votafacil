CC = clang
CARGS = --std=c99
OBJLIST = conio.o ourStrings.o main.o eleitor.o eleicoes.o candidato.o

%.o: %.c
	$(CC) $(CARGS) -c -o $@ $<

main: $(OBJLIST)
	$(CC) $(OBJLIST) -o votafacil

.PHONY: clean

clean:
	rm -f /*.o
