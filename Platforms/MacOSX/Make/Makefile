all: client

NAME = Flowstone
RELATIVE_ROOT_DIR = ../../..
BUILD_DIR = Build
RELATIVE_BUILD_DIR = $(RELATIVE_ROOT_DIR)/$(BUILD_DIR)
CC = clang++
CPP_FLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1
PLATFORM_DIR = Platforms/MacOSX

include Client.mk

clean:
	rm -rf $(RELATIVE_BUILD_DIR)

run: client
	./$(CLIENT_RELATIVE_BINARY)

.PHONY: all run clean
