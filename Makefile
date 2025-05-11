# Makefile

QMAKE = /usr/local/share/Qt-5.5.1/5.5/gcc_64/bin/qmake
BUILD_DIR=build
TARGET=icp-fsm-app

all: build

build:
	@mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(QMAKE) ../src/gui/gui.pro && make

.PHONY: run clean zip doxygen doxyClean

run: build
	LD_LIBRARY_PATH=$(BUILD_DIR) 
	./$(BUILD_DIR)/$(TARGET)

doxygen:
	doxygen Doxyfile

doxyClean:
	rm -rf doc/html
	rm -r doc/

clean:
	rm -rf $(BUILD_DIR)

zip: clean
	zip -r xprochp00-xbasism00-xfickaf00.zip src/
