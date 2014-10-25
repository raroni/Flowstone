NAME = Flowstone

SRC =\
	Libraries/Bro/Library/Source/OSX/Bro.mm\
	Libraries/Bro/Library/Source/OSX/View.mm\
	Libraries/Cabi/Library/Source/OSX/Cabi.mm\
	Libraries/Quanta/Library/Source/Math/Matrix4.cpp\
	Source/User/main.cpp\
	Source/User/Timing.cpp\
	Source/User/Rendering/Renderer.cpp\
	Source/User/Rendering/ShaderRegistry.cpp\
	Source/User/Rendering/WorldRenderer.cpp\
	Source/User/Mainflow/SinglePlayerState.cpp

FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

USER_HEADER_DIRS =\
	-ILibraries/Bro/Library/Include\
	-ILibraries/Cabi/Library/Include\
	-ILibraries/Conrad/Library/Include\
	-ILibraries/Quanta/Library/Include\
	-ISource\
	-ISource/User\

OUTPUT_DIR = Build/$(NAME).app/Contents
BINARY_DIR = $(OUTPUT_DIR)/MacOS
BINARY_PATH = $(BINARY_DIR)/$(NAME)

all:
	mkdir -p $(BINARY_DIR)
	clang++ -Wall -std=gnu++11 -stdlib=libc++ $(USER_HEADER_DIRS) $(FRAMEWORKS) $(SRC) -o $(BINARY_PATH)
	rm -rf $(OUTPUT_DIR)/Resources
	cp -r Resources $(OUTPUT_DIR)/.
