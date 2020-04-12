TARGET := tiny
BUILD_DIR := ./build/blue-207
TOOLS_DIR := tools
STM8_TINY := lib/stm8-tiny
TINY := $(STM8_TINY)/lib/tiny

DEVICE := stm8s207rb
DEVICE_TYPE := STM8S207
STLINK := stlinkv2
OPENOCD_CFG := $(TOOLS_DIR)/openocd/stm8s207.cfg
TOOLCHAIN_VERSION := 4.0.0

MAIN := src/app/blue-207/main.c

SRC_FILES := \

SRC_DIRS := \
  src/app/blue-207 \

LIB_FILES := \

LIB_DIRS := \
  $(TINY)/src \
  $(STM8_TINY)/src \
  src/app/common \
  src/device \

INC_DIRS := \
  $(TINY)/include \

.PHONY: default
default: size

include $(TOOLS_DIR)/makefile-worker.mk
