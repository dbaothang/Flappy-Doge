# Specify the compiler
COMPILER = g++

# Specify where are the header file
INCLUDE_PATH = -Isdl2\SDL2_image-2.6.3\x86_64-w64-mingw32\include\SDL2 \
               -Isdl2\SDL2_mixer-2.6.3\x86_64-w64-mingw32\include\SDL2 \
               -Isdl2\SDL2_ttf-2.20.2\x86_64-w64-mingw32\include\SDL2 \
               -Isdl2\SDL2-2.26.3\x86_64-w64-mingw32\include\SDL2

# Specify library file
LIBRARY_PATH = -Lsdl2\SDL2_image-2.6.3\x86_64-w64-mingw32\lib \
               -Lsdl2\SDL2_mixer-2.6.3\x86_64-w64-mingw32\lib \
               -Lsdl2\SDL2_ttf-2.20.2\x86_64-w64-mingw32\lib \
               -Lsdl2\SDL2-2.26.3\x86_64-w64-mingw32\lib

# Linker flag for SDL2
LINKER_FLAGS = -lSDl2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Compiler flag
COMPILER_FLAGS = -lmingw32

all:
	$(COMPILER) $(INCLUDE_PATH) $(LIBRARY_PATH) -o ./main code/*.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS)
	