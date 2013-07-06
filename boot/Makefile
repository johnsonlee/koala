include ../Makefile.inc

BIN := boot.bin boot.com

.PHONY: all clean

all: $(BIN)

boot.bin: boot.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

boot.com: boot.asm
	$(ASM) $(ASMFLAGS) -D__BOOT_DEBUG__ $^ -o $@

floppy: boot.bin ../a.img
	$(DD) if=boot.bin of=../a.img bs=512 count=1 conv=notrunc

clean:
	@$(RM) $(RMFLAGS) $(BIN)
