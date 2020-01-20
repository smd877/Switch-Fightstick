#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.

# Set the MCU accordingly to your device (e.g. at90usb1286 for a Teensy 2.0++, or atmega16u2 for an Arduino UNO R3)
MCU          = atmega16u2
ARCH         = AVR8
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = HatchEggs_1_box
MODULES      = $(wildcard Modules/*.c)
SRC          = Joystick.c Descriptors.c $(LUFA_SRC_USB) $(MODULES)
LUFA_PATH    = ./lufa/LUFA
CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ ${APPEND_CC_FLAGS}
LD_FLAGS     =
BOX_NUMBER   = 1

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk

hatch-eggs:
ifeq ($(BOX_NUMBER), 1)
	$(MAKE) all
else
	$(MAKE) TARGET=HatchEggs_$(BOX_NUMBER)_boxes APPEND_CC_FLAGS=-DBOX_NUMBER=$(BOX_NUMBER)
endif
loop-battle-tower:
	$(MAKE) TARGET=LoopBattleTower	APPEND_CC_FLAGS=-DLOOP_BATTLE_TOWER
loop-tournament: 
	$(MAKE) TARGET=LoopTournament	APPEND_CC_FLAGS=-DLOOP_TOURNAMENT
release-pokemons:
ifeq ($(BOX_NUMBER), 1)
	$(MAKE) TARGET=ReleasePokemons_1_box APPEND_CC_FLAGS=-DRELEASE_POKEMONS
else
	$(MAKE) TARGET=ReleasePokemons_$(BOX_NUMBER)_boxes APPEND_CC_FLAGS='-DRELEASE_POKEMONS -DBOX_NUMBER=$(BOX_NUMBER)'
endif
repeat-a:
	$(MAKE) TARGET=RepeatA		APPEND_CC_FLAGS=-DREPEAT_A

.PHONY: clean
clean:
	rm -f *.bin *.eep *.elf *.hex *.lss *.map *.sym