APP := calculadora
CCFLAGS := -Wall -pedantic 
CC := g++
MKDIR := mkdir -p
CPPLIBFILES := src/main.cpp src/libs/matrix.cpp src/libs/rational.cpp
OBJLIBFILES := $(CPPLIBFILES:.cpp=.o)

$(APP): $(OBJLIBFILES)
	$(CC) $^ -o $(APP)

%.o: %.cpp
	$(CC) -I ./src/libs -c $< $(CCFLAGS) -o $@

#src/main.o: src/main.cpp
#	$(CC) -I ./src/ -c $^ $(CCFLAGS) -o $@

clean:
	rm -f $(APP) src/main.o $(OBJLIBFILES)
