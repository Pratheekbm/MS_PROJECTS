CC = g++

CFLAGS = -g -O0 -Wall -Wextra
INC = 	-I/Users/pratheek/ifsHOME/MacX64/hdr/\
		-I../inc
		
CFLAGS += $(INC)
CFLAGS += -I/Users/pratheek/ifsHOME/MacX64/hrd/opencv

SRC = 	../src/main.cpp\
		../src/image.cpp

OBJ = $(SRC:.cpp=.o)
LIBS = 	/Users/pratheek/ifsHOME/MacX64/ifslib/libifs.a



OUT = ../bin/sample_image.out

all: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS)  -o $(OUT) $(OBJ) $(LIBS) 
	rm -f *.o

$(OBJ): $(SRC) 
	$(CC) $(CFLAGS) -c $(SRC) $(INC)

clean:
	rm -f *.o
	rm -f *.out
	rm -f ../bin/*.out
	#rm -f ../*.ifs