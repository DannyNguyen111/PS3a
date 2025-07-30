# Compiler and flags
CC = g++
CFLAGS = -std=c++20 -Wall -Werror -pedantic -g
LIB_SFML = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# Header dependencies
DEPS = Sokoban.hpp

# Object files for static library
LIB_OBJECTS = Sokoban.o

# Object files for executable main
SOBO_OBJ = main.o

# Static library file
SOBO_LIB = Sokoban.a

# Executable name
SOBO_EXE = Sokoban

.PHONY: all clean lint

# Default target builds everything
all: $(SOBO_EXE)

# Compile .cpp files to .o files
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library from object files
$(SOBO_LIB): $(LIB_OBJECTS)
	ar rcs $@ $^

# Link executable with static library and SFML
$(SOBO_EXE): $(SOBO_OBJ) $(SOBO_LIB)
	$(CC) $(CFLAGS) -o $@ $(SOBO_OBJ) $(SOBO_LIB) $(LIB_SFML)

clean:
	rm -f *.o $(SOBO_EXE) $(SOBO_LIB)

lint:
	cpplint *.cpp *.hpp

