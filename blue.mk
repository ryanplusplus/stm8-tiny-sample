TARGET := tiny
BUILD_DIR := ./build/blue
TOOLS_DIR := tools
STM8_TINY := lib/stm8-tiny
TINY := $(STM8_TINY)/lib/tiny

DEVICE := stm8s103f3
DEVICE_TYPE := STM8S103
STLINK := stlinkv2
OPENOCD_CFG := openocd/stm8s103.cfg
TOOLCHAIN_VERSION := 4.0.0

MAIN := src/app/blue/main.c

SRC_FILES := \

SRC_DIRS := \
  src/app/blue \

LIB_FILES := \

LIB_DIRS := \
  $(TINY)/src \
  $(STM8_TINY)/src \
  src/app/common \
  src/device \

INC_DIRS := \
  $(TINY)/include \

include $(TOOLS_DIR)/makefile-worker.mk
