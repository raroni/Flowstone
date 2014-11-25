NAME = Flowstone

CC = clang++
CFLAGS = -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1

USER_SOURCES_CPP =\
	Libraries/Quanta/Library/Source/Math/Matrix4.cpp\
	Libraries/Quanta/Library/Source/Math/Quaternion.cpp\
	Libraries/Quanta/Library/Source/Math/Vector3.cpp\
	Libraries/Quanta/Library/Source/Geometry/Transform.cpp\
	Libraries/Quanta/Library/Source/Geometry/TransformationFactory3D.cpp\
	Libraries/Quanta/Library/Source/Geometry/Point3D.cpp\
	Libraries/Quanta/Library/Source/Util.cpp\
	Source/Core/Error.cpp\
	Source/Core/Physics/Engine.cpp\
	Source/Core/Physics/CollisionResolver.cpp\
	Source/User/main.cpp\
	Source/User/Timing.cpp\
	Source/User/Animation/Registry.cpp\
	Source/User/Mainflow/PlayState.cpp\
	Source/User/Rendering/Renderer.cpp\

USER_SOURCES_OBJC = \
	Libraries/Bro/Library/Source/OSX/Bro.mm\
	Libraries/Bro/Library/Source/OSX/View.mm\
	Libraries/Cabi/Library/Source/OSX/Cabi.mm

USER_OBJECTS = $(patsubst %.cpp,Build/Objects/User/%.o,$(USER_SOURCES_CPP)) $(patsubst %.mm,Build/Objects/User/%.o,$(USER_SOURCES_OBJC))

USER_FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

USER_HEADER_DIRS =\
	-ILibraries/Bro/Library/Include\
	-ILibraries/Cabi/Library/Include\
	-ILibraries/Conrad/Library/Include\
	-ILibraries/Quanta/Library/Include\
	-ISource\
	-ISource/User\

USER_OUTPUT_DIR = Build/$(NAME).app/Contents
USER_EXECUTABLE_DIR = $(USER_OUTPUT_DIR)/MacOS
USER_EXECUTABLE_PATH = $(USER_EXECUTABLE_DIR)/$(NAME)

all: user

user: $(USER_EXECUTABLE_PATH)

$(USER_EXECUTABLE_PATH): $(USER_OBJECTS)
	mkdir -p $(USER_EXECUTABLE_DIR)
	$(CC) $(CFLAGS) $(USER_FRAMEWORKS) $(USER_OBJECTS) -o $(USER_EXECUTABLE_PATH)
	rm -rf $(USER_OUTPUT_DIR)/Resources
	cp -r Resources $(USER_OUTPUT_DIR)/.

Build/Objects/User/%.o : %.mm
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(USER_HEADER_DIRS) $< -c -o $@

Build/Objects/User/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(USER_HEADER_DIRS) $< -c -o $@

.PHONY: test

TEST_SOURCES =\
	Libraries/Quanta/Library/Source/Math/Matrix4.cpp\
	Libraries/Quanta/Library/Source/Math/Quaternion.cpp\
	Libraries/Quanta/Library/Source/Math/Vector3.cpp\
	Libraries/Quanta/Library/Source/Geometry/Transform.cpp\
	Libraries/Quanta/Library/Source/Geometry/TransformationFactory3D.cpp\
	Libraries/Quanta/Library/Source/Geometry/Point3D.cpp\
	Libraries/Quanta/Library/Source/Util.cpp\
	Source/Core/Physics/Engine.cpp\
	Source/Core/Physics/CollisionResolver.cpp\
	Test/main.cpp

TEST_HEADER_DIRS =\
	-ILibraries/Conrad/Library/Include\
	-ILibraries/Quanta/Library/Include\
	-ISource\
	-ISource/User\

TEST_OBJECTS = $(patsubst %.cpp,Build/Objects/Test/%.o,$(TEST_SOURCES))

TEST_EXECUTABLE_PATH = Build/Test

test: $(TEST_EXECUTABLE_PATH)
	./Build/Test

$(TEST_EXECUTABLE_PATH): $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(TEST_HEADER_DIRS) $(TEST_OBJECTS) -o $@

Build/Objects/Test/%.o : %.mm
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TEST_HEADER_DIRS) $< -c -o $@

Build/Objects/Test/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TEST_HEADER_DIRS) $< -c -o $@
