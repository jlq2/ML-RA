.PHONY= doc clean

.PHONY= doc clean

CC=g++
OPTIONS= -g -w
LINKER_FLAGS = -lX11 -lm
DEBUG= #-D DEBUG
LIBDIR=src
INCLUDEDIR=include
_OBJ= gfx.o 
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all:    main.cpp $(OBJ)
	 $(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) main.cpp $(OBJ) -o main $(LINKER_FLAGS)

$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.hpp
	 $(CC) $(OPTIONS) $(DEBUG)  -c $(LINKER_FLAGS) -I$(INCLUDEDIR) -o $@ $< 


clean:

	rm -f $(OBJ) 

run: all
	./main
