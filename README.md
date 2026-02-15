# NotMinecraftEngine

A voxel-based game engine inspired by Minecraft, built with C++, OpenGL, and Lua scripting. This engine features a chunk-based terrain system with procedural generation, Lua-driven game logic, and a flexible resource management system.

## Features

### Core Engine
- **OpenGL 3.3** rendering pipeline with instanced block rendering
- **GLFW** window management and input handling
- **GLAD** for OpenGL function loading
- **GLM** for mathematics and transformations

### Lua Integration
- Full Lua scripting support via **LuaBridge**
- Multiple Lua states for isolated script execution
- Engine API exposed to Lua for complete game logic control
- State-specific script directories

### Procedural Generation
- Integrated **FastNoise** library for noise types:
  - Perlin, Simplex, Value, Cellular, Cubic
  - Fractal variants (FBM, Billow, RigidMulti)
  - Customizable frequency, octaves, lacunarity, and gain
- Bilinear interpolation for smooth terrain transitions

### Block System
- Efficient instanced rendering for thousands of blocks
- 6-face texture support (different textures per face)
- Individual block system instances for flexible organization
- Configurable block size and positioning

### Resource Management
- Centralized `ResourceManager` for:
  - Shaders
  - Cameras
  - Block systems
- Texture loading via stb_image
- Safe resource access with ID validation

### Camera System
- Free-flight camera with 6 degrees of movement
- Mouse look with configurable sensitivity
- FOV adjustment
- Multiple camera instances support

### Chunk-Based World
- 16x16 chunk system (configurable)
- Dynamic chunk loading/unloading based on player position
- Heightmap-based terrain generation
- Culling of internal block faces for performance
- Block data caching for efficient updates

## Project Structure

```
NotMinecraftEngine/
├── Engine/
│   ├── Core/
│   │   ├── Lua/           # Lua state management
│   │   ├── Noise/         # FastNoise integration
│   │   ├── Resources/      # Shaders, Cameras, Blocks, Textures
│   │   ├── Window/         # GLFW window handling
│   │   └── Core.h          # Core structure aggregator
│   └── Engine.h/cpp        # Main engine interface
├── Shaders/
│   ├── Block.vs            # Vertex shader for blocks
│   └── Block.fs            # Fragment shader for blocks
├── gamedata/               # Lua scripts and game data
│   ├── EngineConstants.lua # Global engine constants
│   ├── MainLuaState/       # Main game logic
│   └── ChunkLoader/        # Chunk management system
└── Main.cpp                 # Entry point
```

## Lua API

The engine exposes an extensive API to Lua scripts:

### Core Functions
```lua
Engine.createShader(vertexPath, fragmentPath)
Engine.loadTexture(filePath, isOpaque)
Engine.createLuaState(directory)
```

### Block System
```lua
Engine.createBlockSystem()
Engine.addBlockInfo(blockSystemID, x, y, z)
Engine.setBlockTexture(direction, blockSystemID, textureID)
Engine.setBlockSystemShader(blockSystemID, shaderID)
Engine.drawBlocks(blockSystemID)
Engine.clearBlocksData(blockSystemID)
```

### Camera Controls
```lua
Engine.getCurrentCameraX/Y/Z()
Engine.getCurrentCameraFrontX/Y/Z()
Engine.getCurrentCameraYaw/Pitch()
Engine.setCurrentCameraPosition(x, y, z)
Engine.setCurrentCameraRotation(yaw, pitch)
Engine.handleCurrentCamera(direction)  -- CAMERA_FORWARD, etc.
```

### Noise Generation
```lua
Engine.setNoiseSeed(seed)
Engine.setNoiseType(type)           -- NOISE_TYPE_SIMPLEX, etc.
Engine.setNoiseFrequency(frequency)
Engine.setFractalOctaves(octaves)
Engine.setFractalGain(gain)
Engine.getNoise(x, z)                -- Returns height value
```

### Input
```lua
Engine.isPressed(buttonID)           -- BUTTON_W, BUTTON_SPACE, etc.
```

## Building

### Dependencies
- OpenGL 3.3+
- GLFW3
- GLAD
- GLM
- Lua 5.3+
- LuaBridge
- stb_image (included)

### Build Instructions
1. Ensure all dependencies are installed and properly linked
2. Configure your build system (CMake or Make)
3. Compile the project
4. Run the executable from the project root (to access shaders and gamedata)

## Getting Started

1. The engine starts from `Main.cpp` which calls `Engine::start()`
2. A main Lua state is created from `gamedata/MainLuaState`
3. The main state creates a chunk loader state and handles camera input
4. The chunk loader generates terrain procedurally around the player

## Configuration

Edit `gamedata/EngineConstants.lua` to adjust:
- Window dimensions
- Input key mappings
- Block directions
- Noise types and parameters
- Render distance
- Camera settings

## License

- Engine code: MIT License
- FastNoise: MIT License (Copyright (c) 2017 Jordan Peck)
- stb_image: Public Domain / MIT License
- LuaBridge: MIT License
