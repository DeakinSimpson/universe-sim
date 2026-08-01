using Silk.NET.Windowing;

public class Engine
{
    private readonly IWindow window;                // stores the window that will be rendered to
    private readonly List<IUpdateable> updatables;  // stores all objects that need to be updated each frame
    private readonly List<IRenderable> renderables; // stores all objects that need to be rendered each frame
}