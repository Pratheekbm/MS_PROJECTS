CC = g++

CFLAGS = -g -O0 -Wall -Wextra
INC = 	-I../inc
		
CFLAGS += $(INC)

SRC = 	../src/sim_cache.cpp\
		../src/cache.cpp

OBJ = $(SRC:.cpp=.o)

OUT = ../bin/sim_cache.out

all: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS)  -o $(OUT) $(OBJ) $(LIBS) 
	rm -f *.o

$(OBJ): $(SRC) 
	$(CC) $(CFLAGS) -c $(SRC) $(INC)

clean:
	rm -f *.o
	rm -f *.out
	rm -f ../bin/*.out
