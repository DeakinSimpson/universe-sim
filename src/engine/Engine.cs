using System.Drawing;
using Silk.NET.Input;
using Silk.NET.Maths;
using Silk.NET.Windowing;

public class Engine
{
    // initialise all Engine variables
    private static IWindow window;
    private static Renderer renderer;
    private static Camera camera;
    private static IKeyboard primaryKeyboard;
    private static Scene scene;

    WindowOptions options = WindowOptions.Default with
    {
        Size = new Vector2D<int>(800, 600),
        Title = "Universe Simulator"
    };

    // set initial variables
    public Engine()
    {
        scene = new Scene();

        window = Window.Create(options);

        window.Load += OnLoad;
        window.Update += OnUpdate;
        window.Render += OnRender;
        window.FramebufferResize += OnFramebufferResize;
    }

    // starts the engine
    public void Start()
    {
        window.Run();
    }

    // runs on the first load
    private static unsafe void OnLoad()
    {
        // set input and kleyboard
        IInputContext input = window.CreateInput();
        primaryKeyboard = input.Keyboards.FirstOrDefault();

        // runs keyboard check for input
        for (int i = 0; i < input.Keyboards.Count; i++)
        {
            input.Keyboards[i].KeyDown += KeyDown;
        }

        // initialise renderer
        renderer = new Renderer(window);

        // initialise camera
        camera = new Camera();
        camera.onLoad(input);

        // loan the scene
        scene.Load(renderer);
    }

    // runs every frame before rendering frame
    private static void OnUpdate(double deltaTime)
    {
        // update camera positon
        camera.onUpdate((float)deltaTime, primaryKeyboard);

        // update scene
        scene.Update((float)deltaTime);
    }

    private static unsafe void OnRender(double deltaTime)
    {
        // run renderer
        renderer.setBackgroundColour(Color.Black);

        // render the scenee
        scene.Render(renderer, camera, window);
    }

    // check for keydown
    private static void KeyDown(IKeyboard keyboard, Key key, int keyCode)
    {
        if (key == Key.Escape)
        {
            window.Close();            
        }

        if (key == Key.E)
        {
            renderer.ToggleWireframe();
        }
    }

    // resize frame if window is resized
    private static void OnFramebufferResize(Vector2D<int> newSize)
    {
        renderer.getGL().Viewport(newSize);
    }
}