SRC =\
	Libraries/Bro/Library/Source/OSX/Bro.mm\
	Libraries/Bro/Library/Source/OSX/View.mm\
	User/main.cpp
	
FRAMEWORKS = -framework CoreFoundation -framework QuartzCore -framework AppKit -framework OpenGL

USER_HEADER_DIRS = -ILibraries/Bro/Library/Include -IUser

NAME = Flowstone

OUTPUT_DIR = $(NAME).app/Contents/MacOS

OUTPUT = $(OUTPUT_DIR)/$(NAME)

all:
	mkdir -p $(OUTPUT_DIR)
	clang++ -Wall -std=gnu++11 -stdlib=libc++ $(USER_HEADER_DIRS) $(FRAMEWORKS) $(SRC) -o $(OUTPUT)
