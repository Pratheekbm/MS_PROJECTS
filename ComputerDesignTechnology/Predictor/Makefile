CC = g++

CFLAGS = -g -O0 -Wall -Wextra
INC = 	-I./
		
CFLAGS += $(INC)

SRC = 	sim_bp.cpp\
		cache.cpp\
		predictor.cpp

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
