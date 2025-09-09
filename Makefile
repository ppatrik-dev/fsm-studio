# Makefile for FSM Studio

BUILD_DIR=build
TARGET=fsm-studio
QMAKE=/usr/lib/qt6/bin/qmake

.PHONY: all build run install uninstall  \
	html clean-build clean-html clean

all: build

# Build the application and install dependencies
build:
	@echo "Installing build dependencies..."
	@sudo apt-get update
	@sudo apt-get install -y \
		build-essential qt6-base-dev qt6-tools-dev qt6-tools-dev-tools \
		qt6-declarative-dev
	
	@echo "Building the FSM application..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && $(QMAKE) ../src/gui/gui.pro && make -j 8

# Run the application
run: $(BUILD_DIR)/$(TARGET)
	@echo "Running FSM Studio..."
	LD_LIBRARY_PATH=$(BUILD_DIR):$$LD_LIBRARY_PATH \
	./$(BUILD_DIR)/$(TARGET)

# Install the application as a system application.
install: build
	@sudo install -Dm755 $(BUILD_DIR)/$(TARGET) /usr/local/bin/$(TARGET)
	@sudo install -Dm644 resources/fsm-studio.desktop /usr/share/applications/fsm-studio.desktop
	@sudo install -Dm644 resources/fsm-studio.png /usr/local/share/icons/fsm-studio.png
	@sudo mkdir -p /usr/local/share/fsm-studio/examples
	@sudo cp -r examples/* /usr/local/share/fsm-studio/examples/

# Uninstall the application and dependencies
uninstall:
	@echo "Removing FSM Studio..."
	@sudo rm -f /usr/local/bin/$(TARGET)
	@sudo rm -f /usr/share/applications/fsm-studio.desktop
	@sudo rm -f /usr/local/share/icons/fsm-studio.png
	@sudo rm -rf /usr/local/share/fsm-studio/examples/

	@echo "Removing build dependencies..."
	@sudo apt remove --purge -y \
		build-essential qt6-base-dev qt6-tools-dev qt6-tools-dev-tools \
		qt6-declarative-dev
	@sudo apt autoremove -y

	@echo "FSM Studio uninstalled."

# Generate documentation
html:
	@sudo apt-get install -y doxygen
	@doxygen Doxyfile

# Clean all build files
clean-build:
	@rm -rf $(BUILD_DIR)

# Clean generated documentation
clean-html:
	@rm -rf doc/html

# Clean all generated files
clean: clean-build clean-html
