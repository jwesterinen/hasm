TARGET = hasm

DEPS = code.h parser.h symbolTable.h
OBJ =  $(TARGET).o code.o parser.o symbolTable.o

CPP=g++
CPPFLAGS = -I. -O0 -g -Wall -c


%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS)

$(TARGET): $(OBJ)
	$(CPP) -o $@ $^

.PHONY: clean
clean:
	rm -f $(TARGET) *.o






