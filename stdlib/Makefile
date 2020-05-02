TARGET = hack_stdlib.ho

DEPS = display.ho exprstack.ho io.ho keyboard.ho math.ho sys.ho

all: $(TARGET)

$(TARGET): $(DEPS)
	cat $^ > $@

clean:
	rm -f $(TARGET)

install:
	/usr/bin/install -m 644 $(TARGET) $(INST_LIB_DIR)

uninstall:
	rm -f $(INST_LIB_DIR)/$(TARGET)

.PHONY: clean install uninstall
	
