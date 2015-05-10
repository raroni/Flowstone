all: client

NAME = Flowstone
RELATIVE_ROOT_DIR = ../../..
BUILD_DIR = Build
RELATIVE_BUILD_DIR = $(RELATIVE_ROOT_DIR)/$(BUILD_DIR)
CC = clang++
CPP_FLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1
PLATFORM_DIR = Platforms/MacOSX

RELEASE ?= 0
ifeq ($(RELEASE), 0)
	CC_FLAGS += -DDEV
endif

include Client.mk
include Test.mk

clean:
	rm -rf $(RELATIVE_BUILD_DIR)

run: client
	./$(CLIENT_RELATIVE_BINARY)

.PHONY: all run clean
