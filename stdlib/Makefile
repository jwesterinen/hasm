TARGET = hack_stdlib.ho
HEADER = hack_stdlib.h

DEPS = display.ho exprstack.ho io.ho keyboard.ho math.ho sys.ho

all: $(TARGET)

$(TARGET): $(DEPS)
	cat $^ > $@

clean:
	rm -f $(TARGET)

install:
	/usr/bin/install -m 644 $(TARGET) $(INST_LIB_DIR)
	/usr/bin/install -m 644 $(HEADER) $(INST_INCL_DIR)

uninstall:
	rm -f $(INST_LIB_DIR)/$(TARGET)
	rm -f $(INST_INCL_DIR)/$(HEADER)

.PHONY: clean install uninstall
	
