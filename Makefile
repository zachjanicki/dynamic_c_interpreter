CC=		g++
CPPFLAGS=	-Wall -o
ObjectFlags= -c
all: main


main: repl.o typeChecking.o tokenize.o Parser.o Token.h
	$(CC) $(CPPFLAGS) main repl.o typeChecking.o tokenize.o Parser.o

repl.o: repl.cpp Token.h
	$(CC) $(ObjectFlags) $<



typeChecking.o: typeChecking.cpp typeChecking.h
	$(CC) $(ObjectFlags) $<

tokenize.o: tokenize.cpp
	$(CC) $(ObjectFlags) $<

interp.o: interp.cpp Token.h
	$(CC) $(ObjectFlags) $<

Parser.o: Parser.cpp Parser.h Token.h
	$(CC) $(ObjectFlags) $<


clean:
	rm *.o
	rm main
