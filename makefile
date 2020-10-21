CC=g++
CXXFLAGS=-g

OBJS = main.o mapa.o celda.o

all: ${OBJS}
	$(CC) $(CXXFLAGS) -o CocheAutonomo ${OBJS} -std=c++11

clean: 
	rm -rf *.o CocheAutonomo