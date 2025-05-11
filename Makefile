# Makefile

DOXYFILE = Doxyfile
TARGET=icp-fsm-app

all: $(TARGET)

$(TARGET):
	qmake src/gui/gui.pro -o src/Makefile
	make -C src/
	@mv src/$(TARGET) .

.PHONY: run clean zip doxygen doxyClean

run: clean $(TARGET)
	./$(TARGET)

doxygen:
	doxygen $(DOXYFILE)

doxyClean:
	rm -rf doc/html
	rm -r doc/

clean:
	@rm -f $(TARGET)
	@rm -f src/*.o

zip: clean
	git archive --format=zip HEAD -o xprochp00-xbasism00-xfickaf00.zip

