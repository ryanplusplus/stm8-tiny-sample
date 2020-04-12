TARGET := tiny
BUILD_DIR := ./build/blue-atomic
TOOLS_DIR := tools
STM8_TINY := lib/stm8-tiny
TINY := $(STM8_TINY)/lib/tiny

DEVICE := stm8s103f3
DEVICE_TYPE := STM8S103
STLINK := stlinkv2
OPENOCD_CFG := openocd/stm8s103.cfg
TOOLCHAIN_VERSION := 4.0.0

MAIN := src/app/blue-atomic/main.c

SRC_FILES := \

SRC_DIRS := \
  src/app/blue-atomic \
	src/rtos \

LIB_FILES := \
  lib/atomthreads/ports/stm8/atomport-asm-sdcc.s \

LIB_DIRS := \
  $(TINY)/src \
  $(STM8_TINY)/src \
  lib/atomthreads/kernel \

INC_DIRS := \
  $(TINY)/include \
  src/rtos \

include $(TOOLS_DIR)/makefile-worker.mk
