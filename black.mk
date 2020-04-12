TARGET := tiny
BUILD_DIR := ./build/black
TOOLS_DIR := tools
STM8_TINY := lib/stm8-tiny
TINY := $(STM8_TINY)/lib/tiny

DEVICE := stm8s105k4
DEVICE_TYPE := STM8S105
STLINK := stlinkv2
OPENOCD_CFG := $(TOOLS_DIR)/openocd/stm8s105.cfg
TOOLCHAIN_VERSION := 4.0.0

MAIN := src/app/black/main.c

SRC_FILES := \

SRC_DIRS := \
  src/app/black \

LIB_FILES := \

LIB_DIRS := \
  $(TINY)/src \
  $(STM8_TINY)/src \
  src/app/common \
  src/device \

INC_DIRS := \
  $(TINY)/include \

include $(TOOLS_DIR)/makefile-worker.mk
