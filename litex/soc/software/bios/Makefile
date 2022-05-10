include ../include/generated/variables.mak
include $(SOC_DIRECTORY)/software/common.mak


# SRCS := $(shell pwd) # $(wildcard *.c)
# $(error $(SRCS))

OBJECTS := main.o

# helpers.o			\

# cmd_bios.o		\
# 	  cmd_mem.o			\
# 	  cmd_boot.o		\
# 	  sim_debug.o		\

#   cmd_i2c.o			\
#   cmd_spiflash.o	\
#   cmd_litedram.o	\
#   cmd_liteeth.o		\
#   cmd_litesdcard.o  \
#   cmd_litesata.o    \


# ifneq "$(or $(TERM_NO_COMPLETE),$(TERM_MINI))" ""
# CFLAGS += -DTERM_NO_COMPLETE
# else
# OBJECTS += complete.o
# endif

# ifdef TERM_NO_HIST
# CFLAGS += -DTERM_NO_HIST
# endif

# ifdef TERM_MINI
# CFLAGS += -DTERM_MINI
# OBJECTS += readline_simple.o
# else
# OBJECTS += readline.o
# endif

# ifeq ($(CPU), zynq7000)
# LSCRIPT = linker-zynq.ld
# else ifeq ($(CPU), zynqmp)
# LSCRIPT = linker-zynqmp.ld
# else
LSCRIPT = linker.ld
# endif

all: bios.bin
	$(PYTHON) -m litex.soc.software.memusage bios.elf $(CURDIR)/../include/generated/regions.ld $(TRIPLE)

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@
ifneq ($(OS),Windows_NT)
	chmod -x $@
endif
ifeq ($(CPUENDIANNESS),little)
	$(PYTHON) -m litex.soc.software.mkmscimg $@ --little
else
	$(PYTHON) -m litex.soc.software.mkmscimg $@
endif

bios.elf: $(BIOS_DIRECTORY)/$(LSCRIPT) $(OBJECTS)

vpath %.a $(PACKAGES:%=../%)
# vpath %.a ../libbase


%.elf: crt0.o $(LIBS:%=%.a)
	$(CC) $(LDFLAGS) -T $(BIOS_DIRECTORY)/$(LSCRIPT) -N -o $@ \
		crt0.o \
		$(OBJECTS) \
		$(PACKAGES:%=-L../%) \
		-Wl,--whole-archive \
		-Wl,--gc-sections \
		-Wl,-Map,$@.map \
		$(LIBS:lib%=-l%)

ifneq ($(OS),Windows_NT)
	chmod -x $@
endif

# pull in dependency info for *existing* .o files
# -include $(OBJECTS:.o=.d)

VPATH = $(BIOS_DIRECTORY):$(BIOS_DIRECTORY)/cmds:$(CPU_DIRECTORY)

%.o: %.c
	$(compile)

%.o: %.S
	$(assemble)

clean:
	$(RM) $(OBJECTS) bios.elf bios.bin .*~ *~

.PHONY: all clean
