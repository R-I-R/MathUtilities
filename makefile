APP := calculadora
CCFLAGS := -Wall -pedantic 
CC := g++
MKDIR := mkdir -p
CPPLIBFILES := src/libs/matrix.cpp
OBJLIBFILES := $(CPPLIBFILES:.cpp=.o)

$(APP): src/main.o $(OBJLIBFILES)
	$(CC) $^ -o $(APP)

$(OBJLIBFILES): $(CPPLIBFILES)
	$(CC) -I ./src/libs -c $^ $(CCFLAGS) -o $@

src/main.o: src/main.cpp
	$(CC) -I ./src/ -c $^ $(CCFLAGS) -o $@

clean:
	rm -f $(APP) src/main.o $(OBJLIBFILES)
