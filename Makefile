OSNAME = AderinaOS

GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin
CC = gcc
LDS = kernel.ld
LD = ld

CFLAGS = -ffreestanding -fshort-wchar
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

SRCDIR := src
OBJDIR := lib
BUILDDIR = ./bin
BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.c)          
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DIRS = $(wildcard $(SRCDIR)/*)

kernel: $(OBJS) # link

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

link:
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)

setup:
	@mkdir $(BUILDDIR)
	@mkdir $(SRCDIR)
	@mkdir $(OBJDIR)

buildimg:
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	mformat -i $(BUILDDIR)/$(OSNAME).img -f 1440 ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-ext-light16.psf ::

makeall:
	@echo '|===Welcome to the AderinaOS Make!===|'
	@echo '|===Create Bootloader:===|'
	cd ../gnu-efi/ && make bootloader
	@echo '|===BootLoader Created!===|'
	@echo '|===Create Kernel:===|'
	cd ../kernel/
	make kernel
	@echo '|===Linking please wait!===|'
	make link
	@echo '|===Linking finished!===|'
	@echo '|===Kernel Created!===|'
	@echo "|===Build Image $(OSNAME)!===|"
	make buildimg
	@echo '|===Build Image finished!===|'
	@echo '|===Good Luck & Have Fun!===|'

run:
	qemu-system-x86_64 -drive format=raw,file=$(BUILDDIR)/$(OSNAME).img -m 256M -cpu qemu64 -drive \
	if=pflash,format=raw,file=$(OVMFDIR)/"OVMF_CODE-pure-efi.fd",readonly=on -drive \
	if=pflash,format=raw,file=$(OVMFDIR)/"OVMF_VARS-pure-efi.fd"
