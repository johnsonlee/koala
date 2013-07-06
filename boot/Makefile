include ../Makefile.inc

BIN: boot.bin

.PHONY: all clean

all: $(BIN)

boot.bin: boot.asm
	@$(ASM) $(ASMFLAGS) $^ -o $@

floppy: boot.bin ../a.img
	@$(DD) if=boot.bin of=../a.img bs=512 count=1 conv=notrunc

clean:
	@$(RM) $(RMFLAGS) $(BIN)
