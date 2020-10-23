CC=g++
CXXFLAGS=-g -std=c++14

OBJS = main.o mapa.o celda.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o CocheAutonomo ${OBJS}

clean: 
	rm -rf *.o CocheAutonomo