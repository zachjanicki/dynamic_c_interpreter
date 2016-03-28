CC=		g++
CPPFLAGS=	-Wall -o
ObjectFlags= -c

ObjectTargetsWithHeader = typeChecking.o arithmaticTests.o tokenTypeTests.o

all: main


main: AllTests.o
	$(CC) $(CPPFLAGS) main AllTests.o typeChecking.o tokenTypeTests.o arithmaticTests.o

AllTests.o: AllTests.cpp typeChecking.o tokenTypeTests.o arithmaticTests.o
	$(CC) $(ObjectFlags)  $<

# $(ObjectTargetsWithHeader).o: $(ObjectTargetsWithHeader).c
# 	$(CC) (ObjectFlags) $<

tokenTypeTests.o: tokenTypeTests.cpp tokenTypeTests.h
	$(CC) $(ObjectFlags) $<

arithmaticTests.o: arithmaticTests.cpp arithmaticTests.h
	$(CC) $(ObjectFlags) $<

typeChecking.o: ../typeChecking.cpp ../typeChecking.h ../Token.h
	$(CC) $(ObjectFlags) $<




clean:
	rm -rf arithmaticTests.o tokenTypeTests.o typeChecking.o AllTests.o main
