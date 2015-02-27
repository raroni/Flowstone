NAME = Flowstone

CC = clang++
CFLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1

USER_SOURCES_CPP =\
	main.cpp\

USER_HEADER_DIRS =\
	-ISome/Thing\
	-ISome/Thing/Else\

USER_FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

BUILD_DIR = ../../Build
USER_OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/Objects/User/%.o,$(USER_SOURCES_CPP))
USER_OUTPUT_DIR = $(BUILD_DIR)/$(NAME).app/Contents
USER_EXECUTABLE_DIR = $(USER_OUTPUT_DIR)/MacOS
USER_EXECUTABLE_PATH = $(USER_EXECUTABLE_DIR)/$(NAME)

$(BUILD_DIR)/Objects/User/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(USER_HEADER_DIRS) $< -c -o $@

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
