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

WSLENV ?= notwsl

ifeq ($(OS),Windows_NT)
	PLATFORM := Windows
else
	PLATFORM := $(shell uname)
endif

os:
ifeq ($(PLATFORM),Windows)
ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	@echo $(PLATFORM) $(PROCESSOR_ARCHITECTURE)
endif
ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	@echo $(PLATFORM) $(PROCESSOR_ARCHITECTURE)
endif
else
ifndef $(WSLENV)
	@echo $(PLATFORM) $(PROCESSOR_ARCHITECTURE) $(WSLENV)
else
ifeq ($(PLATFORM), Linux)
ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	@echo $(PLATFORM) $(PROCESSOR_ARCHITECTURE)
endif
ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	@echo $(PLATFORM) $(PROCESSOR_ARCHITECTURE)
endif
endif
endif
endif
	

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
ifeq ($(PLATFORM),Windows)
	@echo not supported at this version but you can use WSL(debian) Version 2 Good Luck. 
else
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
endif
ifndef $(WSLENV)
	mformat -i $(BUILDDIR)/$(OSNAME).img -f 1440 ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-ext-light16.psf ::
else
	mkfs.fat $(BUILDDIR)/$(OSNAME).img
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-ext-light16.psf ::
endif

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
