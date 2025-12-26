# Tetris Game

A modern Tetris game with advanced mechanics built with SFML 3 and C++17.

## ✨ Features

### Core Mechanics

- 🎮 Classic Tetris gameplay with modern enhancements
- 🎲 **7-Bag Random System** - Fair piece distribution
- ⏱️ **Lock Delay** - 500ms grace period with 15-move infinity
- 🔄 **DAS & ARR** - Delayed Auto Shift (133ms) and Auto Repeat Rate
- 🎯 **Ghost Piece** - Shows landing position

### Advanced Techniques

- 🌀 **T-Spin Detection** - 3-corner algorithm with bonus scoring
- 🔥 **Back-to-Back (B2B)** - 1.5x multiplier for consecutive special clears
- ✨ **Perfect Clear** - +3000 bonus for clearing entire board
- 📊 **Combo System** - Chain multiple line clears

### Visual & Audio

- 🎨 NES-style 3D tile graphics with antialiasing
- 💫 Particle effects on line clears
- 🌈 Soft drop trail animation
- 🎵 Music & SFX with volume control
- 🖥️ **Fullscreen support** (F11 toggle with aspect ratio preservation)

### UI & UX

- 📋 **2x2 Grid: Hold (top-left) + NEXT queue (J-shaped)** - 3-piece preview
- 🔲 **Hold Piece** - Store piece for later (C key)
- ⏸️ Pause menu with settings access
- 📊 Live statistics (Score, Level, Lines, Tetris count, T-Spin count, Max Combo)
- 🎯 3 Difficulty levels (Easy/Normal/Hard)
- 💾 Settings persistence (config.ini)
  - Music Volume (0-100%)
  - SFX Volume (0-100%)
  - Brightness (20-100%)
  - **DAS** (100-200ms) - Delayed Auto Shift
  - **ARR** (0-50ms) - Auto Repeat Rate
  - Ghost Piece toggle
- 🏆 High score tracking
- 📖 **How To Play screen** - Complete tutorial with game mechanics

## 🎮 Controls

| Key     | Action                  |
| ------- | ----------------------- |
| ← →     | Move left/right         |
| ↓       | Soft drop (+1 pt/cell)  |
| ↑       | Rotate clockwise        |
| Space   | Hard drop (+2 pts/cell) |
| C       | Hold piece              |
| P / ESC | Pause                   |
| F11     | Toggle fullscreen       |

## 🏗️ Build Instructions

### Prerequisites

- **Windows**: MinGW-w64 (GCC compiler) + Make
- **Linux**: GCC + Make

**No SFML installation required!** All libraries included in `lib/` folder - fully isolated & self-contained.

### Quick Start

```bash
git clone https://github.com/24521928/Tetris_24521928_24521784_24520881_23520764_24521294/tree/BigUpdate
cd Tetris_24521928_24521784_24520881_23520764_24521294
make
make run
```

### Build Options

```bash
make         # Build debug version
make release # Build optimized version (O2 flag)
make run     # Build and run
make clean   # Clean build files
```

### Platform Support

- ✅ **Windows** (MinGW-w64 + MSYS2) → generates `Tetris.exe`
- ✅ **Linux** (GCC) → generates `Tetris` executable
- ✅ **macOS** (GCC/Clang) → generates `Tetris` executable

The Makefile automatically detects your OS and configures the build appropriately.

## 📁 Project Structure

```
├── main.cpp           # Entry point, game loop, DAS/ARR, fullscreen
├── src/
│   ├── Config.h       # Game constants, enums (GameState, Difficulty)
│   ├── Piece.h/cpp    # 7-bag randomizer, piece shapes
│   ├── Game.h/cpp     # T-Spin, B2B, lock delay, settings persistence
│   ├── Audio.h/cpp    # Volume control, SFX system
│   └── UI.h/cpp       # 2-column sidebar, particles, animations, menus
├── lib/
│   ├── libsfml-*.dll          # SFML 3.0 runtime libraries
│   ├── libsfml-*.dll.a        # SFML import libraries (for building)
│   ├── libFLAC.dll, libogg-*.dll, libvorbis-*.dll  # Audio codecs
│   ├── libfreetype-6.dll      # Font rendering
│   └── lib*-*.dll             # Runtime dependencies (GCC, pthreads, etc.)
├── assets/
│   ├── audio/         # Sound effects & music
│   └── fonts/         # Game font (Monocraft.ttf)
├── Makefile           # Cross-platform build (auto-detects Windows/Linux/macOS)
└── README.md          # This file
```

## 🎯 Scoring System

### Basic Scoring

- Single line: **100 × Level**
- Double: **300 × Level**
- Triple: **500 × Level**
- Tetris (4 lines): **800 × Level**

### T-Spin Bonuses

- T-Spin Single: **800 × Level**
- T-Spin Double: **1200 × Level**
- T-Spin Triple: **1600 × Level**

### Special Bonuses

- **Back-to-Back**: 1.5× multiplier for consecutive Tetris/T-Spin
- **Perfect Clear**: +3000 points
- **Combo**: Bonus for consecutive line clears
- **Soft Drop**: +1 point per cell
- **Hard Drop**: +2 points per cell

## 🔧 Technical Details

- **Language**: C++17
- **Graphics**: SFML 3.0
- **Antialiasing**: Level 8 for smooth rendering
- **Window**: 800×800 with fullscreen support
- **Architecture**: Modular design with separate Game, UI, Audio systems
- **Settings**: Persistent config.ini
  - Volume controls (Music, SFX)
  - Display brightness (51-255 internal, 20-100% display)
  - Input timing (DAS: 100-200ms, ARR: 0-50ms)
  - Visual toggles (Ghost Piece)
- **Code Style**: Uniform commenting for all source files with GPL v3 headers

## 📦 Distribution

The game is **fully portable and platform-independent**:

- All dependencies included in `lib/` folder (no external DLL interference)
- No installation required
- Works on Windows, Linux, and macOS

**Minimal distribution package:**

```
Tetris/
├── Tetris.exe        (or just "Tetris" on Linux/macOS)
├── lib/              (17 essential DLL/SO files)
├── assets/           (audio + fonts)
└── config.ini        (auto-generated on first run)
```

Simply distribute these folders and users can run the game immediately.

## 🤝 Development

To modify and rebuild the game:

1. Clone the repository
2. Edit source files in `src/` or `main.cpp`
3. Run `make` to rebuild
4. Run `make run` to test

**Key advantages of this setup:**
- ✅ All dependencies are local (`/lib` folder) - no system SFML installation needed
- ✅ Works on Windows, Linux, and macOS with the same Makefile
- ✅ Fully portable - just copy the exe + `/lib` + `/assets` folders to another machine
- ✅ No external .dll interference - only uses libraries in `/lib`

### Dependency Isolation

The project uses a self-contained dependency strategy:
- All SFML libraries (`.dll`, `.dll.a`, and dependencies) are in `/lib`
- Build process links exclusively from `/lib` using `-Llib` flag
- Runtime uses explicit library path (`LD_LIBRARY_PATH` on Linux, `PATH` on Windows)
- Result: Clean, reproducible builds without system dependency conflicts

## 📝 License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.
