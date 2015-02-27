NAME = Flowstone

CC = clang++
CPP_CFLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1

USER_SOURCES_CPP =\
	Source/Timing.cpp

USER_SOURCES_OBJC = \
	Source/Util.m\
	Source/GameView.m\
	Source/GameAppDelegate.m\
	Source/GameWindow.m\
	Source/GameWindowDelegate.m\
	Source/GameApplication.m

USER_SOURCES_OBJCPP = \
	Source/main.mm

USER_HEADER_DIRS =\
	-I../../Libraries/Quanta/Library/Include\
	-IInclude

USER_FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

BUILD_DIR = ../../Build

USER_OBJECTS =\
	$(patsubst %.cpp,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_CPP))\
	$(patsubst %.mm,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_OBJCPP))\
	$(patsubst %.m,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_OBJC))

USER_OUTPUT_DIR = $(BUILD_DIR)/$(NAME).app/Contents
USER_EXECUTABLE_DIR = $(USER_OUTPUT_DIR)/MacOS
USER_EXECUTABLE_PATH = $(USER_EXECUTABLE_DIR)/$(NAME)

$(BUILD_DIR)/Objects/User/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPP_CFLAGS) $(USER_HEADER_DIRS) $< -c -o $@

$(BUILD_DIR)/Objects/User/%.o : %.mm
	mkdir -p $(dir $@)
	$(CC) $(CPP_CFLAGS) $(USER_HEADER_DIRS) $< -c -o $@

$(BUILD_DIR)/Objects/User/%.o : %.m
	mkdir -p $(dir $@)
	$(CC) $(USER_HEADER_DIRS) $< -c -o $@

user: $(USER_EXECUTABLE_PATH)

$(USER_EXECUTABLE_PATH): $(USER_OBJECTS)
	mkdir -p $(USER_EXECUTABLE_DIR)
	$(CC) $(CFLAGS) $(USER_FRAMEWORKS) $(USER_OBJECTS) -o $(USER_EXECUTABLE_PATH)
	rm -rf $(USER_OUTPUT_DIR)/Resources
	cp -r ../../Resources $(USER_OUTPUT_DIR)/.

all: user

clean:
	rm -rf $(BUILD_DIR)

run: user
	# todo: fix this hack
	rm -rf $(USER_OUTPUT_DIR)/Resources
	cp -r ../../Resources $(USER_OUTPUT_DIR)/.
	$(USER_OUTPUT_DIR)/MacOS/$(NAME)
