using Silk.NET.Windowing;

public class Engine
{
    private readonly IWindow window;                // stores the window that will be rendered to
    private readonly List<IUpdatable> updatables;  // stores all objects that need to be updated each frame
    private readonly List<IRenderable> renderables; // stores all objects that need to be rendered each frame

    // constructor for engine - an Enumarable is something that can be looped over with a foreach
    public Engine(IWindow window, IEnumerable<IUpdatable> updatables, IEnumerable<IRenderable> renderables)
    {
        // set Engines variables
        this.window         = window;
        this.updatables     = updatables.ToList();
        this.renderables    = renderables.ToList();

        window.Update += HandleUpdate;
        window.Render += HandleRender;
    }

    // loop through each updateable and call its Update function
    private void HandleUpdate(double deltaTime)
    {
        foreach (var updateable in updatables)
        {
            updateable.Update(deltaTime);
        }
    }

    // loop through each renderable and call its Render function
    private void HandleRender(double deltaTime)
    {
        foreach (var renderable in renderables)
        {
            renderable.Render(deltaTime);
        }
    }

    public void Start()
    {
        window.Run();
    }
}