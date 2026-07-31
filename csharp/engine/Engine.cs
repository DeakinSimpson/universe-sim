using Silk.NET.Input;
using Silk.NET.Maths;
using Silk.NET.OpenGL;
using Silk.NET.Windowing;
using System.Drawing;

public class WindowObj
{
    // reference to the window
    private static IWindow _window;
    private static Renderer renderer;

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

        // run the window
        _window.Run();
    }

    // runs code on window launch 
    private static void OnLoad()
    {
        // now that the window/context actually exists, safe to create input
        IInputContext input = _window.CreateInput();

        // subscribe every connected keyboard to the KeyDown handler
        for (int i = 0; i < input.Keyboards.Count; i++)
        {
            input.Keyboards[i].KeyDown += KeyDown;
        }

        // load the opengl renderer
        renderer = new Renderer(_window);
    }

    // runs code before rendering, great for things that need to change each frame
    private static void OnUpdate(double deltaTime)
    {
        // Console.WriteLine("Update!");
    }

    // renders the frame
    private static void OnRender(double deltaTime)
    {
        renderer.onRender();
    }

    // checks if key is pressed
    private static void KeyDown(IKeyboard keyboard, Key key, int keyCode)
    {
        if (key == Key.Escape)
            _window.Close();
    }

}

public class Renderer
{
    private static GL gl;

    public Renderer(IWindow window)
    {
        gl = window.CreateOpenGL();
        Console.WriteLine("OpenGL opened successfully");

        setBackgroundColour(Color.CornflowerBlue);
    }

    public void onRender()
    {
        setBackgroundColour(Color.CornflowerBlue);
    }

    private void setBackgroundColour(Color color)
    {
        // set the clear colour
        gl.ClearColor(color);

        // render the clear colour
        gl.Clear(ClearBufferMask.ColorBufferBit);
    }
}