# Cosplay Fett Display (https://github.com/wastrachan/cosplay-fett-display/)
#
# Copyright (c) 2021 Winston Astrachan
# Available under the terms of the MIT license

SHELL=/bin/bash
BUILD="$(shell pwd)/build"
FQBN=adafruit:avr:flora8
PORT="$(shell arduino-cli board list | grep $(FQBN) | awk '{print $$1};')"


build:
	@echo ""
	@echo "Building fett-display for $(FQBN)..."
	@echo ""
	arduino-cli compile --fqbn=$(FQBN) --build-path $(BUILD) fett-display


.PHONY: install
install: build
ifeq ($(PORT),"")
	@echo ""
	@echo "No board detected with FQBN $(FQBN)!"
	@echo "Troubleshoot with arduino-cli board list"
	@echo ""
else
	@echo ""
	@echo "Installing fett-display to $(PORT)"
	@echo ""
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) --input-dir $(BUILD) fett-display
endif


.PHONY: clean
clean:
	@echo ""
	@echo "Removing build files..."
	@echo ""
	rm -rf $(BUILD)
