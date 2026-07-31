using Silk.NET.Input;
using Silk.NET.Maths;
using Silk.NET.Windowing;
public class WindowObj
{
    // reference to the window
    private static IWindow _window;
    private static Renderer renderer;
    private static Planet planet;
    private static Shader shader;
    private static IKeyboard primaryKeyboard;
    private static Camera camera;

    //! -- testing zone --
    const string vertexCode = @"
    #version 330 core
    layout (location = 0) in vec3 aPosition;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main()
    {
        gl_Position = projection * view * model * vec4(aPosition, 1.0);
    }";

    const string fragmentCode = @"
    #version 330 core
    out vec4 out_color;

    void main()
    {
        out_color = vec4(1.0, 0.5, 0.2, 1.0);
    }";
    //! -- end testing --

    // set the default window options
    WindowOptions options = WindowOptions.Default with
    {   
        // create a window with size 800x600
        Size = new Vector2D<int>(800, 600),

        // set the top title
        Title = "Universe Simulator"
    };

    // initialise the WindowObj
    public WindowObj()
    {
        // create the window
        _window = Window.Create(options);

        // add functions to the window so it knows what to call
        _window.Load += OnLoad;
        _window.Update += OnUpdate;
        _window.Render += OnRender;
        _window.FramebufferResize += OnFramebufferResize;

        // run the window
        _window.Run();
    }

    // runs code on window launch 
    private static unsafe void OnLoad()
    {
        // now that the window/context actually exists, safe to create input
        IInputContext input = _window.CreateInput();
        primaryKeyboard = input.Keyboards.FirstOrDefault();

        // subscribe every connected keyboard to the KeyDown handler
        for (int i = 0; i < input.Keyboards.Count; i++)
        {
            input.Keyboards[i].KeyDown += KeyDown;
        }

        // load the opengl renderer
        renderer = new Renderer(_window);

        // make planet
        planet = new Planet(0.0f, 0.0f, 0.0f, 1.0f, 20);

        shader = new Shader(vertexCode, fragmentCode, renderer);

        camera = new Camera();
        camera.onLoad(input);
    }

    // runs code before rendering, great for things that need to change each frame
    private static void OnUpdate(double deltaTime)
    {
        // Console.WriteLine("Update!");
        camera.onUpdate((float) deltaTime, primaryKeyboard);
    }

    // renders the frame
    private static unsafe void OnRender(double deltaTime)
    {
        renderer.onRender();

        // render planet
        renderer.renderObject(planet.getVertices(), planet.getIndicies(), shader, planet.getModel(), camera, _window);
    }

    // checks if key is pressed
    private static void KeyDown(IKeyboard keyboard, Key key, int keyCode)
    {
        if (key == Key.Escape)
            _window.Close();
    }

    private static void OnFramebufferResize(Vector2D<int> newSize)
    {
        renderer.getGL().Viewport(newSize);
    }

}