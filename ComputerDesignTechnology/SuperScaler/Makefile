CC = g++

CFLAGS = -g -O3 -Wall -Wextra
INC = 	-I./
		
CFLAGS += $(INC)

SRC = 	main.cpp\
		superScalar.cpp

OBJ = $(SRC:.cpp=.o)

OUT = sim

all: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS)  -o $(OUT) $(OBJ) $(LIBS) 
	rm -f *.o

$(OBJ): $(SRC) 
	$(CC) $(CFLAGS) -c $(SRC) $(INC)

clean:
	rm -f *.o
	rm -f sim
