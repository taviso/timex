AS=$(WINE) bin/as88.exe
LK=$(WINE) bin/lk88.exe
LC=$(WINE) bin/lc88.exe
SY=$(WINE) bin/sy88.exe
PR=$(WINE) bin/pr88.exe
C88=$(WINE) bin/c88.exe
EQ=$(WINE) bin/makeequ.exe
DESC=etc/s1c88349.dsc
ASFLAGS=-Iinclude/asm/ -Ms -gaLHS -OHjN -LcdeGlmNpqsWXy -e -w125
LKFLAGS=-d$(DESC) -M -c -L -Llib/ -e -N -r
LCFLAGS=-f2b32 -d$(DESC) -M -e -s -w114 -w142 -em_common
C88FLAGS+=-Iinclude -Iinclude/sys -e -O1 -gn
LKLIBS=

# Optionally, we can pre-process files with gnu cpp, to get more modern
# features like variadic macros, just set USE_GNU_CPP = 1
C88PPFLAGS=-C -DSMALL -undef -nostdinc -D_C88 -D__GNU__ -Iinclude -Iinclude/sys

.DEFAULT_GOAL = all
.PHONY: clean buildenv

# Figure out the code and params filenames from the .app file
codebin=$(shell grep -oiP '^code=\K.*' $(or $(firstword $(wildcard *.app)),/dev/null))
parbin=$(shell grep -oiP '^par=\K.*' $(or $(firstword $(wildcard *.app)),/dev/null))
dbbin=$(shell grep -oiP '^db=\K.*' $(or $(firstword $(wildcard *.app)),/dev/null))

# Find out what states exist
sources=$(wildcard state*.asm) $(wildcard state*.c)
states:=$(basename $(sources))

sources+=param.asm common.asm common.c

# Check if this is wsl or Linux.
ifneq ($(findstring Microsoft,$(shell uname -r)), Microsoft)
    WINE=wine
endif


# Get make to delete this junk generated during build.
.INTERMEDIATE: $(addsuffix .lnl,$(states) param common)
.INTERMEDIATE: $(addsuffix .map,$(states) param common)
.INTERMEDIATE: $(addsuffix .obj,$(states) param common)
.INTERMEDIATE: $(addsuffix .cal,$(states) param common)
.INTERMEDIATE: $(addsuffix .sre,$(states) param common)
.INTERMEDIATE: $(addsuffix .out,$(states) param common)
.INTERMEDIATE: $(addsuffix   .s,$(states) param common)

%.bin: %.sre
	objcopy -I srec -O binary $^ $@

# The mv/mv pattern is to workaround case-sensitive fs issues.
# NOTE: I could replace this with an awk script.
%.sy: %.map
	-$(SY) $<
	@mv $@ $@_
	@mv $@_ $@

%.equ: %.sy
	$(EQ) $^
	@mv $@ $@_
	@mv $@_ $@

%.inc: %.equ
	@awk '{print "#define",$$1,strtonum("0x"$$3)}' < $< > $@

%.obj: %.asm
	$(AS) $(ASFLAGS) $< -o $@

%.obj: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.out %.lnl %.cal: %.obj
	$(LK) $(LKFLAGS) $^ -o $@ $(LKLIBS)

%.sre %.map: %.out
	$(LC) $(LCFLAGS) $< -o $@

# We need to make sure there are DOS line endings or the compiler
# incorrectly parses inline assembly.
# we also need to translate GNU line-markers to C88 markers, or
# warnings/errors will have the wrong line.
%.i: %.c
	cpp $(C88PPFLAGS) -o $@_ $<
	@awk '/^# [0-9]+/ {print "#line",++$$2,$$3;next}{print}' < $@_ > $@
	@unix2dos -q $@
	@rm -f $@_

ifdef USE_GNU_CPP
%.s: %.i
else
%.s: %.c
endif
	$(C88) $(C88FLAGS) -o $@_ $^
	awk -f bin/cleancc.awk < $@_ > $@
	@rm -f $@_

all: buildenv $(codebin) $(parbin) $(dbbin)

buildenv:
	@test -f bin/c88.exe || echo please run buildenv.sh to setup the toolchain.
	@test -f bin/c88.exe

# All objects other than the common code need to know the common address.
$(addsuffix .out,params $(states)): | common.equ common.inc
$(addsuffix .s,params $(states)): | common.equ common.inc

# We can't use the short attribute, because code must load at an address > 0x8000
$(addsuffix .obj,$(basename $(wildcard lib/*.asm))): ASFLAGS+=-DSHORT=CODE -w102

common.sre common.map: LCFLAGS:=$(filter-out -em_common,$(LCFLAGS))

$(codebin): common.bin $(sort $(addsuffix .bin,$(states))) | bin/genapp
	./bin/genapp $^ > $@

$(parbin): param.bin | bin/genpar $(codebin)
	./bin/genpar -c $$(wc -c < $(codebin)) < $^ > $@

$(dbbin): $(sort $(wildcard db/*.rec)) | bin/gendb
	./bin/gendb $^ > $@

clean::
	rm -f *.equ *.EQU *.EQU_
	rm -f *.sy *.SY *.SY_
	rm -f *.sre
	rm -f *.out
	rm -f *.obj
	rm -f *.lnl
	rm -f *.map
	rm -f *.cal
	rm -f *.tmp
	rm -f *.bin
	rm -f *.s *.s_
	rm -f *.arg
	rm -f *.inc
	rm -f *.i *.i_
	rm -f lib/*.obj
	rm -f util/*.obj
	rm -rf bin/genapp bin/genpar bin/gendb
	rm -rf bin/DB bin/tucp.ini

distclean:: clean
	rm -f bin/*.exe bin/*.dll
	rm -f etc/s1c88349.cpu
	rm -f etc/s1c88349.mem
	rm -rf lib
	rm -rf include/asm
	rm -rf include/sys
