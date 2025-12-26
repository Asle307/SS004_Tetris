# Tetris Makefile - Cross-platform (Windows & Linux)
# Fully isolated build - only uses local /lib dependencies!
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Ilibsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
SOURCES = main.cpp src/Piece.cpp src/Game.cpp src/Audio.cpp src/UI.cpp

# Detect OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    TARGET = Tetris
    LDFLAGS = -Llib -Wl,-rpath,$$ORIGIN/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
else
    # Windows (MinGW/MSYS2)
    TARGET = Tetris.exe
    LDFLAGS = -Llib -static-libgcc -static-libstdc++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
endif

# Default target
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)

# Release build (optimized)
release: CXXFLAGS = -std=c++17 -O2 -DNDEBUG
release: $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET)

# Run the game (with correct path handling for both OS)
run: $(TARGET)
	@if [ "$(UNAME_S)" = "Linux" ]; then \
		LD_LIBRARY_PATH=./lib ./$(TARGET); \
	else \
		set PATH=$(CURDIR)\lib;%PATH% && $(CURDIR)\$(TARGET); \
	fi

.PHONY: all release clean run
