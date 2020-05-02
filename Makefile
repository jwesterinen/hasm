TARGET = hasm

PREFIX ?= /usr/local
INST_BIN_DIR = $(PREFIX)/bin
INST_LIB_DIR = $(PREFIX)/lib

DEPS = code.h parser.h symbolTable.h
OBJ =  $(TARGET).o code.o parser.o symbolTable.o

CPP=g++
CPPFLAGS = -I. -O0 -g -Wall -c


%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CPPFLAGS)

all: $(TARGET)
	make -C stdlib

$(TARGET): $(OBJ)
	$(CPP) -o $@ $^

clean:
	rm -f $(TARGET) *.o
	make -C stdlib clean

install:
	/usr/bin/install -m 755 $(TARGET) $(INST_BIN_DIR)
	make INST_LIB_DIR=$(INST_LIB_DIR) -C stdlib install

uninstall:
	rm -f $(INST_BIN_DIR)/$(TARGET)
	make INST_LIB_DIR=$(INST_LIB_DIR) -C stdlib uninstall

.PHONY: clean install uninstall
	
