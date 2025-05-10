# Makefile

DOXYFILE = Doxyfile
TARGET=icp-fsm-app

all: $(TARGET)

$(TARGET):
	qmake src/gui/gui.pro -o src/Makefile
	make -C src/
	@mv src/$(TARGET) .

.PHONY: run clean doxygen doxyClean

run: $(TARGET)
	./$(TARGET)

doxygen:
	doxygen $(DOXYFILE)

doxyClean:
	rm -rf doc/html
	rm -r doc/

clean:
	make -C src/ clean
	@rm $(TARGET)
