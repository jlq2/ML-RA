.PHONY= doc clean

.PHONY= doc clean

CC=g++
OPTIONS= -g -w
LINKER_FLAGS = -lSDL
DEBUG= #-D DEBUG
LIBDIR=src
INCLUDEDIR=include
_OBJ= screen_wrapper.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all:    main.cpp $(OBJ)
	LIBRARY_PATH="./lib/ALE" $(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o m -lale -lSDL

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.hpp
	LIBRARY_PATH="./lib/ALE" $(CC) $(OPTIONS) $(DEBUG)  -c $(LINKER_FLAGS) -I$(INCLUDEDIR) -o $@ $< 


clean:

	rm -f $(OBJ) 

run: all
	LD_LIBRARY_PATH="./lib/ALE"  ./m roms/breakout.bin
ale:
	cd ./lib/ALE && cmake -DUSE_SDL=ON -DUSE_RLGLUE=OFF -DBUILD_EXAMPLES=ON .
	cd ./lib/ALE && make -j 4

