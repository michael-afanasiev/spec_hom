# Compilers
CXX 		= mpicxx

# Dependencies
PETSC_DIR 	= /opt/petsc

#Flags
CXXFLAGS	= -O0 -g -Wall -std=c++11 -I$(PETSC_DIR)/include 
LDFLAGS		= -L$(PETSC_DIR)/lib -lpetsc -lexodus

# Object files
OBJECTS		= \
	./obj/main.o \
	./obj/mesh.o \
	./obj/hexahedra.o

### Compile to object
./obj/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
### Compile to binary
all: main
	
main: $(OBJECTS) 
	$(CXX) $(LDFLAGS) -o ./wave.exe $(OBJECTS)
	
clean:
	$(RM) ./obj/*.o *.exe
