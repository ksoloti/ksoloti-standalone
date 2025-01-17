BOARDDEF =
FWOPTIONDEF =


# Some new options are important to keep
# SRAM usage and DSP load low with newer GCC versions.
# "--param max-completely-peeled-insns=100" makes a big difference to get SRAM down. Newer GCC versions use 200 here, original axoloti (GCC 4.9) used 100.
# below the single backslash line are options which are unknown to make any difference so far
CCFLAGS = \
    -Wno-implicit-fallthrough \
    -Wno-unused-parameter \
    -Wno-return-type \
    -ggdb3 \
    -mcpu=cortex-m4 \
    -mfloat-abi=hard \
    -mfpu=fpv4-sp-d16 \
    -mthumb \
    -mtune=cortex-m4 \
    -mword-relocations \
    -nostartfiles \
    -nostdlib \
    -std=c++11 \
    -O3 \
    --param max-completely-peeled-insns=100 \
    -fcode-hoisting \
    -fno-threadsafe-statics \
    -ffunction-sections \
    -fdata-sections \
    -fno-common \
    -fno-math-errno \
    -fno-reorder-blocks \
    -fno-rtti \
    -mno-thumb-interwork \
    -fno-use-cxa-atexit \
    -fpermissive \
    -ffast-math \
    -fno-unsafe-math-optimizations \
    -fno-signed-zeros \
    -ffp-contract=off \
    \


DEFS = \
    -D$(BOARDDEF) \
    -DARM_MATH_CM4 \
    -DCORTEX_USE_FPU=TRUE \
    -DTHUMB \
    -DTHUMB_NO_INTERWORKING \
    -DTHUMB_PRESENT \
    -D__FPU_PRESENT

ELFNAME=
ifeq ($(BOARDDEF),BOARD_KSOLOTI_CORE)
  RAMLINKOPT = -Tramlink_ksoloti.ld
  ELFNAME = ksoloti
else ifeq ($(BOARDDEF),BOARD_AXOLOTI_CORE)
  RAMLINKOPT = -Tramlink_axoloti.ld
  ELFNAME = axoloti
endif

ifeq ($(FWOPTIONDEF),FW_SPILINK)
  ELFNAME := $(ELFNAME)_spilink
  DEFS := $(DEFS) -DFW_SPILINK
endif

LDFLAGS = \
    $(RAMLINKOPT) \
    -Bsymbolic \
    -Wl,--gc-sections \
    -Wl,--print-memory-usage \
    -fno-common \
    -mcpu=cortex-m4 \
    -mfloat-abi=hard \
    -mfpu=fpv4-sp-d16 \
    -mno-thumb-interwork \
    -mthumb \
    -mtune=cortex-m4 \
    -nostartfiles

TRGT = arm-none-eabi-
CC=$(TRGT)gcc
CPP=$(TRGT)g++
LD=$(TRGT)gcc
CP=$(TRGT)objcopy
DMP=$(TRGT)objdump
SIZ=$(TRGT)size

axoloti_runtime ?= ..
axoloti_release ?= ..
axoloti_home ?= ..
axoloti_libraries ?= ..
axoloti_firmware ?= ../firmware

CHIBIOS = ${axoloti_release}/chibios
CMSIS = ${axoloti_release}/CMSIS

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)
BUILDDIR=$(subst $(SPACE),\ ,${axoloti_libraries}/build)
FIRMWARE=$(subst $(SPACE),\ ,${axoloti_firmware})

include $(CHIBIOS)/os/hal/platforms/STM32F4xx/platform.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/ports/GCC/ARMCMx/STM32F4xx/port.mk
include $(CHIBIOS)/os/kernel/kernel.mk
include $(CHIBIOS)/os/various/fatfs_bindings/fatfs.mk

INCDIR = $(CMSIS)/Core/Include $(CMSIS)/DSP/Include \
         $(PORTINC) $(KERNINC) $(TESTINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) $(FATFSINC) \
         ${FIRMWARE} $(CHIBIOS) ${FIRMWARE}/mutable_instruments

# Paths
IINCDIR = $(patsubst %,-I%,$(INCDIR) $(DINCDIR) $(UINCDIR))
LLIBDIR = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))

all: ${BUILDDIR}/xpatch.bin

${BUILDDIR}/xpatch.h.gch: ${FIRMWARE}/xpatch.h ${FIRMWARE}/patch.h ${FIRMWARE}/axoloti.h ${FIRMWARE}/parameter_functions.h ${FIRMWARE}/axoloti_math.h ${FIRMWARE}/axoloti_filters.h
#	@echo Building precompiled header
	@$(CPP) $(CCFLAGS) $(DEFS) $(IINCDIR) -Winvalid-pch -MD -MP -c ${FIRMWARE}/xpatch.h -o ${BUILDDIR}/xpatch.h.gch

${BUILDDIR}/xpatch.bin: ${BUILDDIR}/xpatch.cpp ${BUILDDIR}/xpatch.h.gch
#	@echo Removing previous build files
	@rm -f ${BUILDDIR}/xpatch.o ${BUILDDIR}/xpatch.elf ${BUILDDIR}/xpatch.bin ${BUILDDIR}/xpatch.d ${BUILDDIR}/xpatch.map ${BUILDDIR}/xpatch.list ${BUILDDIR}/xpatch.siz
#	@echo Compiling patch dependencies
	@$(CPP) $(CCFLAGS) $(DEFS) -H $(IINCDIR) -Winvalid-pch -MD -MP --include ${BUILDDIR}/xpatch.h -c ${BUILDDIR}/xpatch.cpp -o ${BUILDDIR}/xpatch.o
#	@echo Linking patch dependencies
	@$(LD) $(LDFLAGS) ${BUILDDIR}/xpatch.o -Wl,-Map=${BUILDDIR}/xpatch.map,--cref,--just-symbols=${FIRMWARE}/build/$(ELFNAME).elf -o ${BUILDDIR}/xpatch.elf

#	@echo Creating binary
	@$(CP) -O binary ${BUILDDIR}/xpatch.elf ${BUILDDIR}/xpatch.bin

#	@echo Creating SIZe statistic file for debugging
	@$(SIZ) --format=sysv ${BUILDDIR}/xpatch.elf > ${BUILDDIR}/xpatch.siz
	@$(SIZ) --format=berkeley ${BUILDDIR}/xpatch.elf >> ${BUILDDIR}/xpatch.siz

#	@echo Creating LST file for debugging
	@$(DMP) --demangle --source-comment --disassemble ${BUILDDIR}/xpatch.elf > ${BUILDDIR}/xpatch.list
#   (--source-comment now supported in gcc9) --line-numbers 

.PHONY: clean

clean:
	@rm -f ${BUILDDIR}/xpatch.o ${BUILDDIR}/xpatch.elf ${BUILDDIR}/xpatch.bin ${BUILDDIR}/xpatch.d ${BUILDDIR}/xpatch.map ${BUILDDIR}/xpatch.list ${BUILDDIR}/xpatch.h.gch