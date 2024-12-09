# SPDX-License-Identifier: CC0-1.0
#
# SPDX-FileContributor: Antonio Niño Díaz, 2023

BLOCKSDS	?= /opt/blocksds/core
BLOCKSDSEXT	?= /opt/blocksds/external

# Build artifacts
# ---------------

INSTALLNAME	:= palib

# Tools
# -----

MAKE		:= make
RM		:= rm -rf
CP		:= cp
INSTALL	:= install

# Verbose flag
# ------------

ifeq ($(VERBOSE),1)
V		:=
else
V		:= @
endif

# Targets
# -------

.PHONY: all arm7 arm9 clean install install-lib sys

all: arm9 arm7

arm9:
	@+$(MAKE) -f Makefile.arm9 --no-print-directory

arm7:
	@+$(MAKE) -f Makefile.arm7 --no-print-directory

clean:
	@echo "  CLEAN"
	@$(RM) $(VERSION_HEADER) lib build
	@+$(MAKE) -C sys clean

install-lib: arm9 arm7
	@echo "  INSTALL LIB $(BLOCKSDSEXT)/$(INSTALLNAME)/"
	$(V)$(RM) $(BLOCKSDSEXT)/$(INSTALLNAME)/
	$(V)$(INSTALL) -d $(BLOCKSDSEXT)/$(INSTALLNAME)/
	$(V)$(CP) -r include lib $(BLOCKSDSEXT)/$(INSTALLNAME)/

sys: install-lib
	@+$(MAKE) -C sys

install: sys
	@echo "  INSTALL SYS $(BLOCKSDSEXT)/$(INSTALLNAME)/"
	$(V)$(INSTALL) -d $(BLOCKSDSEXT)/$(INSTALLNAME)/
	+$(MAKE) -C sys install INSTALLDIR=$(BLOCKSDSEXT)/$(INSTALLNAME)/sys
	$(V)$(CP) -r defaultlogo.bmp $(BLOCKSDSEXT)/$(INSTALLNAME)/
