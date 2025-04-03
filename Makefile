# Makefile

TARGET=icp-fsm-app

all: $(TARGET)

$(TARGET):
	qmake src/gui/gui.pro -o src/Makefile
	make -C src/
	@mv src/$(TARGET) .

.PHONY: run clean

run: $(TARGET)
	./$(TARGET)

clean:
	make -C src/ clean
	@rm $(TARGET)