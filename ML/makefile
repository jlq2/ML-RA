.PHONY= doc clean

CC=g++
OPTIONS= -g -w
LINKER_FLAGS = -lX11 -lm
DEBUG= #-D DEBUG
LIBDIR=src
INCLUDEDIR=include
_OBJ= gfx.o Perceptron.o dataReader.o neuralNetwork.o Math.o
OBJ = $(patsubst %,$(LIBDIR)/%,$(_OBJ))

all:	mainPerceptron.cpp $(OBJ)
	 $(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) mainPerceptron.cpp $(OBJ) -o main $(LINKER_FLAGS)
$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.hpp
	 $(CC) $(OPTIONS) $(DEBUG)  -c $(LINKER_FLAGS) -I$(INCLUDEDIR) -o $@ $<

p_sintetico: mainPerceptron.cpp $(OBJ)
	 $(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) mainPerceptron.cpp $(OBJ) -o main $(LINKER_FLAGS)
$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.hpp
	 $(CC) $(OPTIONS) $(DEBUG)  -c $(LINKER_FLAGS) -I$(INCLUDEDIR) -o $@ $<

p_sonar: mainSonar.cpp $(OBJ)
	 $(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) mainSonar.cpp $(OBJ) -o main $(LINKER_FLAGS)
$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.hpp
	 $(CC) $(OPTIONS) $(DEBUG)  -c $(LINKER_FLAGS) -I$(INCLUDEDIR) -o $@ $<

p_iris: mainIris.cpp $(OBJ)
	 $(CC) $(OPTIONS) $(DEBUG) -I$(INCLUDEDIR) mainIris.cpp $(OBJ) -o main $(LINKER_FLAGS)
$(LIBDIR)/%.o : $(LIBDIR)/%.cpp $(INCLUDEDIR)/%.hpp
	 $(CC) $(OPTIONS) $(DEBUG)  -c $(LINKER_FLAGS) -I$(INCLUDEDIR) -o $@ $<

run:
	./main

perceptron_sintetico: p_sintetico run
perceptron_sonar: p_sonar run
perceptron_iris: p_iris run

clean:
	rm -f $(OBJ)	