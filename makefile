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
TARGET_NUM   = 0
EFFORT_H     = 0
EFFORT_A     = 0
EFFORT_B     = 0
EFFORT_C     = 0
EFFORT_D     = 0
EFFORT_S     = 0

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

release-pokemons:
ifeq ($(BOX_NUMBER), 1)
	$(MAKE) TARGET=ReleasePokemons_1_box APPEND_CC_FLAGS=-DRELEASE_POKEMONS
else
	$(MAKE) TARGET=ReleasePokemons_$(BOX_NUMBER)_boxes APPEND_CC_FLAGS="-DRELEASE_POKEMONS -DBOX_NUMBER=$(BOX_NUMBER)"
endif

only-hatch-eggs:
	$(MAKE) TARGET=OnlyHatchEggs_$(BOX_NUMBER)_boxes APPEND_CC_FLAGS='-DONLY_HATCH_EGGS -DBOX_NUMBER=$(BOX_NUMBER)'
magical-trade:
	$(MAKE) TARGET=MagicalTrade_$(BOX_NUMBER)_boxes APPEND_CC_FLAGS='-DTRADES -DBOX_NUMBER=$(BOX_NUMBER)'
poke-job:
	$(MAKE) TARGET=PokeJob_$(TARGET_NUM) APPEND_CC_FLAGS='-DPOKE_JOB -DTARGET_NUM=$(TARGET_NUM)'
give-effort:
	$(MAKE) TARGET=GiveEffort APPEND_CC_FLAGS='-DGIVE_EFFORT -DEFFORT_H=$(EFFORT_H) -DEFFORT_A=$(EFFORT_A) -DEFFORT_B=$(EFFORT_B) -DEFFORT_C=$(EFFORT_C) -DEFFORT_D=$(EFFORT_D) -DEFFORT_S=$(EFFORT_S)'
loop-battle-tower:
	$(MAKE) TARGET=LoopBattleTower	APPEND_CC_FLAGS=-DLOOP_BATTLE_TOWER
loop-tournament:
	$(MAKE) TARGET=LoopTournament	APPEND_CC_FLAGS=-DLOOP_TOURNAMENT
repeat-a:
	$(MAKE) TARGET=RepeatA		APPEND_CC_FLAGS=-DREPEAT_A
tokiwatari-watt:
	$(MAKE) TARGET=TokiwatariWatt	APPEND_CC_FLAGS=-DTOKIWATARI_WATT
shake-tree:
	$(MAKE) TARGET=ShakeTree	APPEND_CC_FLAGS=-DSHAKE_TREE

.PHONY: clean
clean:
	rm -f *.bin *.eep *.elf *.hex *.lss *.map *.sym