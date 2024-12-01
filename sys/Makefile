# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2024

BLOCKSDS	?= /opt/blocksds/core
BLOCKSDSEXT	?= /opt/blocksds/external

# Tools
# -----

CP		:= cp
INSTALL		:= install
RM		:= rm -rf
MAKE		:= make

# Targets
# -------

.PHONY: all arm7_maxmod_dswifi arm7_mp3 arm7_mp3_dswifi clean install

all: arm7_maxmod_dswifi arm7_mp3 arm7_mp3_dswifi

arm7_maxmod_dswifi:
	$(MAKE) -C arm7_maxmod_dswifi

arm7_mp3:
	$(MAKE) -C arm7_mp3

arm7_mp3_dswifi:
	$(MAKE) -C arm7_mp3_dswifi

INSTALLDIR	?= $(BLOCKSDSEXT)/palib/sys
INSTALLDIR_ABS	:= $(abspath $(INSTALLDIR))

install: all
	@echo "  INSTALL $(INSTALLDIR_ABS)"
	@test $(INSTALLDIR_ABS)
	@$(INSTALL) -d $(INSTALLDIR_ABS)
	$(MAKE) -C arm7_maxmod_dswifi install INSTALLDIR=$(INSTALLDIR_ABS)
	$(MAKE) -C arm7_mp3 install INSTALLDIR=$(INSTALLDIR_ABS)
	$(MAKE) -C arm7_mp3_dswifi install INSTALLDIR=$(INSTALLDIR_ABS)

clean:
	$(MAKE) -C arm7_maxmod_dswifi clean
	$(MAKE) -C arm7_mp3 clean
	$(MAKE) -C arm7_mp3_dswifi clean
