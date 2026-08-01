# universe-sim

install precompiled binaries for glfw and place them in the lib file in the main project directory (mingw for windows)

<!-- packages -->
dotnet add package Silk.NET.Windowing
dotnet add package Silk.NET.Input
dotnet add package Silk.NET.OpenGL

<!-- engine refactor structure -->
src/
  Core/            # Application entry, game loop, time/clock, config
  Platform/        # Window, input abstraction (wraps Silk.NET specifics)
  Rendering/       # Renderer, Shader, Mesh, Camera, Material — no sim logic
  Scene/           # Scene graph / entity registry, transforms
  Physics/         # Orbital mechanics, gravity, integrators
  Simulation/      # Domain objects: Planet, Star, SolarSystem — data + behavior
  Assets/          # Loading shaders, textures, models (paths, caching)
  Game/            # The actual "universe sim" composition — wires the above together