NAME = Flowstone

USER_SRC =\
	Libraries/Bro/Library/Source/OSX/Bro.mm\
	Libraries/Bro/Library/Source/OSX/View.mm\
	Libraries/Cabi/Library/Source/OSX/Cabi.mm\
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

USER_FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

USER_HEADER_DIRS =\
	-ILibraries/Bro/Library/Include\
	-ILibraries/Cabi/Library/Include\
	-ILibraries/Conrad/Library/Include\
	-ILibraries/Quanta/Library/Include\
	-ISource\
	-ISource/User\

USER_OUTPUT_DIR = Build/$(NAME).app/Contents
USER_BINARY_DIR = $(USER_OUTPUT_DIR)/MacOS
USER_BINARY_PATH = $(USER_BINARY_DIR)/$(NAME)

all: user

user:
	mkdir -p $(USER_BINARY_DIR)
	clang++ -Wall -std=gnu++11 -stdlib=libc++ -ferror-limit=1 $(USER_HEADER_DIRS) $(USER_FRAMEWORKS) $(USER_SRC) -o $(USER_BINARY_PATH)
	rm -rf $(USER_OUTPUT_DIR)/Resources
	cp -r Resources $(USER_OUTPUT_DIR)/.

.PHONY: test

TEST_SRC =\
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

test:
	clang++ -Wall -std=gnu++11 -stdlib=libc++ $(TEST_HEADER_DIRS) $(TEST_SRC) -o Build/Test
	./Build/Test
